#include "FilaEncomenda.h"

FilaEncomenda::FilaEncomenda(){
    Encomendas = new Encomenda[capacidade];
    inicio = 0;
    tamanho = 0;
}

FilaEncomenda::~FilaEncomenda(){
    delete[] Encomendas;
}

int FilaEncomenda::Tamanho(){
    return tamanho;
}

bool FilaEncomenda::Vazia(){
    return tamanho == 0;
}

void FilaEncomenda::Adicionar(Encomenda entrada){
    if(tamanho == capacidade){
        Resize();
    }

    int fim = (inicio + tamanho) % capacidade;
    Encomendas[fim] = entrada;
    tamanho++;
}

Encomenda FilaEncomenda::Remover(){
    if(Vazia()) throw "Fila Vazia";

    Encomenda aux = Encomendas[inicio];
    inicio = (inicio + 1) % capacidade;
    tamanho--;
    return aux;
}

void FilaEncomenda::Resize(){
    int capacidade_nova = capacidade*2;
    Encomenda* aux = new Encomenda[capacidade_nova];

    for(int i = 0; i<tamanho; i++){
        int j = (inicio + i) % capacidade;
        aux[i] = Encomendas[j];    
    }

    delete[] Encomendas;
    Encomendas = aux;
    inicio = 0;
    capacidade = capacidade_nova;
}