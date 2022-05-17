#include "../../headers/FloydWarshallAlgo/FloydWarshallGraph.h"

#include <cfloat>

Graph::Graph(int size)
{
    this->size = size;


    matrix = new double* [size];

    for (int i = 0; i < size; i++)

    {

        matrix[i] = new double[size];

        for (int j = 0; j < size; j++)

            matrix[i][j] = DBL_MAX;
    }
}