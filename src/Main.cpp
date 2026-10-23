#include "Atributo.h"
#include "Aventureiro.h"
#include "Catalogo.h"
#include "Consulta.h"
#include "Encomenda.h"
#include "EsparsaL.h"
#include "EsparsaT.h"
#include "FilaEncomenda.h"
#include "Item.h"
#include "ListaObjeto.h"
#include "Ordenacao.h"
#include "PilhaItems.h"
#include <iostream>
#include <sstream>

int main(){
    ListaObjeto<Atributo> Atributos;
    ListaObjeto<Aventureiro> Aventureiros;
    ListaObjeto<Item> Items;

    Catalogo Cat;
    FilaEncomenda Fila;

    std::string entrada = "";
    while(std::cin >> entrada){

        if(entrada == "E"){
            char modo;
            std::cin >> modo;
            Cat.MudaModo(modo);

            std::cout << "E " << modo << std::endl;
        }

        else if(entrada == "A"){

            Cat.AdicionaColuna();

            std::string nome_atributo;
            std::cin >> nome_atributo;
            int id_atributo = Atributos.Tamanho();
            Atributo *atr = new Atributo(id_atributo, nome_atributo);
            Atributos.Adicionar(atr);

            std::cout << "A " << id_atributo << std::endl;
        }

        else if(entrada == "I"){

            Cat.AdicionaLinha();

            std::string nome_item;
            std::cin >> nome_item;
            int id_item = Items.Tamanho();
            Item *it = new Item(id_item, nome_item);
            Items.Adicionar(it);

            std::cout << "I " << id_item << std::endl;
        }

        else if(entrada == "M"){
            int id_atributo, id_item, valor;
            std::cin >> id_item >> id_atributo >> valor;
            Cat.Set(id_item, id_atributo, valor);

            std::cout << "M "
            << Items.Acessar(id_item)->GetNome() << " "
            << Atributos.Acessar(id_atributo)->GetNome() << " "
            << valor << std::endl;
        }

        else if(entrada == "H"){
            std::string nome_aventureiro;
            std::cin >> nome_aventureiro;
            int id_aventureiro = Aventureiros.Tamanho();
            Aventureiro *av = new Aventureiro(id_aventureiro, nome_aventureiro);
            Aventureiros.Adicionar(av);

            std::cout << "H " << id_aventureiro << std::endl;
        }

        else if(entrada == "F"){
            int id_aventureiro, id_item;
            std::cin >> id_aventureiro >> id_item;
            Encomenda enc = Encomenda(id_aventureiro, id_item);
            Fila.Adicionar(enc);

            std::cout << "F " << Fila.Tamanho() << std::endl;
        }

        else if(entrada == "Z"){
            int k_turnos;
            std::cin >> k_turnos;
            
            int n_forjadas = 0;
            std::stringstream buffer;

            for(int i = 0; i<k_turnos; i++){
                if(Fila.Vazia()) break;

                Encomenda enc = Fila.Remover();
                int id_aventureiro = enc.GetIdAventureiro();
                int id_item = enc.GetIdItem();
                Aventureiro *av = Aventureiros.Acessar(id_aventureiro);
                av->Inventario.Empilha(id_item);

                n_forjadas++;
                if(n_forjadas > 1) buffer << " ";
                buffer << "encomenda_" << n_forjadas
                <<  " " << id_aventureiro
                << " " << id_item;
            }

            std::cout << "Z " << n_forjadas << std::endl;
            if(n_forjadas > 0)
            std::cout << buffer.str() << std::endl;
        }

        else if(entrada == "D"){
            int id_aventureiro;
            std::cin >> id_aventureiro;
            Aventureiro *av = Aventureiros.Acessar(id_aventureiro);

            std::cout << "D " << av->GetNome() << " ";
            if(av->Inventario.Tamanho() == 0){
                std::cout << "VAZIO" << std::endl;
            }
            else{
                int id_item = av->Inventario.Desempilha();
                std::cout << Items.Acessar(id_item)->GetNome() << std::endl;
            }
        }

        else if(entrada == "LI"){
            int id_item;
            std::cin >> id_item;
            ConsultaLI(Cat, Items, id_item);
        }

        else if(entrada == "LA"){
            int id_atributo;
            std::cin >> id_atributo;
            ConsultaLA(Cat, Atributos, id_atributo);
        }

        else if(entrada == "LH"){
            int id_aventureiro;
            std::cin >> id_aventureiro;
            ConsultaLH(Cat, *Aventureiros.Acessar(id_aventureiro));
        }

        else if(entrada == "Q"){
            int id_aventureiro, n, m;
            std::cin >> id_aventureiro >> n >> m;

            // m pares (métrica, peso)
            std::string *metricas = new std::string[m];
            double *pesos = new double[m];
            for(int j = 0; j<m; j++){
                std::cin >> metricas[j] >> pesos[j];
            }

            ConsultaQ(Cat, *Aventureiros.Acessar(id_aventureiro), n, m, metricas, pesos);

            delete[] metricas;
            delete[] pesos;
        }
    }

    return 0;
}