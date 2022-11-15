#include "node.h"
#include <iostream>

Node::Node(int x, int y, bool heuristica) {
    x_ = x;
    y_ = y;
    cost_ = 0;
    father_ = NULL;
    if (heuristica) {
        value_ = abs(final_x_ - x_) + abs(final_y_ - y_);
    } else {
        value_ = sqrt(pow(final_x_ - x_, 2) + pow(final_y_ - y_, 2));
    }
}

Node::Node(int x, int y, Node* father, bool heuristica) {
    x_ = x;
    y_ = y;
    father_ = father;
    cost_ = father->GetCost() + 1;
    if (heuristica) {
        value_ = abs(final_x_ - x_) + abs(final_y_ - y_) + cost_;
    } else {
        value_ = sqrt(pow((final_x_ - x_), 2) + pow((final_y_ - y_), 2)) + cost_;
    }
}
