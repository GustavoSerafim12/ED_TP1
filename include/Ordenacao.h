#ifndef ORDENACAO_H
#define ORDENACAO_H

// Ordenam os ids em v pela chave[id], da maior pra menor (empate: id menor).
void InsertionSort(int* v, int n, double* chave, double escala);
void MergeSort(int* v, int ini, int fim, double* chave, double escala);
void QuickSort(int* v, int ini, int fim, double* chave, double escala);

long long ComparacoesOrdenacao();
void ZeraComparacoesOrdenacao();

#endif
