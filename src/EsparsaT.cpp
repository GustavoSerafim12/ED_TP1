#include "EsparsaT.h"

EsparsaT::EsparsaT(){
    _itens = new int[capacidade];
    _atributos = new int[capacidade];
    _valores = new int[capacidade];
    tamanho = 0;
    percorridas = 0;
}

EsparsaT::~EsparsaT(){
    delete[] _itens;
    delete[] _atributos;
    delete[] _valores;
}

int EsparsaT::Get(int id_item, int id_atributo){
    int p = Busca(id_item, id_atributo);

    if(p < tamanho && _itens[p] == id_item && _atributos[p] == id_atributo){
        return _valores[p];
    }

    return 0;
}

void EsparsaT::Set(int id_item, int id_atributo, int valor){
    int p = Busca(id_item, id_atributo);
    bool existe = (p < tamanho && _itens[p] == id_item && _atributos[p] == id_atributo);
    
    if(existe && valor != 0){
        _valores[p] = valor;
    } else if(existe && valor == 0){
        RemoveEm(p);
    } else if(!existe && valor != 0){
        InsereEm(p, id_item, id_atributo, valor);
    }
}

void EsparsaT::Remove(int id_item, int id_atributo){
    int p = Busca(id_item, id_atributo);

    if(p < tamanho && _itens[p] == id_item && _atributos[p] == id_atributo){
        RemoveEm(p);
    }
}

int EsparsaT::GetLinha(int id_item, int* atributos, int* valores){
    // atributo -1 faz a busca parar na primeira tripla do item
    int p = Busca(id_item, -1);
    int k = 0;

    while(p < tamanho && _itens[p] == id_item){
        atributos[k] = _atributos[p];
        valores[k] = _valores[p];
        k++;
        p++;
        percorridas++;
    }

    return k;
}

int EsparsaT::GetColuna(int id_atributo, int* itens, int* valores){
    int k = 0;

    for(int i = 0; i<tamanho; i++){
        percorridas++;

        if(_atributos[i] == id_atributo){
            itens[k] = _itens[i];
            valores[k] = _valores[i];
            k++;
        }
    }

    return k;
}

// só usado na migração, que já manda as triplas em ordem
void EsparsaT::AdicionaNoFim(int id_item, int id_atributo, int valor){
    if(tamanho == capacidade) Resize();

    _itens[tamanho] = id_item;
    _atributos[tamanho] = id_atributo;
    _valores[tamanho] = valor;
    tamanho++;
}

void EsparsaT::Limpa(){
    tamanho = 0;
}

int EsparsaT::NumCelulas(){
    return tamanho;
}

long long EsparsaT::MemoriaUsada(){
    return capacidade * 3 * sizeof(int);
}

long long EsparsaT::Percorridas(){
    return percorridas;
}

void EsparsaT::ZeraContador(){
    percorridas = 0;
}

// acha a primeira tripla >= (item, atributo)
int EsparsaT::Busca(int id_item, int id_atributo){
    int inicio = 0, fim = tamanho;

    while(inicio < fim){
        int meio = (inicio + fim)/2;
        percorridas++;

        if(_itens[meio] < id_item || (_itens[meio] == id_item && _atributos[meio] < id_atributo)){
            inicio = meio + 1;
        } else {
            fim = meio;
        }
    }

    return inicio;
}

void EsparsaT::InsereEm(int p, int id_item, int id_atributo, int valor){
    if(tamanho == capacidade) Resize();

    // empurra tudo de p pra frente pra abrir espaço
    for(int i = tamanho; i>p; i--){
        _itens[i] = _itens[i-1];
        _atributos[i] = _atributos[i-1];
        _valores[i] = _valores[i-1];
        percorridas++;
    }

    _itens[p] = id_item;
    _atributos[p] = id_atributo;
    _valores[p] = valor;
    tamanho++;
}

void EsparsaT::RemoveEm(int p){
    for(int i = p; i<tamanho-1; i++){
        _itens[i] = _itens[i+1];
        _atributos[i] = _atributos[i+1];
        _valores[i] = _valores[i+1];
        percorridas++;
    }

    tamanho--;
}

void EsparsaT::Resize(){
    capacidade *= 2;
    int* aux_itens = new int[capacidade];
    int* aux_atributos = new int[capacidade];
    int* aux_valores = new int[capacidade];

    for(int i = 0; i<tamanho; i++){
        aux_itens[i] = _itens[i];
        aux_atributos[i] = _atributos[i];
        aux_valores[i] = _valores[i];
    }

    delete[] _itens;
    delete[] _atributos;
    delete[] _valores;

    _itens = aux_itens;
    _atributos = aux_atributos;
    _valores = aux_valores;
}