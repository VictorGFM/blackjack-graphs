#include "Grafo.h"

Grafo::Grafo() = default;

Grafo::Grafo(vector<Aresta> arestas, vector<int> idadeAlunos, int quantidadeArestas, int quantidadeVertices) {
    N = quantidadeVertices;
    M = quantidadeArestas;

    for(int i=0; i<N; i++) {
        Vertice* novoVertice = new Vertice();
        novoVertice->indice = i+1;
        novoVertice->valor = idadeAlunos[i];
        listaVertices.push_back(novoVertice);
    }

    for(int i=0; i<M; i++) {
        int fonte = arestas[i].fonte;
        int destino = arestas[i].destino;
        listaVertices[fonte - 1]->verticesAdjacentes.push_back(destino);
    }
}

void Grafo::imprimeGrafo() {
    for(int i=0; i<N; i++) {
        cout << listaVertices[i]->indice << "(" << listaVertices[i]->valor << ")" << ": ";
        for(int j=0; j<listaVertices[i]->verticesAdjacentes.size(); j++) {
            cout << listaVertices[i]->verticesAdjacentes[j] << ";";
        }
        cout << endl;
    }
}

void Grafo::setListaVertices(vector<Vertice*> listaVertices) {
    this->listaVertices = listaVertices;
}

vector<Vertice*> Grafo::getListaVertices() {
    return listaVertices;
}

int Grafo::getQuantidadeVertices() {
    return N;
}

int Grafo::getQuantidadeArestas() {
    return M;
}