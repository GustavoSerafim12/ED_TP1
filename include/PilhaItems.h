#ifndef PILHAITEMS_H
#define PILHAITEMS_H
#define MAXTAM 2

class PilhaItems{
private:
    int* id_items;
    int topo;
    int capacidade = MAXTAM;
    void Resize();

public:
    PilhaItems();
    ~PilhaItems();
    PilhaItems(const PilhaItems& copia) = delete;
    PilhaItems& operator=(const PilhaItems& copia) = delete;

    void Empilha(int id_item);
    int Desempilha();

    void limpa();
    int Tamanho();
    // item da posição i (0 é a base), sem desempilhar
    int Acessar(int i);
};

#endif
