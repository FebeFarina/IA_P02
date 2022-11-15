#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>
#include <fstream>
#include "node.h"

class Grid{
 public:
  Grid(int size_x, int size_y, int initial_x, int initial_y, int final_x, int final_y, bool heuristica);
  void Print(std::string filename, Node node);
  void PrintWhole(std::string filename);
  void Recorrido(int initial_x, int initial_y, int final_x, int final_y);
  void AStar(bool fast_mode);
  int GetNodosGenerados() {return nodos_generados;}
  int GetNodosAnalizados() {return nodos_analizados;}
  void SwitchHeuristic() {heuristica_ = !heuristica_;}
  void ResetNodes() {nodos_generados = 0; nodos_analizados = 0;}
 private: 
  std::vector<std::vector<char>> grid_;
  int initial_x_;
  int initial_y_;
  int final_x_;
  int final_y_;
  bool heuristica_;
  int nodos_generados{0};
  int nodos_analizados{0};
};

#endif