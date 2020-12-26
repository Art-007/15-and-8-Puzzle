#pragma once
#include <iostream>
#include <stdio.h>
using namespace std;

class node {
public:
    node();
    node(node* up, node* down, node* left, node* right, int value);
    node* getUp();
    node* getDown();
    node* getLeft();
    node* getRight();
    int getValue();
    void setUp(node u);
    void setDown(node d);
    void setLeft(node l);
    void setRight(node r);
    void setUpNull();
    void setDownNull();
    void setLeftNull();
    void setRightNull();
    void setValue(int value);
private:
    node* up;
    node* down;
    node* left;
    node* right;
    int value;
};

