#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>

#include "node.h"
#include "grid.h"
#include "time.h"
#include "stdlib.h"

void ChooseMinorValue(std::vector<Node> &vector)
{
  double minor = vector[0].GetValue();
  int position = 0;
  for (int i{0}; i < vector.size(); ++i)
  {
    if (vector[i].GetValue() <= minor)
    {
      minor = vector[i].GetValue();
      position = i;
    }
  }
  Node aux = vector[position];
  vector[position] = vector[vector.size() - 1];
  vector[vector.size() - 1] = aux;
}

#endif