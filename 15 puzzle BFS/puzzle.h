#pragma once

#include <stdio.h>
#include <iostream>
#include "node.h"
using namespace std;
#define n 4

class puzzle {
public:
    puzzle();
    puzzle(int squares[n][n], int goal[n][n]);
    void findEmpty(); // function to find the location of the empty tile
    void resetTiles();
    bool goalCheck();
    void BFS();
    int Hamming();
    void aStar();
    void print();
private:
    node arr[n][n];
    int tiles[n][n];
    int goalState[n][n];
    //arr[down][right]
    //arr[row][col]
    int x; int y; // i and j location for the empty tile (used for findEmpty() function)
};
