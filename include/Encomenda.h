#ifndef ENCOMENDA_H
#define ENCOMENDA_H

class Encomenda{
    private:
        int _id_aventureiro;
        int _id_item;
    public:
        Encomenda(int id_aventureiro, int id_item);
        Encomenda();
        ~Encomenda() = default;

        int GetIdAventureiro();
        int GetIdItem();
};

#endif
