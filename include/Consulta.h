#ifndef CONSULTA_H
#define CONSULTA_H

#include <string>
#include "Catalogo.h"
#include "ListaObjeto.h"
#include "Item.h"
#include "Atributo.h"
#include "Aventureiro.h"

void ConsultaLI(Catalogo& cat, ListaObjeto<Item>& itens, int id_item);
void ConsultaLA(Catalogo& cat, ListaObjeto<Atributo>& atributos, int id_atr);

// soma as linhas de todos os itens da pilha (com repetição), sem desempilhar
void CalculaBuild(Catalogo& cat, Aventureiro& av, long long* build, int T);

void ConsultaLH(Catalogo& cat, Aventureiro& av);
void ConsultaQ(Catalogo& cat, Aventureiro& av, int n, int m,
               std::string* metricas, double* pesos);

#endif
