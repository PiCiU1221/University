#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <fcntl.h>
#include <pthread.h>
#include <ctype.h>
#include <time.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PID_FILE "prog.pid"

static char document_root[256];
char log_filename[256];
pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

int check_port(int port) {
    if (port < 1 || port > 65535) {
        fprintf(stderr, "Błąd: Niepoprawny numer portu: %d. Musi być w zakresie 1-65535.\n", port);
        return 1;
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        fprintf(stderr, "Błąd: Nie można utworzyć gniazda: %s\n", strerror(errno));
        return 2;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        if (errno == EADDRINUSE) {
            fprintf(stderr, "Błąd: Port %d jest już zajęty przez inną usługę.\n", port);
            close(sock);
            return 3;
        } else {
            fprintf(stderr, "Błąd: Nie można powiązać gniazda z portem: %s\n", strerror(errno));
            close(sock);
            return 4;
        }
    }

    close(sock);
    return 0;
}

int check_directory(const char *dir) {
    struct stat st;
    if (stat(dir, &st) != 0) {
        fprintf(stderr, "Błąd: Nie można odczytać katalogu '%s': %s\n", dir, strerror(errno));
        return 1;
    }

    if (!S_ISDIR(st.st_mode)) {
        fprintf(stderr, "Błąd: Podana ścieżka nie jest katalogiem: %s\n", dir);
        return 2;
    }

    if (access(dir, R_OK) != 0) {
        fprintf(stderr, "Błąd: Brak dostępu do katalogu '%s' (brak uprawnień do odczytu): %s\n", dir, strerror(errno));
        return 3;
    }

    return 0;
}

int check_if_daemon_running() {
    FILE *f = fopen(PID_FILE, "r");
    if (f == NULL) {
        return 1;
    }

    int pid;
    if (fscanf(f, "%d", &pid) != 1) {
        fclose(f);
        return 2;
    }
    fclose(f);

    if (kill(pid, 0) == 0) {
        return 0;
    } else {
        return 3;
    }
}

void daemonize(const char *dir) {
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Błąd: Nie można utworzyć procesu potomnego: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    if (setsid() < 0) {
        fprintf(stderr, "Błąd: Nie można utworzyć nowej sesji: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Błąd: Nie można utworzyć procesu potomnego (fork #2): %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    if (chdir(dir) < 0) {
        fprintf(stderr, "Błąd: Nie można zmienić katalogu na '%s': %s\n", dir, strerror(errno));
        exit(EXIT_FAILURE);
    }

    umask(0);

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    open("/dev/null", O_RDONLY);
    open("/dev/null", O_WRONLY);
    open("/dev/null", O_RDWR);
}

void write_pid_file() {
    FILE *f = fopen(PID_FILE, "w");
    if (!f) {
        exit(EXIT_FAILURE);
    }
    fprintf(f, "%d\n", getpid());
    fclose(f);
}

void get_parent_dir(const char *dir, char *parent_dir, size_t size) {
    strncpy(parent_dir, dir, size - 1);
    parent_dir[size - 1] = '\0';

    char *last_slash = strrchr(parent_dir, '/');
    if (last_slash != NULL) {
        *last_slash = '\0';

        if (parent_dir[0] == '\0') {
            strcpy(parent_dir, "/");
        }
    } else {
        strcpy(parent_dir, ".");
    }
}

void send_binary_response(int client_fd, int code, const char *status, const char *content_type, const void *body, size_t size) {
    char header[1024];
    snprintf(header, sizeof(header),
             "HTTP/1.1 %d %s\r\n"
             "Content-Type: %s\r\n"
             "Content-Length: %zu\r\n"
             "Connection: close\r\n"
             "\r\n",
             code, status, content_type, size);

    send(client_fd, header, strlen(header), 0);
    send(client_fd, body, size, 0);
}

void send_response(int client_fd, int code, const char *status, const char *content_type, const char *body) {
    char header[1024];
    snprintf(header, sizeof(header),
             "HTTP/1.1 %d %s\r\n"
             "Content-Type: %s\r\n"
             "Content-Length: %ld\r\n"
             "Connection: close\r\n"
             "\r\n",
             code, status, content_type, body ? strlen(body) : 0);

    send(client_fd, header, strlen(header), 0);
    if (body)
        send(client_fd, body, strlen(body), 0);
}

void set_document_root(const char *path) {
    strncpy(document_root, path, sizeof(document_root));
}

const char *get_document_root() {
    return document_root;
}

const char* get_mime_type(const char *path) {
    const char *ext = strrchr(path, '.');
    if (!ext) return "application/octet-stream";

    if (strcmp(ext, ".html") == 0 || strcmp(ext, ".htm") == 0) return "text/html";
    if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0) return "image/jpeg";
    if (strcmp(ext, ".png") == 0) return "image/png";
    if (strcmp(ext, ".gif") == 0) return "image/gif";
    return "application/octet-stream";
}

void init_log_filename(const char *program_path) {
    const char *last_slash = strrchr(program_path, '/');
    const char *progname = last_slash ? last_slash + 1 : program_path;
    snprintf(log_filename, sizeof(log_filename), "%s.log", progname);
}

