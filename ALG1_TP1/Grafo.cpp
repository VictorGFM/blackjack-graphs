#include "Grafo.h"
#include <iostream>

Grafo::Grafo(std::vector<Aresta> arestas, std::vector<int> idadePessoas, int quantidadeArestas, int quantidadeVertices) {
    N = quantidadeVertices;
    M = quantidadeArestas;
    this->listaAdjacenciaVertices = new Vertice*[N]();

    for(int i=0; i<N; i++) {
        listaAdjacenciaVertices[i] = new Vertice();
        listaAdjacenciaVertices[i]->indice = i+1;
        listaAdjacenciaVertices[i]->valor = idadePessoas[i];
        listaAdjacenciaVertices[i]->proximo = nullptr;
    }

    for(int i=0; i<M; i++) {
        int fonte = arestas[i].fonte;
        int destino = arestas[i].destino;

        listaAdjacenciaVertices[fonte-1]->proximo = obtemVerticeAdjacente(destino, listaAdjacenciaVertices[fonte-1]->proximo,
                                                                 idadePessoas[destino-1]);
    }
}

Grafo::~Grafo() {
    for(int i=0; i<N; i++) {
        delete[] listaAdjacenciaVertices[i];
    }
    delete listaAdjacenciaVertices;
}

Vertice* Grafo::obtemVerticeAdjacente(int destino, Vertice* verticeFonte, int idadePessoa) {
    Vertice* novoVertice = new Vertice;
    novoVertice->indice = destino;
    novoVertice->valor = idadePessoa;
    novoVertice->proximo = verticeFonte;
    return novoVertice;
}

void Grafo::imprimeGrafo() {
    for(int i=0; i<N; i++) {
        std::cout << listaAdjacenciaVertices[i]->indice << "(" << listaAdjacenciaVertices[i]->valor << ")" << ": ";
        while(listaAdjacenciaVertices[i]->proximo != nullptr) {
            std::cout << listaAdjacenciaVertices[i]->proximo->indice << "("
            << listaAdjacenciaVertices[i]->proximo->valor << ")" << ";";
            listaAdjacenciaVertices[i] = listaAdjacenciaVertices[i]->proximo;
        }
        std::cout << std::endl;
    }
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