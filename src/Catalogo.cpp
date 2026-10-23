#include "Catalogo.h"

Catalogo::Catalogo(){
    _modo = 'L';
    _N = 0;
    _T = 0;
    _capBuf = CAP_INICIAL_BUF;
    _bufAtr = new int[_capBuf];
    _bufVal = new int[_capBuf];
}

Catalogo::~Catalogo(){
    delete[] _bufAtr;
    delete[] _bufVal;
}

void Catalogo::CresceBuffers(){
    while(_capBuf < _T) _capBuf *= 2;

    delete[] _bufAtr;
    delete[] _bufVal;
    _bufAtr = new int[_capBuf];
    _bufVal = new int[_capBuf];
}

// as cabeças do modo L são criadas sempre, mesmo no modo T
void Catalogo::AdicionaLinha(){
    _N++;
    _modoL.AdicionaLinha();
}

void Catalogo::AdicionaColuna(){
    _T++;
    _modoL.AdicionaColuna();
    if(_T > _capBuf) CresceBuffers();
}

char Catalogo::GetModo(){
    return _modo;
}

int Catalogo::NumItens(){
    return _N;
}

int Catalogo::NumAtributos(){
    return _T;
}

void Catalogo::MudaModo(char novo){
    if(novo == _modo) return;

    // copia linha por linha pro modo novo (lendo ainda do modo antigo),
    // assim as triplas já entram em ordem
    for(int i = 0; i<_N; i++){
        int k = GetLinha(i, _bufAtr, _bufVal);
        for(int j = 0; j<k; j++){
            if(novo == 'T') _modoT.AdicionaNoFim(i, _bufAtr[j], _bufVal[j]);
            else _modoL.AdicionaNoFim(i, _bufAtr[j], _bufVal[j]);
        }
    }

    // só depois de copiar tudo apaga o antigo
    if(_modo == 'T') _modoT.Limpa();
    else _modoL.Limpa();

    _modo = novo;
}

int Catalogo::Get(int item, int atributo){
    if(_modo == 'T') return _modoT.Get(item, atributo);
    return _modoL.Get(item, atributo);
}

void Catalogo::Set(int item, int atributo, int valor){
    if(_modo == 'T') _modoT.Set(item, atributo, valor);
    else _modoL.Set(item, atributo, valor);
}

void Catalogo::Remove(int item, int atributo){
    if(_modo == 'T') _modoT.Remove(item, atributo);
    else _modoL.Remove(item, atributo);
}

int Catalogo::GetLinha(int item, int* outAtributos, int* outValores){
    if(_modo == 'T') return _modoT.GetLinha(item, outAtributos, outValores);
    return _modoL.GetLinha(item, outAtributos, outValores);
}

int Catalogo::GetColuna(int atributo, int* outItens, int* outValores){
    if(_modo == 'T') return _modoT.GetColuna(atributo, outItens, outValores);
    return _modoL.GetColuna(atributo, outItens, outValores);
}

void Catalogo::AcumulaLinha(int item, long long* vetor, int sinal){
    int k = GetLinha(item, _bufAtr, _bufVal);
    for(int j = 0; j<k; j++){
        vetor[_bufAtr[j]] += (long long)sinal * _bufVal[j];
    }
}

long long Catalogo::ProdutoInternoDenso(int item, long long* vetor){
    int k = GetLinha(item, _bufAtr, _bufVal);
    long long soma = 0;
    for(int j = 0; j<k; j++){
        soma += _bufVal[j] * vetor[_bufAtr[j]];
    }
    return soma;
}

long long Catalogo::ProdutoInternoMerge(int item, int* atrB, long long* valB, int tamB){
    int tamA = GetLinha(item, _bufAtr, _bufVal);
    long long soma = 0;
    int a = 0, b = 0;

    // as duas listas estão ordenadas por atributo: anda na que tem o menor
    // e só soma quando os atributos batem
    while(a < tamA && b < tamB){
        if(_bufAtr[a] < atrB[b]) a++;
        else if(_bufAtr[a] > atrB[b]) b++;
        else{
            soma += _bufVal[a] * valB[b];
            a++;
            b++;
        }
    }
    return soma;
}

int Catalogo::NumCelulas(){
    if(_modo == 'T') return _modoT.NumCelulas();
    return _modoL.NumCelulas();
}

long long Catalogo::MemoriaUsada(){
    if(_modo == 'T') return _modoT.MemoriaUsada();
    return _modoL.MemoriaUsada();
}

long long Catalogo::Percorridas(){
    return _modoT.Percorridas() + _modoL.Percorridas();
}

void Catalogo::ZeraContador(){
    _modoT.ZeraContador();
    _modoL.ZeraContador();
}
