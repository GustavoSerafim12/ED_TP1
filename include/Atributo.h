#ifndef ATRIBUTO_H
#define ATRIBUTO_H
#include <string>

class Atributo{
    private:
        int _id_atributo;
        std::string _nome;
    public:
        Atributo(int id_atributo, std::string nome);
        Atributo();
        ~Atributo() = default;
        int GetId();
        std::string GetNome();
};

#endif
