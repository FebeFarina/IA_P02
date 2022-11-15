#ifndef NODE_H
#define NODE_H

#include <math.h>

//static int final_x_;
//static int final_y_;

class Node{
 public:
  Node(int x, int y, bool heuristica);
  Node(int x, int y, Node* father, bool heuristica);
  static void SetFinal(int x, int y) {
    final_x_ = --x;
    final_y_ = --y;
  }
  int GetX() const { return x_; }
  int GetY() const { return y_; }
  int GetValue() const { return value_; }
  int GetCost() const { return cost_; }
  Node* GetFather() const { return father_; }
  void SetFather(Node* father) { father_ = father; }
 private:
  int x_;
  int y_;
  double value_;
  int cost_;
  Node* father_;
  static int final_x_;
  static int final_y_;
};

#endif