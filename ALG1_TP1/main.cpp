#include <iostream>
#include "Grafo.h"

int main() {
    /*
    Aresta* edges = new Aresta();
    edges[0] = { 0, 1 };
    edges[1] = { 1, 2 };
    edges[2] = { 2, 0 };
    edges[3] = { 2, 1 };
    edges[4] = { 3, 2 };
    edges[5] = { 4, 5 };
    edges[6] = { 5, 4 };
*/
    Aresta edges[] =
            {
                    // pair (x, y) represents edge from x to y
                    { 0, 1 }, { 1, 2 }, { 2, 0 }, { 2, 1 },
                    { 3, 2 }, { 4, 5 }, { 5, 4 }
            };

    // Number of vertices in the graph
    int N = 6;

    // calculate number of edges
    int M = sizeof(edges)/sizeof(edges[0]);

    // construct graph
    Grafo grafo(edges, M, N);

    // print adjacency list representation of graph
    for (int i = 0; i < N; i++)
    {
        // print given vertex
        std::cout << i << " --";

        // print all its neighboring vertices
        Vertice* ptr = grafo.getListaAdjacenciaVertices()[i];
        while (ptr != nullptr)
        {
            std::cout << " -> " << ptr->indice << " ";
            ptr = ptr->proximo;
        }
        std::cout << std::endl;
    }

    return 0;
}