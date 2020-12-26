#include "node.h"
#include "puzzle.h"
#include <iostream>
#include <stdio.h>
using namespace std;
// n is defined in puzzle.h

int main() {
    int tiles[n][n] = { {2, 8, 3}, {1, 6, 4}, {7, 0, 5} };
    int goal[n][n] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 0} };
    puzzle p1(tiles, goal);
    cout << "Initial State:" << endl;
    p1.print();
    p1.aStar();
    return 0;
}