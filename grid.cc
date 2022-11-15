#include "grid.h"

#include <unistd.h>

#include <iostream>

#include "function.h"
#include "node.h"

Grid::Grid(int size_x, int size_y, int initial_x, int initial_y, int final_x,
           int final_y, bool heuristica) {
  std::vector<char> vector_secundario;
  vector_secundario.resize(size_x, '*');
  grid_.resize(size_y);
  for (int i{0}; i < grid_.size(); ++i) {
    grid_[i] = vector_secundario;
  }
  initial_x_ = --initial_x;
  initial_y_ = --initial_y;
  final_x_ = --final_x;
  final_y_ = --final_y;
  grid_[initial_x][initial_y] = 'I';
  grid_[final_x][final_y] = 'F';
  heuristica_ = heuristica;
}

void Grid::Print(std::string filename, Node node) {
  std::ofstream output(filename);
  for (int i{-5}; i <= 5; ++i) {
    for (int j{-5}; j <= 5; ++j) {
      if (node.GetX() + i >= 0 && node.GetX() + i < grid_.size() &&
          node.GetY() + j >= 0 && node.GetY() + j < grid_[0].size()) {
        output << grid_[node.GetX() + i][node.GetY() + j];
      } else {
        output << ' ';
      }
    }
    output << std::endl;
  }
  output << "X: " << node.GetX() + 1 << " Y: " << node.GetY() + 1 << std::endl;
  output << "Nodos generados: "<<nodos_generados - 1<<std::endl;
  output << "Nodos analizados: "<<nodos_analizados + 1 <<std::endl;
}

void Grid::PrintWhole(std::string filename) {
  std::ofstream output(filename);
  for (int i{0}; i < grid_.size(); ++i) {
    for (int j{0}; j < grid_[0].size(); ++j) {
      output << grid_[i][j];
    }
    output << std::endl;
  }
}

void Grid::Recorrido(int initial_x, int initial_y, int final_x, int final_y) {
  int x_coche = initial_x - 1, y_coche = initial_y - 1;
  std::string salida = "salida.txt";
  std::cout << "Escribe el camino" << std::endl;
  int ayuda1, ayuda2;
  while (x_coche != final_x - 1 || y_coche != final_y - 1) {
    std::cout << "x y = ";
    std::cin >> ayuda1;
    std::cin >> ayuda2;
    --ayuda1;
    --ayuda2;
    if (((ayuda1 == x_coche + 1 || ayuda1 == x_coche ||
          ayuda1 == x_coche - 1) &&
         (ayuda2 == y_coche + 1 || ayuda2 == y_coche ||
          ayuda2 == y_coche - 1)) &&
        (ayuda1 >= 0 && ayuda2 >= 0 && ayuda1 < grid_.size() &&
         ayuda2 < grid_[0].size())) {
      x_coche = ayuda1;
      y_coche = ayuda2;
      grid_[x_coche][y_coche] = 'O';
      // Print(salida);
      std::cout << "Camino recorrido en el punto " << x_coche + 1 << " "
                << y_coche + 1 << std::endl;
    } else {
      std::cout << "ERROR, introduzca un numero valido" << std::endl;
    }
  }
  std::cout << "\nSe ha llegado al punto final" << std::endl;
}

void Grid::AStar(bool fast_mode) {
  std::vector<Node> frontier;
  Node node(initial_x_, initial_y_, heuristica_);
  node.SetFather(&node);
  if (fast_mode) {
    Print("salida.txt", node);
  }
  frontier.push_back(node);
  int pasos{0};
  while (true) {
    ChooseMinorValue(frontier);
    node = frontier[frontier.size() - 1];
    frontier.pop_back();
    frontier.clear();
    grid_[node.GetX()][node.GetY()] = 'O';
    if (node.GetX() == final_x_ && node.GetY() == final_y_) {
      break;
    } else {
      for (int i{-1}; i <= 1; ++i) {
        for (int j{-1}; j <= 1; ++j) {
          if (!(i == j || i == -j)) {
              if (node.GetX() + i >= 0 && node.GetY() + j >= 0 &&
                node.GetX() + i < grid_.size() &&
                node.GetY() + j < grid_[0].size()) {
                Node aux(node.GetX() + i, node.GetY() + j, &node, heuristica_);
                frontier.push_back(aux);
                ++nodos_generados;
              }
          }
        }
      }
    }
    if (fast_mode) {
      usleep(1000000);
      Print("salida.txt", node);
    }
    ++nodos_analizados;
  }
  if (fast_mode) {
    PrintWhole("salida.txt");
  }
}