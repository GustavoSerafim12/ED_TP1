#include "EsparsaL.h"

EsparsaL::EsparsaL(){
    _capLin = CAP_INICIAL_CABECAS;
    _capCol = CAP_INICIAL_CABECAS;
    _cabLin = new CelulaL*[_capLin];
    _cabCol = new CelulaL*[_capCol];
    _numLinhas = 0;
    _numColunas = 0;
    tamanho = 0;
    percorridas = 0;
}

EsparsaL::~EsparsaL(){
    Limpa();

    for(int i = 0; i<_numLinhas; i++){
        delete _cabLin[i];
    }

    for(int j = 0; j<_numColunas; j++){
        delete _cabCol[j];
    }

    delete[] _cabLin;
    delete[] _cabCol;
}

void EsparsaL::AdicionaLinha(){
    if(_numLinhas == _capLin) CresceLinhas();

    _cabLin[_numLinhas] = new CelulaL{-1, -1, 0, nullptr, nullptr};
    _numLinhas++;
}

void EsparsaL::AdicionaColuna(){
    if(_numColunas == _capCol) CresceColunas();

    _cabCol[_numColunas] = new CelulaL{-1, -1, 0, nullptr, nullptr};
    _numColunas++;
}

int EsparsaL::Get(int id_item, int id_atributo){
    CelulaL* prox = AntLinha(id_item, id_atributo)->proxLin;

    if(prox != nullptr && prox->atributo == id_atributo){
        return prox->valor;
    }

    return 0;
}

void EsparsaL::Set(int id_item, int id_atributo, int valor){
    CelulaL* antLin = AntLinha(id_item, id_atributo);
    CelulaL* antCol = AntColuna(id_item, id_atributo);
    CelulaL* atual = antLin->proxLin;
    bool existe = (atual != nullptr && atual->atributo == id_atributo);

    if(existe && valor != 0){
        atual->valor = valor;
    } else if(existe && valor == 0){
        // desliga a célula da linha e da coluna antes de apagar
        antLin->proxLin = atual->proxLin;
        antCol->proxCol = atual->proxCol;
        delete atual;
        tamanho--;
    } else if(!existe && valor != 0){
        // a nova já aponta pra quem vem depois dela na linha e na coluna
        CelulaL* nova = new CelulaL{id_item, id_atributo, valor, antLin->proxLin, antCol->proxCol};
        // liga a nova na linha e depois na coluna
        antLin->proxLin = nova;
        antCol->proxCol = nova;
        tamanho++;
    }
}

void EsparsaL::Remove(int id_item, int id_atributo){
    CelulaL* antLin = AntLinha(id_item, id_atributo);
    CelulaL* antCol = AntColuna(id_item, id_atributo);
    CelulaL* atual = antLin->proxLin;

    if(atual != nullptr && atual->atributo == id_atributo){
        antLin->proxLin = atual->proxLin;
        antCol->proxCol = atual->proxCol;
        delete atual;
        tamanho--;
    }
}

int EsparsaL::GetLinha(int id_item, int* outAtributos, int* outValores){
    int k = 0;

    for(CelulaL* c = _cabLin[id_item]->proxLin; c != nullptr; c = c->proxLin){
        outAtributos[k] = c->atributo;
        outValores[k] = c->valor;
        k++;
        percorridas++;
    }

    return k;
}

int EsparsaL::GetColuna(int id_atributo, int* outItens, int* outValores){
    int k = 0;

    for(CelulaL* c = _cabCol[id_atributo]->proxCol; c != nullptr; c = c->proxCol){
        outItens[k] = c->item;
        outValores[k] = c->valor;
        k++;
        percorridas++;
    }

    return k;
}

void EsparsaL::AdicionaNoFim(int id_item, int id_atributo, int valor){
    Set(id_item, id_atributo, valor);
}

// apaga as células pelas linhas; as cabeças continuam
void EsparsaL::Limpa(){
    for(int i = 0; i<_numLinhas; i++){
        CelulaL* c = _cabLin[i]->proxLin;

        while(c != nullptr){
            CelulaL* prox = c->proxLin;
            delete c;
            c = prox;
        }

        _cabLin[i]->proxLin = nullptr;
    }

    for(int j = 0; j<_numColunas; j++){
        _cabCol[j]->proxCol = nullptr;
    }

    tamanho = 0;
}

int EsparsaL::NumCelulas(){
    return tamanho;
}

long long EsparsaL::MemoriaUsada(){
    return (long long)tamanho * sizeof(CelulaL)
         + (long long)(_numLinhas + _numColunas) * sizeof(CelulaL)
         + (long long)(_capLin + _capCol) * sizeof(CelulaL*);
}

long long EsparsaL::Percorridas(){
    return percorridas;
}

void EsparsaL::ZeraContador(){
    percorridas = 0;
}

// para na última célula da linha com atributo menor (ou na cabeça)
CelulaL* EsparsaL::AntLinha(int id_item, int id_atributo){
    CelulaL* c = _cabLin[id_item];

    while(c->proxLin != nullptr && c->proxLin->atributo < id_atributo){
        c = c->proxLin;
        percorridas++;
    }

    return c;
}

// mesma ideia, mas descendo pela coluna
CelulaL* EsparsaL::AntColuna(int id_item, int id_atributo){
    CelulaL* c = _cabCol[id_atributo];

    while(c->proxCol != nullptr && c->proxCol->item < id_item){
        c = c->proxCol;
        percorridas++;
    }

    return c;
}

void EsparsaL::CresceLinhas(){
    _capLin *= 2;
    CelulaL** aux = new CelulaL*[_capLin];

    for(int i = 0; i<_numLinhas; i++){
        aux[i] = _cabLin[i];
    }

    delete[] _cabLin;
    _cabLin = aux;
}

void EsparsaL::CresceColunas(){
    _capCol *= 2;
    CelulaL** aux = new CelulaL*[_capCol];

    for(int j = 0; j<_numColunas; j++){
        aux[j] = _cabCol[j];
    }

    delete[] _cabCol;
    _cabCol = aux;
}
