#include "Item.h"

Item::Item(int id_item, std::string nome): 
_id_item(id_item),
_nome(nome){}

int Item::GetId(){
    return _id_item;
}

std::string Item::GetNome(){
    return _nome;
}