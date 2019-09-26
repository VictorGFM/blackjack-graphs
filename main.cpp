#include <iostream>
#include <fstream>
#include <sstream>
#include "Grafo.h"
#include "Gerenciador.h"

ifstream obtemArquivoEntrada(char *argv[]);
void obtemLinhasArquivo(ifstream &arquivoEntrada, vector<string> &vetorLinhasArquivo);
vector<string> obtemVetorParametrosLinha(const string& linhaArquivo);
void obtemParametrosIniciais(const string& linhaArquivo, int &qtdAlunosTime, int &qtdRelacoesDiretas, int &qtdInstrucoes);
void obtemVetorIdadeAlunos(vector<int> &vetorIdadeAlunos, const string& linhaArquivo);
void obtemVetorArestas(int qtdRelacoesDiretas, vector<Aresta> &vetorArestas, vector<string> vetorLinhasArquivo);
void executaInstrucoes(Grafo &grafo, int qtdInstrucoes, int qtdRelacoesDiretas, vector<string> vetorLinhasArquivo);

int main(int argc, char *argv[]) {
    vector<string> vetorParametrosLinha;
    vector<int> vetorIdadeAlunos;
    vector<Aresta> vetorArestas;

    //Verifica se argumento com nome do arquivo de entrada foi informado como parametro.
    if(argv[1] == nullptr) {
        cout << "Parametro de arquivo de entrada nao informado!";
        return 1;
    }

    //Cria arquivo e verifica se foi aberto corretamente.
    ifstream arquivoEntrada = obtemArquivoEntrada(argv);
    if(!arquivoEntrada) {
        cout << "Erro ao tentar abrir o arquivo!" << endl;
        return 1;
    }

    //Obtem vetor com todas as linhas do arquivo de entrada lidas.
    vector<string> vetorLinhasArquivo;
    obtemLinhasArquivo(arquivoEntrada, vetorLinhasArquivo);
    if(vetorLinhasArquivo.empty()) return 0;

    //Obtem parametros iniciais informados na primeira linha do arquivo.
    int qtdAlunosTime, qtdRelacoesDiretas, qtdInstrucoes;
    obtemParametrosIniciais(vetorLinhasArquivo[0], qtdAlunosTime, qtdRelacoesDiretas, qtdInstrucoes);
    if(qtdAlunosTime == 0) return 0;

    //Obtem vetor com a idade dos alunos.
    obtemVetorIdadeAlunos(vetorIdadeAlunos, vetorLinhasArquivo[1]);

    //Obtem as arestas de relacionamento entre os alunos.
    obtemVetorArestas(qtdRelacoesDiretas, vetorArestas, vetorLinhasArquivo);

    //Cria e inicializa grafo com os alunos e seus relacionamentos.
    Grafo grafo(vetorArestas, vetorIdadeAlunos, qtdRelacoesDiretas, qtdAlunosTime);

    //Executa instrucoes informadas no arquivo de entrada.
    executaInstrucoes(grafo, qtdInstrucoes, qtdRelacoesDiretas, vetorLinhasArquivo);

    return 0;
}

void obtemParametrosIniciais(const string& linhaArquivo, int &qtdAlunosTime, int &qtdRelacoesDiretas, int &qtdInstrucoes) {
    vector<string> vetorParametrosLinha = obtemVetorParametrosLinha(linhaArquivo);
    qtdAlunosTime= stoi(vetorParametrosLinha[0]);
    qtdRelacoesDiretas= stoi(vetorParametrosLinha[1]);
    qtdInstrucoes= stoi(vetorParametrosLinha[2]);

}

void obtemLinhasArquivo(ifstream &arquivoEntrada, vector<string> &vetorLinhasArquivo) {
    string linhaArquivo;
    while(getline(arquivoEntrada, linhaArquivo)) {
        vetorLinhasArquivo.push_back(linhaArquivo);
    }
}

ifstream obtemArquivoEntrada(char *argv[]) {
    string nomeArquivo = argv[1];
    ifstream arquivoEntrada;
    arquivoEntrada.open(nomeArquivo);
    return arquivoEntrada;
}

void executaInstrucoes(Grafo &grafo, int qtdInstrucoes, int qtdRelacoesDiretas, vector<string> vetorLinhasArquivo) {
    for(int i=0; i < qtdInstrucoes; i++) {
        int indiceInicialLinhaInstrucoes = 2 + qtdRelacoesDiretas;
        vector<string> vetorParametrosLinha = obtemVetorParametrosLinha(vetorLinhasArquivo[indiceInicialLinhaInstrucoes+i]);
        string tipoInstrucao = vetorParametrosLinha[0];
        if(tipoInstrucao == "S") {
            int alunoA = stoi(vetorParametrosLinha[1]);
            int alunoB = stoi(vetorParametrosLinha[2]);
            executaSwap(&grafo, alunoA, alunoB);
        } else if(tipoInstrucao == "C") {
            int aluno = stoi(vetorParametrosLinha[1]);
            executaCommander(grafo, aluno);
        } else if(tipoInstrucao == "M") {
            executaMeeting(grafo);
        }
    }
}

void obtemVetorIdadeAlunos(vector<int> &vetorIdadeAlunos, const string& linhaArquivo) {
    vector<string> vetorParametrosLinha = obtemVetorParametrosLinha(linhaArquivo);
    for(const string& idade : vetorParametrosLinha) {
        vetorIdadeAlunos.push_back(stoi(idade));
    }
}

void obtemVetorArestas(int qtdRelacoesDiretas, vector<Aresta> &vetorArestas, vector<string> vetorLinhasArquivo) {
    for(int i=0; i < qtdRelacoesDiretas; i++) {
        vector<string> vetorParametrosLinha = obtemVetorParametrosLinha(vetorLinhasArquivo[i+2]);
        Aresta aresta = {stoi(vetorParametrosLinha[0]), stoi(vetorParametrosLinha[1])};
        vetorArestas.push_back(aresta);
    }
}

vector<string> obtemVetorParametrosLinha(const string& linhaArquivo) {
    vector<string> vetorParametrosLinha;
    istringstream iss(linhaArquivo);
    for(string linha; iss >> linha; ) {
        vetorParametrosLinha.push_back(linha);
    }
    return vetorParametrosLinha;
}
