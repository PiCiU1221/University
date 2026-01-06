#include <stdlib.h>
#include <string.h>

#define MEM_OK                0
#define MEM_ERR_CALLOC        1
#define MEM_ERR_NODE_ALLOC    2
#define MEM_ERR_REALLOC       3
#define MEM_ERR_PTR_NOT_FOUND 4
#define MEM_ERR_FREE_FAIL     5

int mem_errno = 0;

typedef struct Node {
    void *ptr;
    unsigned int size;
    struct Node *next;
    struct Node *prev;
} Node;

Node *head = NULL;

Node *find_node_by_ptr(void *ptr) {
    Node *current = head;
    while (current) {
        if (current->ptr == ptr)
            return current;
        current = current->next;
    }
    return NULL;
}

void *mem_alloc(void *ptr, unsigned int size) {
    mem_errno = MEM_OK;

    if (ptr == NULL) {
        void *new_ptr = calloc(1, size);
        if (!new_ptr) {
            mem_errno = MEM_ERR_CALLOC;
            return NULL;
        }

        Node *node = malloc(sizeof(Node));
        if (!node) {
            free(new_ptr);
            mem_errno = MEM_ERR_NODE_ALLOC;
            return NULL;
        }

        node->ptr = new_ptr;
        node->size = size;
        node->next = head;
        node->prev = NULL;

        if (head) {
            head->prev = node;
        }

        head = node;

        return new_ptr;
    }

    Node *node = find_node_by_ptr(ptr);
    if (!node) {
        mem_errno = MEM_ERR_PTR_NOT_FOUND;
        return NULL;
    }

    void *new_ptr = realloc(ptr, size);
    if (!new_ptr) {
        mem_errno = MEM_ERR_REALLOC;
        return NULL;
    }

    unsigned int old_size = node->size;
    if (size > old_size) {
        unsigned int extra_bytes = size - old_size;
        void *start_of_new_memory = (char *)new_ptr + old_size;
        
        memset(start_of_new_memory, 0, extra_bytes);
    }
    
    node->ptr = new_ptr;
    node->size = size;

    return new_ptr;
}

int mem_free(void *ptr) {
    mem_errno = MEM_OK;

    Node *node = find_node_by_ptr(ptr);
    if (!node) {
        mem_errno = MEM_ERR_PTR_NOT_FOUND;
        return mem_errno;
    }

    if (node->prev)
        node->prev->next = node->next;
    else
        head = node->next;

    if (node->next)
        node->next->prev = node->prev;

    free(node->ptr);
    free(node);

    return 0;
}

void cleanup_memory() {
    Node *current = head;
    while (current) {
        Node *next = current->next;
        free(current->ptr);
        free(current);
        current = next;
    }
    head = NULL;
}

__attribute__((constructor))
static void memory_manager_initializer() {
    atexit(cleanup_memory);
}
