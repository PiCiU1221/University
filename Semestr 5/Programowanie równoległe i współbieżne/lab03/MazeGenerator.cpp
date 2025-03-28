#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include "MazeGenerator.h"

Node::Node(int x, int y) : x(x), y(y) {}

MazeGenerator::MazeGenerator(int dim, int wallsToRemove)
        : dimension(dim), maze(dim, std::vector<int>(dim, -1)), wallsToRemove(wallsToRemove) {}

std::vector<std::vector<int>> MazeGenerator::generateMaze() {
    generatePaths();
    removeRandomWalls();
    return maze;
}

void MazeGenerator::generatePaths() {
    std::stack<Node> stack;
    stack.push(Node(1, 1));
    maze[1][1] = 0;

    while (!stack.empty()) {
        Node current = stack.top();
        stack.pop();

        std::vector<Node> neighbors = findNeighbors(current);
        if (!neighbors.empty()) {
            stack.push(current);
            Node next = neighbors[rand() % neighbors.size()];
            removeWall(current, next);
            maze[next.y][next.x] = 0;
            stack.push(next);
        }
    }
}

std::vector<Node> MazeGenerator::findNeighbors(const Node& node) {
    std::vector<Node> neighbors;
    std::vector<std::pair<int, int>> directions = { {0, -2}, {0, 2}, {-2, 0}, {2, 0} };

    for (const auto& dir : directions) {
        int newX = node.x + dir.first;
        int newY = node.y + dir.second;
        if (pointOnGrid(newX, newY) && maze[newY][newX] == -1) {
            neighbors.emplace_back(newX, newY);
        }
    }
    return neighbors;
}

bool MazeGenerator::pointOnGrid(int x, int y) const {
    return x >= 0 && y >= 0 && x < dimension && y < dimension;
}

void MazeGenerator::removeWall(const Node& current, const Node& next) {
    maze[(current.y + next.y) / 2][(current.x + next.x) / 2] = 0;
}

void MazeGenerator::removeRandomWalls() {
    for (int i = 0; i < wallsToRemove; i++) {
        if (!removeRandomWall()) {
            std::cout << "No more walls to remove safely.\n";
        }
    }
}

bool MazeGenerator::removeRandomWall() {
    std::vector<Node> wallPositions;
    for (int y = 1; y < dimension - 1; y++) {
        for (int x = 1; x < dimension - 1; x++) {
            if (maze[y][x] == -1 && hasExactlyTwoOppositePathNeighbors(x, y)) {
                wallPositions.emplace_back(x, y);
            }
        }
    }

    if (wallPositions.empty()) {
        return false;
    }

    auto randomWall = wallPositions[rand() % wallPositions.size()];
    maze[randomWall.y][randomWall.x] = 0;
    return true;
}

bool MazeGenerator::hasExactlyTwoOppositePathNeighbors(int x, int y) const {
    bool top = maze[y - 1][x] == 0;
    bool bottom = maze[y + 1][x] == 0;
    bool left = maze[y][x - 1] == 0;
    bool right = maze[y][x + 1] == 0;
    return (top && bottom && !left && !right) || (left && right && !top && !bottom);
}