void log_request(const char *client_ip, const char *request_line, int code) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timebuf[64];
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", t);

    pthread_t tid = pthread_self();

    char first_line[1024];
    const char *newline = strchr(request_line, '\n');
    if (newline) {
        size_t len = newline - request_line;
        if (len >= sizeof(first_line)) len = sizeof(first_line) - 1;
        strncpy(first_line, request_line, len);
        first_line[len] = '\0';
        size_t last = strlen(first_line);
        if (last > 0 && first_line[last - 1] == '\r') {
            first_line[last - 1] = '\0';
        }
    } else {
        strncpy(first_line, request_line, sizeof(first_line) - 1);
        first_line[sizeof(first_line) - 1] = '\0';
    }

    pthread_mutex_lock(&log_mutex);
    FILE *logfile = fopen(log_filename, "a");
    if (logfile) {
        fprintf(logfile, "[%s] [TID: %lu] [Client: %s] \"%s\" -> %d\n",
                timebuf, (unsigned long)tid, client_ip, first_line, code);
        fclose(logfile);
    }
    pthread_mutex_unlock(&log_mutex);
}

void *handle_client(void *arg) {
    int client_fd = *(int*)arg;
    free(arg);

    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    getpeername(client_fd, (struct sockaddr *)&addr, &len);
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &addr.sin_addr, client_ip, sizeof(client_ip));

    char buffer[2048];
    int received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (received <= 0) {
        close(client_fd);
        return NULL;
    }

    buffer[received] = '\0';

    char method[8], path[1024], protocol[16];
    sscanf(buffer, "%s %s %s", method, path, protocol);

    if (strcmp(method, "GET") != 0) {
        send_response(client_fd, 501, "Not Implemented", "text/plain", "501 - Only GET is supported.\n");
        log_request(client_ip, buffer, 501);
        close(client_fd);
        return NULL;
    }

    char full_path[1024];
    if (strcmp(path, "/") == 0) {
        snprintf(full_path, sizeof(full_path), "%s/index.html", get_document_root());
    } else {
        snprintf(full_path, sizeof(full_path), "%s%s", get_document_root(), path);
    }

    FILE *file = fopen(full_path, "r");
    if (!file) {
        char message[512];
        snprintf(message, sizeof(message), "404 - File not found: %.480s\n", full_path);
        send_response(client_fd, 404, "Not Found", "text/plain", message);
        log_request(client_ip, buffer, 404);
        close(client_fd);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char *content = malloc(size + 1);
    fread(content, 1, size, file);
    fclose(file);

    const char *mime = get_mime_type(full_path);

    if (strncmp(mime, "text/", 5) == 0 || strcmp(mime, "application/javascript") == 0) {
        send_response(client_fd, 200, "OK", mime, content);
    } else {
        send_binary_response(client_fd, 200, "OK", mime, content, size);
    }

    log_request(client_ip, buffer, 200);
    free(content);

    close(client_fd);
    sleep(100);
    return NULL;
}

void start_server(int port, const char *dir) {
    printf("Uruchamianie serwera jako demon na porcie %d z katalogiem %s...\n", port, dir);

    int port_ok = check_port(port);
    if (port_ok != 0) return;

    int dir_ok = check_directory(dir);
    if (dir_ok != 0) return;

    int daemon_status = check_if_daemon_running();
    if (daemon_status == 0) {
        fprintf(stderr, "Błąd: Demon już działa.\n");
        return;
    }

    char parent_dir[256];
    get_parent_dir(dir, parent_dir, sizeof(parent_dir));
    daemonize(parent_dir);

    set_document_root(dir);

    write_pid_file();

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        fprintf(stderr, "Błąd: Nie można utworzyć gniazda serwera: %s\n", strerror(errno));
        exit(1);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        fprintf(stderr, "Błąd: bind() nie powiódł się: %s\n", strerror(errno));
        exit(1);
    }

    listen(server_fd, 10);

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int *client_fd = malloc(sizeof(int));
        *client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);

        if (*client_fd < 0) {
            free(client_fd);
            continue;
        }

        pthread_t thread;
        pthread_create(&thread, NULL, handle_client, client_fd);
        pthread_detach(thread);
    }
}

void stop_server() {
    printf("Zatrzymywanie serwera...\n");

    int daemon_status = check_if_daemon_running();
    if (daemon_status != 0) {
        fprintf(stderr, "Błąd: Demon nie jest uruchomiony.\n");
        return;
    }

    FILE *f = fopen(PID_FILE, "r");
    if (!f) {
        fprintf(stderr, "Błąd: Nie można otworzyć pliku PID.\n");
        return;
    }

    int pid;
    if (fscanf(f, "%d", &pid) != 1) {
        fprintf(stderr, "Błąd: Nie można odczytać PID z pliku.\n");
        fclose(f);
        return;
    }
    fclose(f);

    if (kill(pid, SIGTERM) != 0) {
        perror("Błąd wysyłania sygnału SIGTERM");
        return;
    }

    if (remove(PID_FILE) != 0) {
        perror("Błąd usuwania pliku PID");
        return;
    }

    printf("Demon o PID %d został zatrzymany.\n", pid);
}

int main(int argc, char *argv[]) {
    int opt;
    int start_flag = 0;
    int stop_flag = 0;
    int port = 0;
    char *dir = NULL;

    while ((opt = getopt(argc, argv, "sp:d:q")) != -1) {
        switch (opt) {
            case 's':
                start_flag = 1;
                break;
            case 'p':
                port = atoi(optarg);
                break;
            case 'd':
                dir = optarg;
                break;
            case 'q':
                stop_flag = 1;
                break;
            default:
                fprintf(stderr, "Użycie: %s -s -p port -d katalog | -q\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (start_flag) {
        if (port <= 0 || dir == NULL) {
            fprintf(stderr, "Błąd: brak portu (-p) lub katalogu (-d) przy starcie serwera.\n");
            exit(EXIT_FAILURE);
        }
        init_log_filename(argv[0]);
        start_server(port, dir);
    } else if (stop_flag) {
        stop_server();
    } else {
        fprintf(stderr, "Musisz podać -s (start) lub -q (zatrzymaj).\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
