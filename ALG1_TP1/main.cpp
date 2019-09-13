#include <iostream>
#include <fstream>
#include <sstream>
#include "Grafo.h"

std::vector<std::string> obtemVetorParametrosLinha(const std::string& linhaArquivo);

void executaSwap(Grafo *grafo, int comandante, int subordinado);

int main(int argc, char* argv[]) {
    std::vector<std::string> vetorParametrosLinha;

    std::string nomeArquivo = argv[1] == nullptr ? "equipe3.txt" : argv[1];
    std::ifstream arquivoEntrada;

    arquivoEntrada.open(nomeArquivo);
    if(!arquivoEntrada) {
        std::cout << "Erro ao tentar abrir o arquivo!" << std::endl;
    }

    std::vector<std::string> vetorLinhasArquivo;
    std::string linhaArquivo;
    while(getline(arquivoEntrada, linhaArquivo)) {
        vetorLinhasArquivo.push_back(linhaArquivo);
    }

    vetorParametrosLinha = obtemVetorParametrosLinha(vetorLinhasArquivo[0]);

    int quantidadePessoasTime = std::stoi(vetorParametrosLinha[0]);
    int quantidadeRelacoesDiretas = std::stoi(vetorParametrosLinha[1]);
    int quantidadeInstrucoes = std::stoi(vetorParametrosLinha[2]);

    std::vector<int> vetorIdadePessoas;
    vetorParametrosLinha = obtemVetorParametrosLinha(vetorLinhasArquivo[1]);
    for(std::string i : vetorParametrosLinha) {
        vetorIdadePessoas.push_back(std::stoi(i));
    }

    std::vector<Aresta> vetorArestas;
    for(int i=0; i<quantidadeRelacoesDiretas; i++) {
        vetorParametrosLinha = obtemVetorParametrosLinha(vetorLinhasArquivo[i+2]);
        Aresta aresta = {std::stoi(vetorParametrosLinha[0]), std::stoi(vetorParametrosLinha[1])};
        vetorArestas.push_back(aresta);
    }

    Grafo grafo(vetorArestas, vetorIdadePessoas, quantidadeRelacoesDiretas, quantidadePessoasTime);
    grafo.imprimeGrafo();
    for(int i=0; i<quantidadeInstrucoes; i++) {
        int indiceInicialLinhaInstrucoes = 2+quantidadeRelacoesDiretas;
        vetorParametrosLinha = obtemVetorParametrosLinha(vetorLinhasArquivo[indiceInicialLinhaInstrucoes+i]);
        if(vetorParametrosLinha[0] == "S") {
            executaSwap(&grafo, std::stoi(vetorParametrosLinha[1]), std::stoi(vetorParametrosLinha[2]));
        } else if(vetorParametrosLinha[0] == "C") {
            executaCommander();
        } else if(vetorParametrosLinha[0] == "M") {
            executaMeeting();
        }
    }

    return 0;
}

void executaSwap(Grafo *grafo, int comandante, int subordinado) {
    Grafo grafoSimulacao = *grafo;
    Vertice **listaAdjacenciaVertices = grafoSimulacao.getListaAdjacenciaVertices();
    while(listaAdjacenciaVertices[comandante]->proximo != nullptr) {
        if(listaAdjacenciaVertices[comandante]->proximo->indice == subordinado) {
            //remove vertice subordinado
            //adiciona comandante como subordinado
        }
    }
}

std::vector<std::string> obtemVetorParametrosLinha(const std::string& linhaArquivo) {
    std::vector<std::string> vetorParametrosLinha;
    std::istringstream iss(linhaArquivo);
    for(std::string linhaArquivo; iss >> linhaArquivo; ) {
        vetorParametrosLinha.push_back(linhaArquivo);
    }
    return vetorParametrosLinha;
}
