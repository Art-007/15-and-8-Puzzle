#include "puzzle.h"

puzzle::puzzle() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr[i][j].setUpNull();
            arr[i][j].setDownNull();
            arr[i][j].setLeftNull();
            arr[i][j].setRightNull();
            arr[i][j].setValue(0);
            tiles[i][j] = 0;
        }
    }
}

puzzle::puzzle(int squares[n][n], int goal[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0) { //if we are on top row, up is null
                arr[i][j].setUpNull();
                arr[i][j].setDown(arr[i + 1][j]);
            }
            if (j == 0) { //if we are on left col, left is null
                arr[i][j].setLeftNull();
                arr[i][j].setRight(arr[i][j + 1]);
            }
            if (i > 0 && i < n - 1) { //set up and down for all in row 1
                arr[i][j].setUp(arr[i - 1][j]);
                arr[i][j].setDown(arr[i + 1][j]);
            }
            if (j > 0 && j < n - 1) { //set left and right for all in col 1
                arr[i][j].setLeft(arr[i][j - 1]);
                arr[i][j].setRight(arr[i][j + 1]);
            }
            if (i == n - 1) { //if we are on bottom row, down is null
                arr[i][j].setDownNull();
                arr[i][j].setUp(arr[i - 1][j]);
            }
            if (j == n - 1) { //if we are on right col, right is null 
                arr[i][j].setRightNull();
                arr[i][j].setLeft(arr[i][j - 1]);
            }
            arr[i][j].setValue(squares[i][j]);
            tiles[i][j] = squares[i][j];
            goalState[i][j] = goal[i][j];
        }
    }
}

void puzzle::findEmpty() {
    int emptyi = 0; int emptyj = 0;
    while (emptyi < n) { // nested while loop to find the location of the empty tile
        while (emptyj < n) {
            if (arr[emptyi][emptyj].getValue() == 0)
                goto found;
            emptyj++;
        }
        emptyj = 0;
        emptyi++;
    }
found:
    //cout << "Empty tile found at i = " << i << ", and j = " << j << endl;
    x = emptyi;
    y = emptyj;
}

void puzzle::resetTiles() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            tiles[i][j] = arr[i][j].getValue();
        }
    }
}

bool puzzle::goalCheck() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (tiles[i][j] != goalState[i][j])
                return false;
        }
    }
    return true;
}

void puzzle::BFS() {
    int tempTile = 0; //used to move tiles without erasing one of the tiles current values
    while (1) {
        findEmpty();
        if (arr[x][y].getUp() != NULL) {
            tempTile = arr[x - 1][y].getValue();
            tiles[x - 1][y] = 0;
            tiles[x][y] = tempTile;
            puzzle tempU(tiles, goalState);
            tempU.print();
            if (tempU.goalCheck())
                goto end;
            //tempU.BFS();
        }

        resetTiles();
        if (arr[x][y].getDown() != NULL) {
            tempTile = arr[x + 1][y].getValue();
            tiles[x + 1][y] = 0;
            tiles[x][y] = tempTile;
            puzzle tempD(tiles, goalState);
            tempD.print();
            if (tempD.goalCheck())
                goto end;
            //tempD.BFS();
        }

        resetTiles();
        if (arr[x][y].getLeft() != NULL) {
            tempTile = arr[x][y - 1].getValue();
            tiles[x][y - 1] = 0;
            tiles[x][y] = tempTile;
            puzzle tempL(tiles, goalState);
            tempL.print();
            if (tempL.goalCheck())
                goto end;
            //tempL.BFS();
        }

        resetTiles();
        if (arr[x][y].getRight() != NULL) {
            tempTile = arr[x][y + 1].getValue();
            tiles[x][y + 1] = 0;
            tiles[x][y] = tempTile;
            puzzle tempR(tiles, goalState);
            tempR.print();
            if (tempR.goalCheck())
                goto end;
            //tempR.BFS();
        }
        resetTiles();
        break;
    }
end: tempTile = 0;
}

int puzzle::Hamming() {
    int h = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i][j].getValue() > 0) {
                if (arr[i][j].getValue() != goalState[i][j])
                    h++;
            }
        }
    }
    return h;
}

