#ifndef AVENTUREIRO_H
#define AVENTUREIRO_H

#include <string>
#include "PilhaItems.h"

class Aventureiro{
private:
    int _id_aventureiro;
    std::string _nome;

public:
    Aventureiro(int id_aventureiro, std::string nome);
    Aventureiro();
    
    ~Aventureiro() = default;
    int GetId();
    std::string GetNome();

    PilhaItems Inventario;
};

#endif
