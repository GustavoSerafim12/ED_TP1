#ifndef FILAENCOMENDA_H
#define FILAENCOMENDA_H

#include "Encomenda.h"
#define MAXTAM_INITIAL 4

class FilaEncomenda {
private:
    int capacidade = MAXTAM_INITIAL;
    Encomenda* Encomendas;
    int inicio, tamanho;

    void Resize();
    
public:
    FilaEncomenda();
    ~FilaEncomenda();
    FilaEncomenda(const FilaEncomenda& copia) = delete;
    FilaEncomenda& operator=(const FilaEncomenda& copy) = delete;

    void Adicionar(Encomenda entrada);
    Encomenda Remover();
    bool Vazia();
    int Tamanho();
};

#endif
