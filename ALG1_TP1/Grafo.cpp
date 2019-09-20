#include "Grafo.h"

Grafo::Grafo() = default;

Grafo::Grafo(vector<Aresta> arestas, vector<int> valoresVertices, int qtdArestas, int qtdVertices) {
    N = qtdVertices;
    M = qtdArestas;

    for(int i=0; i<N; i++) { //Inicializa vertices do grafo
        Vertice* novoVertice = new Vertice();
        novoVertice->indice = i+1;
        novoVertice->valor = valoresVertices[i];
        listaVertices.push_back(novoVertice);
    }

    for(int i=0; i<M; i++) { //Cria arestas do grafo por meio de lista de vertices adjacentes
        int fonte = arestas[i].fonte;
        int destino = arestas[i].destino;
        listaVertices[fonte - 1]->verticesAdjacentes.push_back(destino);
    }
}

void Grafo::imprimeGrafo() { // Imprime os vértices do grafo e seus adjacentes
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