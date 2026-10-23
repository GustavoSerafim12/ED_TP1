#include "PilhaItems.h"

PilhaItems::PilhaItems(){
    id_items = new int[capacidade];
    topo = 0;
}

PilhaItems::~PilhaItems(){
    delete[] id_items;
}

void PilhaItems::Resize(){
    capacidade *= 2;
    int* aux = new int[capacidade];

    for(int i = 0; i<topo; i++){
        aux[i] = id_items[i];
    }

    delete[] id_items;
    id_items = aux;
}

void PilhaItems::Empilha(int id_item){
    if(topo == capacidade) Resize();

    id_items[topo] = id_item;
    topo++;
}

int PilhaItems::Desempilha(){
    if(topo == 0) throw "Pilha Vazia";
    topo--;
    return id_items[topo];
}

void PilhaItems::limpa(){
    topo = 0;
}

int PilhaItems::Tamanho(){
    return topo;
}

int PilhaItems::Acessar(int i){
    return id_items[i];
}