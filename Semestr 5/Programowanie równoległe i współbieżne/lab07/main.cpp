#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <omp.h>

using namespace std;

enum Move { LEFT, RIGHT, UP, DOWN };

vector<vector<int>> labyrinth;
vector<vector<omp_lock_t>> labyrinth_mutex;

int unique_tid = 1;
omp_lock_t tid_mutex;

void printLabyrinth() {
    for (const auto& row : labyrinth) {
        for (const auto& value : row) {
            printf("%2d ", value);
        }
        cout << endl;
    }
}

void loadMatrixFromFile() {
    ifstream file("board.txt");

    string line;

    while (getline(file, line)) {
        vector<int> row;
        stringstream ss(line);
        string value;

        while (getline(ss, value, ';')) {
            row.push_back(stoi(value));
        }

        labyrinth.push_back(row);
    }

    file.close();

    omp_init_lock(&tid_mutex);

    for (size_t i = 0; i < labyrinth.size(); ++i) {
        vector<omp_lock_t> row_mutexes(labyrinth[i].size());
        for (size_t j = 0; j < row_mutexes.size(); ++j) {
            omp_init_lock(&row_mutexes[j]);
        }
        labyrinth_mutex.push_back(std::move(row_mutexes));
    }
}

pair<int, int> getRandomZeroPosition() {
    srand(time(0));

    int rows = labyrinth.size();
    int cols = labyrinth[0].size();

    const int maxAttempts = 1000;

    for (int attempt = 0; attempt < maxAttempts; ++attempt) {
        int randomRow = rand() % rows;
        int randomCol = rand() % cols;

        if (labyrinth[randomRow][randomCol] == 0) {
            return {randomRow, randomCol};
        }
    }

    return {1,1};
}

pair<int, int> getNewCoordinates(int x, int y, Move move) {
    switch (move) {
        case LEFT:
            return {x, y - 1};
        case RIGHT:
            return {x, y + 1};
        case UP:
            return {x - 1, y};
        case DOWN:
            return {x + 1, y};
        default:
            return {x, y};
    }
}

void thread_function(int tid, int x, int y) {
    int possibleMovesCount;

    do {
        omp_set_lock(&labyrinth_mutex[x][y]);
        if (labyrinth[x][y] == 0) {
            labyrinth[x][y] = tid;
        }
        omp_unset_lock(&labyrinth_mutex[x][y]);

        vector<Move> possibleMoves;

        // lewo
        omp_set_lock(&labyrinth_mutex[x][y - 1]);
        if (labyrinth[x][y-1] == 0) {
            possibleMoves.push_back(LEFT);
        }
        omp_unset_lock(&labyrinth_mutex[x][y - 1]);

        // prawo
        omp_set_lock(&labyrinth_mutex[x][y + 1]);
        if (labyrinth[x][y+1] == 0) {
            possibleMoves.push_back(RIGHT);
        }
        omp_unset_lock(&labyrinth_mutex[x][y + 1]);

        //gora
        omp_set_lock(&labyrinth_mutex[x - 1][y]);
        if (labyrinth[x-1][y] == 0) {
            possibleMoves.push_back(UP);
        }
        omp_unset_lock(&labyrinth_mutex[x - 1][y]);

        // dol
        omp_set_lock(&labyrinth_mutex[x + 1][y]);
        if (labyrinth[x+1][y] == 0) {
            possibleMoves.push_back(DOWN);
        }
        omp_unset_lock(&labyrinth_mutex[x + 1][y]);

        possibleMovesCount = possibleMoves.size();

        if (possibleMovesCount > 1) {
            #pragma omp parallel for
            for (int i = 0; i < possibleMovesCount - 1; i++) {
                pair<int, int> newCoordinates = getNewCoordinates(x, y, possibleMoves.at(i));

                int new_tid;
                omp_set_lock(&tid_mutex);
                new_tid = unique_tid++;
                omp_unset_lock(&tid_mutex);

                #pragma omp task
                {
                    thread_function(new_tid, newCoordinates.first, newCoordinates.second);
                }
            }
        }

        if (possibleMovesCount >= 1) {
            pair<int, int> newCoordinates = getNewCoordinates(x, y, possibleMoves.at(possibleMovesCount - 1));

            x = newCoordinates.first;
            y = newCoordinates.second;
        }
    } while (possibleMovesCount != 0);


}

tuple<int, int, int> generateRandomColor() {
    return {rand() % 256, rand() % 256, rand() % 256};
}

void createPPMFile(const string& filename, int scale) {
    ofstream ppmFile(filename);

    int height = labyrinth.size();
    int width = labyrinth[0].size();

    ppmFile << "P3\n";
    ppmFile << width * scale << " " << height * scale << "\n";
    ppmFile << "255\n";

    unordered_map<int, tuple<int, int, int>> colorMap;
    colorMap[-1] = {0, 0, 0};

    for (const auto& row : labyrinth) {
        for (int i = 0; i < scale; ++i) {
            for (const auto& value : row) {
                if (value > 0 && colorMap.find(value) == colorMap.end()) {
                    colorMap[value] = generateRandomColor();
                }

                auto color = colorMap[value];
                int r = get<0>(color);
                int g = get<1>(color);
                int b = get<2>(color);

                for (int j = 0; j < scale; ++j) {
                    ppmFile << r << " " << g << " " << b << " ";
                }
            }
            ppmFile << "\n";
        }
    }

    ppmFile.close();
}

int main() {
    // z pliku
    loadMatrixFromFile();
    //printLabyrinth();

    pair<int, int> randomStartPos = getRandomZeroPosition();
    int x = randomStartPos.first;
    int y = randomStartPos.second;

    #pragma omp parallel
    {
        #pragma omp single
        {
            thread_function(unique_tid++, x, y);
        }
    }

    omp_destroy_lock(&tid_mutex);

    for (size_t i = 0; i < labyrinth_mutex.size(); ++i) {
        for (size_t j = 0; j < labyrinth_mutex[i].size(); ++j) {
            omp_destroy_lock(&labyrinth_mutex[i][j]);
        }
    }

    cout << "\nCompleted labyrinth" << endl;
    //printLabyrinth();
    createPPMFile("output_image.ppm", 3);

    return 0;
}