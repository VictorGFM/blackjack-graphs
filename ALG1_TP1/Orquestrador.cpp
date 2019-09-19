#include "Orquestrador.h"
#include <algorithm>
#include <list>
#include <stack>

void trocaVerticesAlunos(Grafo *grafo, int comandante, int comandado);

bool contemCiclo(Grafo *grafo);

bool verificaCicloDFS(int verticeAtual, bool verticesVisitados[], bool pilhaRecursividade[], Grafo *grafo);

void criaOrdenadacaoTopologica(int verticeAtual, bool verticesVisitados[], stack<int>* pilha, Grafo grafo);

void executaSwap(Grafo *grafo, int alunoA, int alunoB) {
    int comandante, comandado;
    vector<int> comandadosAlunoA = grafo->getListaVertices()[alunoA - 1]->verticesAdjacentes;
    vector<int> comandadosAlunoB = grafo->getListaVertices()[alunoB - 1]->verticesAdjacentes;

    if(find(comandadosAlunoA.begin(), comandadosAlunoA.end(), alunoB) != comandadosAlunoA.end()) {
        comandante = alunoA;
        comandado = alunoB;
    } else if(find(comandadosAlunoB.begin(), comandadosAlunoB.end(), alunoA) != comandadosAlunoB.end()) {
        comandante = alunoB;
        comandado = alunoA;
    } else {
        cout << "S N" << endl;
        return;
    }

    trocaVerticesAlunos(grafo, comandante, comandado);

    if(contemCiclo(grafo)) {
        trocaVerticesAlunos(grafo, comandado, comandante);
        cout << "S N" << endl;
    } else {
        cout << "S T" << endl;
    }

}

bool contemCiclo(Grafo *grafo) {
    int qtdVertices = grafo->getQuantidadeVertices();
    bool verticesVisitados[qtdVertices], pilhaRecursiva[qtdVertices];
    for(int i=0; i<qtdVertices; i++) {
        verticesVisitados[i] = false;
        pilhaRecursiva[i] = false;
    }

    for(int i=0; i<qtdVertices; i++) {
        if(verificaCicloDFS(i, verticesVisitados, pilhaRecursiva, grafo)) {
            return true;
        }
    }

    return false;
}

bool verificaCicloDFS(int verticeAtual, bool verticesVisitados[], bool pilhaRecursividade[], Grafo *grafo) {
    if(!verticesVisitados[verticeAtual]) {
        verticesVisitados[verticeAtual] = true;
        pilhaRecursividade[verticeAtual] = true;

        for(auto i : grafo->getListaVertices()[verticeAtual]->verticesAdjacentes) {
            if(!verticesVisitados[i-1] && verificaCicloDFS(i-1, verticesVisitados, pilhaRecursividade, grafo)) {
                return true;
            } else if (pilhaRecursividade[i-1]) {
                return true;
            }
        }

    }
    pilhaRecursividade[verticeAtual] = false;
    return false;
}

void trocaVerticesAlunos(Grafo *grafo, int comandante, int comandado) {
    vector<int>* listaAdjacenciaComandante = &grafo->getListaVertices()[comandante - 1]->verticesAdjacentes;
    vector<int>* listaAdjacenciaComandado = &grafo->getListaVertices()[comandado - 1]->verticesAdjacentes;

    listaAdjacenciaComandante->erase(remove(listaAdjacenciaComandante->begin(), listaAdjacenciaComandante->end(), comandado),
                                    listaAdjacenciaComandante->end());
    listaAdjacenciaComandado->push_back(comandante);
}

void executaCommander(Grafo *grafo, int aluno) {
    cout << "commander" << endl;
}

void executaMeeting(Grafo grafo) {
    int qtdVertices = grafo.getQuantidadeVertices();
    stack<int> pilha;
    bool verticesVisitados[qtdVertices];

    for(int i=0; i<qtdVertices; i++) {
        verticesVisitados[i] = false;
    }

    for(int i=0; i<qtdVertices; i++) {
        if(!verticesVisitados[i]) {
            criaOrdenadacaoTopologica(i, verticesVisitados, &pilha, grafo);
        }
    }

    cout << "M";
    while(!pilha.empty()) {
        cout << " " << pilha.top()+1;
        pilha.pop();
    }
}

void criaOrdenadacaoTopologica(int verticeAtual, bool verticesVisitados[], stack<int>* pilha, Grafo grafo) {
    verticesVisitados[verticeAtual] = true;

    for(auto i : grafo.getListaVertices()[verticeAtual]->verticesAdjacentes) {
        if(!verticesVisitados[i-1]) {
            criaOrdenadacaoTopologica(i-1, verticesVisitados, pilha, grafo);
        }
    }

    pilha->push(verticeAtual);
}
