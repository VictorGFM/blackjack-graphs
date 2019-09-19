#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <vector>

using namespace std;

struct Vertice {
    int indice;
    int valor;
    vector<int> verticesAdjacentes;
};

struct Aresta {
    int fonte, destino;
};

class Grafo {

    private:
        vector<Vertice*> listaVertices;
        int N, M; //quantidade de Vertices e quantidade de Arestas do Grafo respectivamente.
    public:
        Grafo(vector<Aresta> arestas, vector<int> idadeAlunos, int quantidadeArestas, int quantidadeVertices);
        void imprimeGrafo();
        vector<Vertice*> getListaVertices();
        int getQuantidadeVertices();
        int getQuantidadeArestas();
};

#endif
