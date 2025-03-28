#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

#include <vector>
#include <stack>
#include <utility>

class Node {
public:
    int x, y;
    Node(int x, int y);
};

class MazeGenerator {
public:
    MazeGenerator(int dim, int wallsToRemove);
    std::vector<std::vector<int>> generateMaze();

private:
    int dimension;
    int wallsToRemove;
    std::vector<std::vector<int>> maze;

    void generatePaths();
    std::vector<Node> findNeighbors(const Node& node);
    bool pointOnGrid(int x, int y) const;
    void removeWall(const Node& current, const Node& next);
    void removeRandomWalls();
    bool removeRandomWall();
    bool hasExactlyTwoOppositePathNeighbors(int x, int y) const;
};

#endif // MAZE_GENERATOR_H
