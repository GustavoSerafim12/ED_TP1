#include "Ordenacao.h"
#include <cmath>

long long comparacoes = 0;

// a vem antes de b se tem chave maior; no empate ganha o id menor.
// compara as chaves arredondadas (chave * escala) pra não sofrer com erro de double
bool Precede(int a, int b, double* chave, double escala){
    comparacoes++;
    long long ka = std::llround(chave[a] * escala);
    long long kb = std::llround(chave[b] * escala);
    if(ka != kb) return ka > kb;
    return a < b;
}

void InsertionSort(int* v, int n, double* chave, double escala){
    for(int i = 1; i<n; i++){
        int x = v[i];
        int j = i - 1;
        while(j >= 0 && Precede(x, v[j], chave, escala)){
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = x;
    }
}

// junta v[ini..meio] e v[meio+1..fim], que já estão ordenados
void Merge(int* v, int ini, int meio, int fim, double* chave, double escala){
    int* aux = new int[fim - ini + 1];
    int i = ini, j = meio + 1, k = 0;

    while(i <= meio && j <= fim){
        if(Precede(v[j], v[i], chave, escala)) aux[k++] = v[j++];
        else aux[k++] = v[i++];
    }
    while(i <= meio) aux[k++] = v[i++];
    while(j <= fim) aux[k++] = v[j++];

    for(k = 0; k < fim - ini + 1; k++){
        v[ini + k] = aux[k];
    }
    delete[] aux;
}

void MergeSort(int* v, int ini, int fim, double* chave, double escala){
    if(ini >= fim) return;
    int meio = (ini + fim) / 2;
    MergeSort(v, ini, meio, chave, escala);
    MergeSort(v, meio + 1, fim, chave, escala);
    Merge(v, ini, meio, fim, chave, escala);
}

void QuickSort(int* v, int ini, int fim, double* chave, double escala){
    if(ini >= fim) return;
    int pivo = v[(ini + fim) / 2];
    int i = ini, j = fim;

    // i para em quem não devia estar na esquerda, j em quem não devia estar na direita
    while(i <= j){
        while(Precede(v[i], pivo, chave, escala)) i++;
        while(Precede(pivo, v[j], chave, escala)) j--;
        if(i <= j){
            int t = v[i];
            v[i] = v[j];
            v[j] = t;
            i++;
            j--;
        }
    }
    QuickSort(v, ini, j, chave, escala);
    QuickSort(v, i, fim, chave, escala);
}

long long ComparacoesOrdenacao(){
    return comparacoes;
}

void ZeraComparacoesOrdenacao(){
    comparacoes = 0;
}
