#ifndef GRAPH_H
#define GRAPH_H

using namespace std;
#include <string>
#include "../list/list.h"
#include "../flights/flights.h"
#include "../redBlackTree/map.h"
#include "FloydWarshallGraph.h"

void configurationForStartMatrix(int size,double** matrix, double** SecondMatrix);

void FloydWarshall(Graph&, Graph&);

#endif