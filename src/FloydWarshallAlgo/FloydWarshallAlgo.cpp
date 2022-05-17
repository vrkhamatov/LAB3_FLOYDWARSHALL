using namespace std;
#include <string>
#include "../../headers/FloydWarshallAlgo/FloydWarshallAlgo.h"
#include <cfloat>


void configurationForStartMatrix(int size,double** matrix, double** pathMatrix){

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j)
            {
                pathMatrix[i][j] = i;
            }
            else if(matrix[i][j] == DBL_MAX)
            {
                pathMatrix[i][j] = DBL_MAX;
            }
            else
            {
                pathMatrix[i][j] = j;
            }
        }
    }

}

void FloydWarshall(Graph& graph, Graph& pathGraph)
{
    int size = graph.size;
    double** matrix = graph.matrix;
    double** pathMatrix = pathGraph.matrix;

    configurationForStartMatrix(size,matrix, pathMatrix);

    for (int k = 0; k < size; k++)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (i == j)
                {
                    matrix[i][j] = i;
                } else
                if (matrix[i][j] > (matrix[i][k] + matrix[k][j]))
                {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                    pathMatrix[i][j] = k;
                }
            }
        }
    }
}