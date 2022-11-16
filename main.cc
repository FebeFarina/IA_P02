#include <iostream>
#include <iomanip>

#include "grid.h"
#include "node.h"

int Node::final_x_ = 0;
int Node::final_y_ = 0;
int main()
{
  int opcion;
  while (opcion != 3)
  {
    system("clear");
    std::cout << "¿Bienvenido! ¿Que desea hacer?" << std::endl;
    std::cout << "1. Recorrido A*" << std::endl;
    std::cout << "2. Evaluación de funciones" << std::endl;
    std::cout << "3. Salir" << std::endl;
    std::cout << "> ";
    std::cin >> opcion;
    if (opcion == 1)
    {
      system("clear");
      std::cout << "Introduzca el tamaño de la cuadrícula (x, y): ";
      int size_x, size_y;
      std::cin >> size_x >> size_y;
      std::cout << "Introduzca la posición inicial (x, y): ";
      int initial_x, initial_y;
      std::cin >> initial_y >> initial_x;
      if (initial_y > size_x || initial_x > size_y)
      {
        std::cout << "Error, la posicion inicial no esta dentro de la rejilla"
                  << std::endl;
        return 0;
      }
      std::cout << "Introduzca la posición final (x, y): ";
      int final_x, final_y;
      std::cin >> final_y >> final_x;
      if (final_y > size_x || final_x > size_y)
      {
        std::cout << "Error, la posicion inicial no esta dentro de la rejilla"
                  << std::endl;
        return 0;
      }
      Node::SetFinal(final_x, final_y);
      std::cout << std::endl
                << "¿Qué heurística desea utilizar?" << std::endl;
      std::cout << "1. Manhattan" << std::endl;
      std::cout << "2. Euclídea" << std::endl;
      std::cout << "> ";
      int heuristica;
      std::cin >> heuristica;
      bool heuristica_bool;
      if (heuristica == 1)
      {
        heuristica_bool = true;
      }
      else
      {
        heuristica_bool = false;
      }
      Grid grid(size_x, size_y, initial_x, initial_y, final_x, final_y,
                heuristica_bool);
      system("clear");
      std::cout << "Dirijase al fichero salida.txt para ver el resultado y "
                   "pulse enter para iniciar el algoritmo...";
      std::cin.ignore();
      std::cin.get();
      grid.AStar(true);
      std::cout << "¿Desea realizar otro recorrido con la otra heurística?"
                << std::endl;
      std::cout << "1. Sí" << std::endl;
      std::cout << "2. No" << std::endl;
      int otro_recorrido;
      std::cin >> otro_recorrido;
      if (otro_recorrido == 1)
      {
        heuristica_bool = !heuristica_bool;
        Grid grid(size_x, size_y, initial_x, initial_y, final_x, final_y,
                  heuristica_bool);
        system("clear");
        std::cout << "Dirijase al fichero salida.txt para ver el resultado y "
                     "pulse enter para iniciar el algoritmo...";
        std::cin.ignore();
        std::cin.get();
        grid.AStar(true);
        std::cout << "Pulse enter para continuar...";
        std::cin.ignore();
        std::cin.get();
      }
    }
    else if (opcion == 2)
    {
      system("clear");
      std::cout<<"se van a generar 5 tablas para comparar sus recorridos.\n"
      <<"¿quiere generar 5 tablas con valores aleatorios o desea introducirlos manualmente?\n"
      <<"1. Aleatorio\n"
      <<"2. Manual"<<std::endl;
      int random_option;
      std::cin >> random_option;
      bool random = true;
      if (random_option == 1)
      {
        random = true;
      }
      else
      {
        random = false;
      }
      if(random == true){
      srand(time(NULL));
      std::vector<int> result;
      int generados1{0}, generados2{0}, analizados1{0}, analizados2{0};
      std::ofstream output("salida.txt");
      output << std::left << std::setw(8) << "Rejilla";
      output << std::left << std::setw(13) << "Nodo inicial";
      output << std::left << std::setw(12) << "Nodo final";
      output << std::left << std::setw(18) << "Nodos A Manhattan";
      output << std::left << std::setw(18) << "Nodos G Manhattan";
      output << std::left << std::setw(18) << "Nodos A Euclidea";
      output << std::left << std::setw(18) << "Nodos G Euclidea" << std::endl;
      for (int i{0}; i < 5; ++i)
      {
        int random_x_initial = rand() % 100 + 1;
        int random_y_initial = rand() % 100 + 1;
        int random_x_final = rand() % 100 + 1;
        int random_y_final = rand() % 100 + 1;
        Node::SetFinal(random_x_final, random_y_final);
        Grid grid(100, 100, random_x_initial, random_y_initial, random_x_final,
                  random_y_final, true);
        //std::cout << random_x_initial << " " << random_y_initial << " " << random_x_final << " " << random_y_final << std::endl;
        grid.AStar(false);
        analizados1 = grid.GetNodosAnalizados();
        generados1 = grid.GetNodosGenerados();
        grid.SwitchHeuristic();
        grid.ResetNodes();
        grid.AStar(false);
        analizados2 = grid.GetNodosAnalizados();
        generados2 = grid.GetNodosGenerados();

        output << std::left << std::setw(8) << i + 1;
        output << std::left << std::setw(1) << "(" << std::setw(3) << random_y_initial << std::setw(2) << ", " << std::setw(3) << random_x_initial << std::setw(4) << ")";
        output << std::left << std::setw(1) << "(" << std::setw(3) << random_y_final << std::setw(2) << ", " << std::setw(3) << random_x_final << std::setw(3) << ")";
        output << std::left << std::setw(18) << analizados1+1;
        output << std::left << std::setw(18) << generados1;
        output << std::left << std::setw(18) << analizados2+1;
        output << std::left << std::setw(18) << generados2 << std::endl;
      }
      std::cout << "Tabla de resultados en salida.txt. Pulse enter para continuar...";
      std::cin.ignore();
      std::cin.get();
      }
      else{
      std::vector<int> result;
      int generados1{0}, generados2{0}, analizados1{0}, analizados2{0};
      std::ofstream output("salida.txt");
      output << std::left << std::setw(8) << "Rejilla";
      output << std::left << std::setw(13) << "Nodo inicial";
      output << std::left << std::setw(12) << "Nodo final";
      output << std::left << std::setw(18) << "Nodos A Manhattan";
      output << std::left << std::setw(18) << "Nodos G Manhattan";
      output << std::left << std::setw(18) << "Nodos A Euclidea";
      output << std::left << std::setw(18) << "Nodos G Euclidea" << std::endl;
      for (int i{0}; i < 5; ++i)
      {       
        system("clear");
        std::cout << "Introduzca el tamaño de la cuadrícula (x, y): ";
        int size_x, size_y;
      std::cin >> size_x >> size_y;
        std::cout<<"introduzca la posicion inicial (x,y)"<<std::endl;
        int random_x_initial;
        int random_y_initial;
        std::cin >> random_y_initial >> random_x_initial;
        std::cout<<"introduzca la posicion final (x,y)"<<std::endl;
        int random_x_final;
        int random_y_final;
        std::cin >> random_y_final >> random_x_final;
        Node::SetFinal(random_x_final, random_y_final);
        Grid grid(size_x, size_y, random_x_initial, random_y_initial, random_x_final,
                  random_y_final, true);
        //std::cout << random_x_initial << " " << random_y_initial << " " << random_x_final << " " << random_y_final << std::endl;
        grid.AStar(false);
        analizados1 = grid.GetNodosAnalizados();
        generados1 = grid.GetNodosGenerados();
        grid.SwitchHeuristic();
        grid.ResetNodes();
        grid.AStar(false);
        analizados2 = grid.GetNodosAnalizados();
        generados2 = grid.GetNodosGenerados();

        output << std::left << std::setw(8) << i + 1;
        output << std::left << std::setw(1) << "(" << std::setw(3) << random_y_initial << std::setw(2) << ", " << std::setw(3) << random_x_initial << std::setw(4) << ")";
        output << std::left << std::setw(1) << "(" << std::setw(3) << random_y_final << std::setw(2) << ", " << std::setw(3) << random_x_final << std::setw(3) << ")";
        output << std::left << std::setw(18) << analizados1;
        output << std::left << std::setw(18) << generados1;
        output << std::left << std::setw(18) << analizados2;
        output << std::left << std::setw(18) << generados2 << std::endl;
      }
      std::cout << "Tabla de resultados en salida.txt. Pulse enter para continuar...";
      std::cin.ignore();
      std::cin.get();
      }
    }
  }
}