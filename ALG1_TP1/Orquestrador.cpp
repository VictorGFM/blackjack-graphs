#include "Orquestrador.h"
#include <algorithm>
#include <list>
#include <stack>

bool isVerticesAdjacentes(Grafo *grafo, int alunoA, int alunoB, int &comandante, int &comandado);
void trocaVerticesAlunos(Grafo *grafo, int comandante, int comandado);
bool contemCiclo(Grafo *grafo);
bool verificaCicloDFS(int verticeAtual, bool verticesVisitados[], bool pilhaRecursividade[], Grafo *grafo);
void criaOrdenadacaoTopologica(int verticeAtual, bool verticesVisitados[], stack<int>* pilha, Grafo grafo);
Grafo transporGrafo(Grafo grafo);
void defineComandanteMaisJovem(Grafo &grafo, bool *verticesVisitados, list<int> &filaComandantes,
                               Grafo &grafoTransposto, int &menorIdade, int &comandanteMaisJovem);

//Realiza comando SWAP.
void executaSwap(Grafo *grafo, int alunoA, int alunoB) {
    int comandante, comandado;

    //verifica se alunoA e alunoB são adjacentes
    if(!isVerticesAdjacentes(grafo, alunoA, alunoB, comandante, comandado)) {
        cout << "S N" << endl;
        return;
    }

    //realiza troca entre alunos e verifica se foi gerado um ciclo no grafo, desfazendo a troca em caso positivo
    trocaVerticesAlunos(grafo, comandante, comandado);
    if(contemCiclo(grafo)) {
        trocaVerticesAlunos(grafo, comandado, comandante);
        cout << "S N" << endl;
    } else {
        cout << "S T" << endl;
    }

}

//Verifica se vertices são adjacentes.
bool isVerticesAdjacentes(Grafo *grafo, int alunoA, int alunoB, int &comandante, int &comandado) {
    bool verticesAdjacentes = true;
    vector<int> comandadosAlunoA = grafo->getListaVertices()[alunoA - 1]->verticesAdjacentes;
    vector<int> comandadosAlunoB = grafo->getListaVertices()[alunoB - 1]->verticesAdjacentes;

    if(find(comandadosAlunoA.begin(), comandadosAlunoA.end(), alunoB) != comandadosAlunoA.end()) {
        comandante = alunoA;
        comandado = alunoB;
    } else if(find(comandadosAlunoB.begin(), comandadosAlunoB.end(), alunoA) != comandadosAlunoB.end()) {
        comandante = alunoB;
        comandado = alunoA;
    } else {
        verticesAdjacentes = false;
    }

    return verticesAdjacentes;
}

//Verifica se grafo possui ciclo realizando uma DFS com uso de pilha recursiva.
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

//Funcao recursiva que realiza DFS no grafo, retornando se esse é ciclico ou não.
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

//Realiza troca entre dois vertices do grafo.
void trocaVerticesAlunos(Grafo *grafo, int comandante, int comandado) {
    vector<int>* listaAdjacenciaComandante = &grafo->getListaVertices()[comandante - 1]->verticesAdjacentes;
    vector<int>* listaAdjacenciaComandado = &grafo->getListaVertices()[comandado - 1]->verticesAdjacentes;

    listaAdjacenciaComandante->erase(remove(listaAdjacenciaComandante->begin(), listaAdjacenciaComandante->end(), comandado),
                                    listaAdjacenciaComandante->end());
    listaAdjacenciaComandado->push_back(comandante);
}

//Realiza comando COMMANDER.
void executaCommander(Grafo grafo, int aluno) {
    int qtdVertices = grafo.getQuantidadeVertices();
    bool verticesVisitados[qtdVertices];
    int menorIdade = INT32_MAX, comandanteMaisJovem = -1;
    list<int> filaComandantes;

    //Inicializa todos vertices como nao visitado
    for(int i=0; i<qtdVertices; i++) {
        verticesVisitados[i] = false;
    }
    verticesVisitados[aluno-1] = true;
    filaComandantes.push_back(aluno);

    //Gera grafo transposto
    Grafo grafoTransposto = transporGrafo(grafo);

    //Percorre grafo transposto a fim de achar o comandante mais jovem de um aluno.
    defineComandanteMaisJovem(grafo, verticesVisitados, filaComandantes, grafoTransposto, menorIdade,
                              comandanteMaisJovem);

    if(comandanteMaisJovem == -1 || comandanteMaisJovem == aluno) {
        cout << "C *" << endl;
    } else {
        cout << "C " << menorIdade << endl;
    }

}

//Retorna grafo transposto.
Grafo transporGrafo(Grafo grafo) {
    Grafo grafoTransposto;
    vector<Vertice*> listaVerticesTransposta;
    for(int i=0; i<grafo.getQuantidadeVertices(); i++) {
        listaVerticesTransposta.push_back(new Vertice(*grafo.getListaVertices()[i]));
        listaVerticesTransposta[i]->verticesAdjacentes.clear();
    }
    grafoTransposto.setListaVertices(listaVerticesTransposta);

    for(int i=0; i<grafo.getQuantidadeVertices(); i++) {
        for(int j=0; j<grafo.getListaVertices()[i]->verticesAdjacentes.size(); j++) {
            grafoTransposto.getListaVertices()[grafo.getListaVertices()[i]->verticesAdjacentes[j]-1]->verticesAdjacentes.push_back(i+1);
        }
    }
    return grafoTransposto;
}

//Busca comandante mais jovem de aluno ao percorrer grafo transposto.
void defineComandanteMaisJovem(Grafo &grafo, bool *verticesVisitados, list<int> &filaComandantes,
                               Grafo &grafoTransposto, int &menorIdade, int &comandanteMaisJovem) {
    int alunoAtual;
    while(!filaComandantes.empty()) {
        alunoAtual = filaComandantes.front();
        filaComandantes.pop_front();

        if(grafo.getListaVertices()[alunoAtual - 1]->valor < menorIdade || comandanteMaisJovem == -1) {
            menorIdade = grafo.getListaVertices()[alunoAtual - 1]->valor;
            comandanteMaisJovem = alunoAtual;
        }

        for(auto i : grafoTransposto.getListaVertices()[alunoAtual-1]->verticesAdjacentes) {
            if(!verticesVisitados[i-1]) {
                verticesVisitados[i-1] = true;
                filaComandantes.push_back(i);
            }
        }
    }
}

//Realiza comando MEETING.
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

//Ordena vertices do grafo por meio de ordem topologica em uma pilha.
void criaOrdenadacaoTopologica(int verticeAtual, bool verticesVisitados[], stack<int>* pilha, Grafo grafo) {
    verticesVisitados[verticeAtual] = true;

    for(auto i : grafo.getListaVertices()[verticeAtual]->verticesAdjacentes) {
        if(!verticesVisitados[i-1]) {
            criaOrdenadacaoTopologica(i-1, verticesVisitados, pilha, grafo);
        }
    }

    pilha->push(verticeAtual);
}
