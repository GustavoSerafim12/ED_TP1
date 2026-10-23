#include "Atributo.h"

Atributo::Atributo(int id_atributo, std::string nome): 
_id_atributo(id_atributo),
_nome(nome){}

int Atributo::GetId(){
    return _id_atributo;
}

std::string Atributo::GetNome(){
    return _nome;
}