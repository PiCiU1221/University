#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <mutex>
#include <unordered_map>
#include "MazeGenerator.h"

using namespace std;

enum Move {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

vector<vector<int>> labyrinth;
vector<vector<mutex>> labyrinth_mutex;

int unique_tid = 1;
mutex tid_mutex;

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

    for (size_t i = 0; i < labyrinth.size(); ++i) {
        vector<mutex> row_mutexes(labyrinth[i].size());
        labyrinth_mutex.push_back(move(row_mutexes));
    }
}

void generateLabyrinth(int dimension, int wallsToRemove) {
    labyrinth.resize(dimension, vector<int>(dimension, -1));

    MazeGenerator mazeGen(dimension, wallsToRemove);
    labyrinth = mazeGen.generateMaze();

    for (size_t i = 0; i < labyrinth.size(); ++i) {
        vector<mutex> row_mutexes(labyrinth[i].size());
        labyrinth_mutex.push_back(move(row_mutexes));
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
    vector<thread> threads;
    int possibleMovesCount;

    do {
        labyrinth_mutex[x][y].lock();
        if (labyrinth[x][y] == 0) {
            labyrinth[x][y] = tid;
        }
        labyrinth_mutex[x][y].unlock();

        vector<Move> possibleMoves;

        // lewo
        labyrinth_mutex[x][y-1].lock();
        if (labyrinth[x][y-1] == 0) {
            possibleMoves.push_back(LEFT);
        }
        labyrinth_mutex[x][y-1].unlock();

        // prawo
        labyrinth_mutex[x][y+1].lock();
        if (labyrinth[x][y+1] == 0) {
            possibleMoves.push_back(RIGHT);
        }
        labyrinth_mutex[x][y+1].unlock();

        //gora
        labyrinth_mutex[x-1][y].lock();
        if (labyrinth[x-1][y] == 0) {
            possibleMoves.push_back(UP);
        }
        labyrinth_mutex[x-1][y].unlock();

        // dol
        labyrinth_mutex[x+1][y].lock();
        if (labyrinth[x+1][y] == 0) {
            possibleMoves.push_back(DOWN);
        }
        labyrinth_mutex[x+1][y].unlock();

        possibleMovesCount = possibleMoves.size();

        if (possibleMovesCount > 1) {
            for (int i = 0; i < possibleMovesCount - 1; i++) {
                pair<int, int> newCoordinates = getNewCoordinates(x, y, possibleMoves.at(i));

                tid_mutex.lock();
                threads.push_back(thread(thread_function, unique_tid++, newCoordinates.first, newCoordinates.second));
                tid_mutex.unlock();
            }
        }

        if (possibleMovesCount >= 1) {
            pair<int, int> newCoordinates = getNewCoordinates(x, y, possibleMoves.at(possibleMovesCount - 1));

            x = newCoordinates.first;
            y = newCoordinates.second;
        }
    } while (possibleMovesCount != 0);

    for (auto &t : threads) {
        t.join();
    }
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
    //loadMatrixFromFile();

    // generowane
    int dimension = 501;
    // dimension musi byc nieparzyste
    if (dimension % 2 == 0) dimension++;
    int wallsToRemove = 200;
    generateLabyrinth(dimension, wallsToRemove);

    //printLabyrinth();

    pair<int, int> randomStartPos = getRandomZeroPosition();
    int x = randomStartPos.first;
    int y = randomStartPos.second;

    thread starting_thread (thread_function, unique_tid++, x, y);

    starting_thread.join();

    cout << "\nCompleted labyrinth" << endl;
    //printLabyrinth();
    createPPMFile("output_image.ppm", 3);

    return 0;
}