#include "node.h"
node::node() {
    up = NULL;
    down = NULL;
    left = NULL;
    right = NULL;
    value = 0;
}

node::node(node* up, node* down, node* left, node* right, int value) {
    this->up = up;
    this->down = down;
    this->left = left;
    this->right = right;
    this->value = value;
}
node* node::getUp() {
    return up;
}

node* node::getDown() {
    return down;
}

node* node::getLeft() {
    return left;
}

node* node::getRight() {
    return right;
}

int node::getValue() {
    return value;
}

void node::setUp(node u) {
    up = &u;
}

void node::setDown(node d) {
    down = &d;
}

void node::setLeft(node l) {
    left = &l;
}

void node::setRight(node r) {
    right = &r;
}

void node::setUpNull() {
    this->up = NULL;
}

void node::setDownNull() {
    this->down = NULL;
}

void node::setLeftNull() {
    this->left = NULL;
}

void node::setRightNull() {
    this->right = NULL;
}


void node::setValue(int value) {
    this->value = value;
}
