#ifndef GRAFO_H
#define GRAFO_H

#include <vector>

struct Vertice {
    int indice;
    int valor;
    Vertice* proximo;
};

struct Aresta {
    int fonte, destino;
};

class Grafo {

    private:
        Vertice **listaAdjacenciaVertices;
        int N, M; //quantidade de Vertices e quantidade de Arestas do Grafo
        Vertice* obtemVerticeAdjacente(int destino, Vertice* verticeFonte, int idadePessoa);
    public:
        Grafo(std::vector<Aresta> arestas, std::vector<int> idadePessoas, int quantidadeArestas, int quantidadeVertices);
        ~Grafo();
        void imprimeGrafo();
        Vertice** getListaAdjacenciaVertices();
        int getQuantidadeVertices();
        int getQuantidadeArestas();
};

#endif
