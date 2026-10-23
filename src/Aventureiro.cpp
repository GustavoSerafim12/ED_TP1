#include "Aventureiro.h"

Aventureiro::Aventureiro(int id_aventureiro, std::string nome):
    _id_aventureiro(id_aventureiro),
    _nome(nome){}

int Aventureiro::GetId(){
    return _id_aventureiro;
}

std::string Aventureiro::GetNome(){
    return _nome;
}