#ifndef GRAFO_H
#define GRAFO_H

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
        int N, M; //quantidade de Vertices e quantidade de Arestas do Grafopublic
        Vertice* obtemVerticeAdjacente(int destino, Vertice* verticeFonte);
    public:
        Grafo(Aresta* arestas, int quantidadeArestas, int quantidadeVertices);
        ~Grafo();
        Vertice** getListaAdjacenciaVertices();
        int getQuantidadeVertices();
        int getQuantidadeArestas();
};

#endif
