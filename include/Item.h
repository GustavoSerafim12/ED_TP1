#ifndef ITEM_H
#define ITEM_H
#include <string>

class Item{
    private:
        int _id_item;
        std::string _nome;
    public:
        Item(int id_item, std::string nome);
        Item();
        ~Item() = default;
        int GetId();
        std::string GetNome();
};

#endif
