#include <iostream>
#include "Grafo.h"
#include "Orquestrador.h"

void obtemVetorIdadeAlunos(int qtdAlunosTime, vector<int> &vetorIdadeAlunos);

void obtemVetorArestas(int qtdRelacoesDiretas, vector<Aresta> &vetorArestas);

void executaInstrucoes(int qtdInstrucoes, Grafo &grafo);

int main() {
    int qtdAlunosTime, qtdRelacoesDiretas, qtdInstrucoes;

    cin >> qtdAlunosTime >> qtdRelacoesDiretas >> qtdInstrucoes;

    vector<int> vetorIdadeAlunos;
    obtemVetorIdadeAlunos(qtdAlunosTime, vetorIdadeAlunos);

    vector<Aresta> vetorArestas;
    obtemVetorArestas(qtdRelacoesDiretas, vetorArestas);

    Grafo grafo(vetorArestas, vetorIdadeAlunos, qtdRelacoesDiretas, qtdAlunosTime);
    grafo.imprimeGrafo();

    executaInstrucoes(qtdInstrucoes, grafo);

    return 0;
}

void executaInstrucoes(int qtdInstrucoes, Grafo &grafo) {
    for(int i=0; i < qtdInstrucoes; i++) {
        string tipoInstrucao;
        cin >> tipoInstrucao;
        if(tipoInstrucao == "S") {
            int alunoA, alunoB;
            cin >> alunoA >> alunoB;
            executaSwap(&grafo, alunoA, alunoB);
        } else if(tipoInstrucao == "C") {
            int aluno;
            cin >> aluno;
            executaCommander(grafo, aluno);
        } else if(tipoInstrucao == "M") {
            executaMeeting(grafo);
        }
    }
}

void obtemVetorIdadeAlunos(int qtdAlunosTime, vector<int> &vetorIdadeAlunos) {
    for(int i=0; i < qtdAlunosTime; i++) {
        int idade;
        cin >> idade;
        vetorIdadeAlunos.push_back(idade);
    }
}

void obtemVetorArestas(int qtdRelacoesDiretas, vector<Aresta> &vetorArestas) {
    for(int i=0; i < qtdRelacoesDiretas; i++) {
        int fonte, origem;
        cin >> fonte >> origem;
        Aresta aresta = {fonte, origem};
        vetorArestas.push_back(aresta);
    }
}