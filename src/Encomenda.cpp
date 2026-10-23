#include "Encomenda.h"

Encomenda::Encomenda(int id_aventureiro, int id_item):
_id_aventureiro(id_aventureiro),
_id_item(id_item){}

Encomenda::Encomenda(){
    _id_aventureiro = -1;
    _id_item = -1;
}

int Encomenda::GetIdAventureiro(){
    return _id_aventureiro;
}

int Encomenda::GetIdItem(){
    return _id_item;
}