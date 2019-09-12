#include "Grafo.h"

Grafo::Grafo(Aresta* arestas, int quantidadeArestas, int quantidadeVertices) {
    N = quantidadeVertices;
    M = quantidadeArestas;
    listaAdjacenciaVertices = new Vertice*[N]();

    for(int i=0; i<N; i++) {
        listaAdjacenciaVertices[i] = nullptr;
    }

    for(int i=0; i<M; i++) {
        int fonte = arestas[i].fonte;
        int destino = arestas[i].destino;

        listaAdjacenciaVertices[fonte] = obtemVerticeAdjacente(destino, listaAdjacenciaVertices[fonte]);
    }
}

Grafo::~Grafo() {
    for(int i=0; i<N; i++) {
        delete[] listaAdjacenciaVertices[i];
    }
    delete listaAdjacenciaVertices;
}

Vertice* Grafo::obtemVerticeAdjacente(int destino, Vertice* verticeFonte) {
    Vertice* novoVertice = new Vertice;
    novoVertice->indice = destino;
    novoVertice->proximo = verticeFonte;
    return novoVertice;
}

Vertice** Grafo::getListaAdjacenciaVertices() {
    return listaAdjacenciaVertices;
}

int Grafo::getQuantidadeVertices() {
    return N;
}

int Grafo::getQuantidadeArestas() {
    return M;
}