void puzzle::aStar() {
    int tempTile = 0; //used to move tiles without erasing one of the tiles current values
    int hU = 100, hD = 100, hL = 100, hR = 100; //stores the hamming distance for each possible states
    //use a very large number (e.g. 100 in case the hamming distance isnt calculated in the if statements
    findEmpty();

    if (arr[x][y].getUp() != NULL) {
        tempTile = arr[x - 1][y].getValue();
        tiles[x - 1][y] = 0;
        tiles[x][y] = tempTile;
        puzzle tempU(tiles, goalState);
        //tempU.print();
        //cout << "Hamming Distance: " << tempU.Hamming() << endl << endl;
        hU = tempU.Hamming();
        if (hU == 0) {
            cout << "Hamming: " << hU << endl; tempU.print();
            return;
        }
    }

    resetTiles();
    if (arr[x][y].getDown() != NULL) {
        tempTile = arr[x + 1][y].getValue();
        tiles[x + 1][y] = 0;
        tiles[x][y] = tempTile;
        puzzle tempD(tiles, goalState);
        //tempD.print();
        //cout << "Hamming Distance: " << tempD.Hamming() << endl << endl;
        hD = tempD.Hamming();
        if (hD == 0) {
            cout << "Hamming: " << hD << endl; tempD.print();
            return;
        }
    }

    resetTiles();
    if (arr[x][y].getLeft() != NULL) {
        tempTile = arr[x][y - 1].getValue();
        tiles[x][y - 1] = 0;
        tiles[x][y] = tempTile;
        puzzle tempL(tiles, goalState);
        //tempL.print();
        //cout << "Hamming Distance: " << tempL.Hamming() << endl << endl;
        hL = tempL.Hamming();
        if (hL == 0) {
            cout << "Hamming: " << hL << endl; tempL.print();
            return;
        }
    }

    resetTiles();
    if (arr[x][y].getRight() != NULL) {
        tempTile = arr[x][y + 1].getValue();
        tiles[x][y + 1] = 0;
        tiles[x][y] = tempTile;
        puzzle tempR(tiles, goalState);
        //tempR.print();
        //cout << "Hamming Distance: " << tempR.Hamming() << endl << endl;
        hR = tempR.Hamming();
        if (hR == 0) {
            cout << "Hamming: " << hR << endl; tempR.print();
            return;
        }
    }

    resetTiles();
    if (hU <= hD)
        if (hU <= hL)
            if (hU <= hR) {
                tempTile = arr[x - 1][y].getValue();
                tiles[x - 1][y] = 0;
                tiles[x][y] = tempTile;
                puzzle shortest(tiles, goalState);
                cout << "Hamming: " << hU << endl; shortest.print();
                shortest.aStar();
            }
            else {
                tempTile = arr[x][y + 1].getValue();
                tiles[x][y + 1] = 0;
                tiles[x][y] = tempTile;
                puzzle shortest(tiles, goalState);
                cout << "Hamming: " << hR << endl; shortest.print();
                shortest.aStar();
            }
        else {
            if (hL <= hR) {
                tempTile = arr[x][y - 1].getValue();
                tiles[x][y - 1] = 0;
                tiles[x][y] = tempTile;
                puzzle shortest(tiles, goalState);
                cout << "Hamming: " << hL << endl; shortest.print();
                shortest.aStar();
            }
            else {
                tempTile = arr[x][y + 1].getValue();
                tiles[x][y + 1] = 0;
                tiles[x][y] = tempTile;
                puzzle shortest(tiles, goalState);
                cout << "Hamming: " << hR << endl; shortest.print();
                shortest.aStar();
            }
        }
    else {
        if (hD <= hL)
            if (hD <= hR) {
                tempTile = arr[x + 1][y].getValue();
                tiles[x + 1][y] = 0;
                tiles[x][y] = tempTile;
                puzzle shortest(tiles, goalState);
                cout << "Hamming: " << hD << endl; shortest.print();
                shortest.aStar();
            }
            else {
                tempTile = arr[x][y + 1].getValue();
                tiles[x][y + 1] = 0;
                tiles[x][y] = tempTile;
                puzzle shortest(tiles, goalState);
                cout << "Hamming: " << hR << endl; shortest.print();
                shortest.aStar();
            }
        else {
            if (hL <= hR) {
                tempTile = arr[x][y - 1].getValue();
                tiles[x][y - 1] = 0;
                tiles[x][y] = tempTile;
                puzzle shortest(tiles, goalState);
                cout << "Hamming: " << hL << endl; shortest.print();
                shortest.aStar();
            }
            else {
                tempTile = arr[x][y + 1].getValue();
                tiles[x][y + 1] = 0;
                tiles[x][y] = tempTile;
                puzzle shortest(tiles, goalState);
                cout << "Hamming: " << hR << endl; shortest.print();
                shortest.aStar();
            }
        }
    }
}

void puzzle::print() {
    for (int i = 0; i < n; i++) {
        cout << "[";
        for (int j = 0; j < n; j++) {
            if (arr[i][j].getValue() != 0)
                cout << " " << arr[i][j].getValue() << " ";
            else
                cout << "   ";
        }
        cout << "]" << endl;
    }
    cout << endl << endl;
    /*
    //remove later
    int temp = 0; // used to get value of the current tile
    int temp2 = 0; // used to get the value of neighboring tiles
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            temp = arr[i][j].getValue();

            //check if the current node has an up and print if it does
            if (arr[i][j].getUp() == NULL)
                cout << temp << "'s up is null" << endl;
            else {
                temp2 = arr[i - 1][j].getValue();
                cout << temp << "'s up is " << temp2 << endl;
            }

            //check if the current node has a down and print if it does
            if (arr[i][j].getDown() == NULL)
                cout << temp << "'s down is null" << endl;
            else {
                temp2 = arr[i + 1][j].getValue();
                cout << temp << "'s down is " << temp2 << endl;
            }

            //check if the current node has a left and print if it does
            if (arr[i][j].getLeft() == NULL)
                cout << temp << "'s left is null" << endl;
            else {
                temp2 = arr[i][j - 1].getValue();
                cout << temp << "'s left is " << temp2 << endl;
            }

            //check if the current node has a right and print if it does
            if (arr[i][j].getRight() == NULL)
                cout << temp << "'s right is null" << endl;
            else {
                temp2 = arr[i][j + 1].getValue();
                cout << temp << "'s right is " << temp2 << endl;
            }
            cout << endl;
        }
    }
    */
}
