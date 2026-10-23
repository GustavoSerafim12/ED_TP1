#include "Consulta.h"
#include "Ordenacao.h"
#include <cstdio>
#include <cmath>

enum Metrica { PODER, EQUILIBRIO, SINERGIA };

Metrica LeMetrica(std::string nome){
    if(nome == "PODER") return PODER;
    if(nome == "EQUILIBRIO") return EQUILIBRIO;
    return SINERGIA;
}

void ConsultaLI(Catalogo& cat, ListaObjeto<Item>& itens, int id_item){
    int T = cat.NumAtributos();
    int* atributos = new int[T];
    int* valores = new int[T];

    int k = cat.GetLinha(id_item, atributos, valores);
    std::printf("LI %s", itens.Acessar(id_item)->GetNome().c_str());
    if(k == 0) std::printf(" VAZIO");
    for(int j = 0; j<k; j++){
        std::printf(" atributo_%d %d %d", j + 1, atributos[j], valores[j]);
    }
    std::printf("\n");

    delete[] atributos;
    delete[] valores;
}

void ConsultaLA(Catalogo& cat, ListaObjeto<Atributo>& atributos, int id_atr){
    int N = cat.NumItens();
    int* itens = new int[N];
    int* valores = new int[N];

    int k = cat.GetColuna(id_atr, itens, valores);
    std::printf("LA %s", atributos.Acessar(id_atr)->GetNome().c_str());
    if(k == 0) std::printf(" VAZIO");
    for(int j = 0; j<k; j++){
        std::printf(" item_%d %d %d", j + 1, itens[j], valores[j]);
    }
    std::printf("\n");

    delete[] itens;
    delete[] valores;
}

void CalculaBuild(Catalogo& cat, Aventureiro& av, long long* build, int T){
    for(int a = 0; a<T; a++){
        build[a] = 0;
    }
    int tam = av.Inventario.Tamanho();
    for(int p = 0; p<tam; p++){
        cat.AcumulaLinha(av.Inventario.Acessar(p), build, +1);
    }
}

void ConsultaLH(Catalogo& cat, Aventureiro& av){
    int T = cat.NumAtributos();
    long long* build = new long long[T];
    CalculaBuild(cat, av, build, T);

    std::printf("LH %s", av.GetNome().c_str());
    int impressos = 0;
    for(int a = 0; a<T; a++){
        if(build[a] != 0){
            impressos++;
            std::printf(" atributo_%d %d %lld", impressos, a, build[a]);
        }
    }
    if(impressos == 0) std::printf(" VAZIO");
    std::printf("\n");

    delete[] build;
}

double NormaBuild(long long* build, int T){
    double soma2 = 0.0;
    for(int a = 0; a<T; a++){
        soma2 += (double)build[a] * (double)build[a];
    }
    return std::sqrt(soma2);
}

// valores[i] = valor da métrica pro item i
void CalculaValores(Metrica met, Catalogo& cat, int* bufA, int* bufV, double* valores,
                    long long* build, double normaBuild){
    int N = cat.NumItens();
    int T = cat.NumAtributos();

    for(int i = 0; i<N; i++){
        int k = cat.GetLinha(i, bufA, bufV);
        double soma = 0.0, soma2 = 0.0;
        for(int j = 0; j<k; j++){
            soma += bufV[j];
            soma2 += (double)bufV[j] * bufV[j];
        }

        if(met == PODER){
            valores[i] = soma;
        }
        else if(met == EQUILIBRIO){
            // variância = média dos quadrados - quadrado da média, contando
            // os T atributos (os zeros também entram). menos variância = mais equilibrado
            if(T == 0){
                valores[i] = 1.0;
            }
            else{
                double mu = soma / T;
                double var = soma2 / T - mu * mu;
                if(var < 0) var = 0; // erro de arredondamento pode deixar negativo
                valores[i] = 1.0 / (1.0 + std::sqrt(var));
            }
        }
        else{
            // cosseno entre o item e a build
            double normaItem = std::sqrt(soma2);
            if(normaItem == 0.0 || normaBuild == 0.0){
                valores[i] = 0.0;
            }
            else{
                long long prod = cat.ProdutoInternoDenso(i, build);
                valores[i] = (double)prod / (normaItem * normaBuild);
            }
        }
    }
}

// quem está na posição p ganha (N - p) * peso: o 1º ganha N*peso, o último 1*peso
void Pontua(int* ordem, int N, double peso, double* pontuacao){
    for(int p = 0; p<N; p++){
        pontuacao[ordem[p]] += (N - p) * peso;
    }
}

// coloca em candidatos os itens que não estão na pilha; devolve quantos ficaram
int DescartaEquipados(Aventureiro& av, int N, bool* equipado, int* candidatos){
    for(int i = 0; i<N; i++){
        equipado[i] = false;
    }
    int tamPilha = av.Inventario.Tamanho();
    for(int p = 0; p<tamPilha; p++){
        equipado[av.Inventario.Acessar(p)] = true;
    }

    int c = 0;
    for(int i = 0; i<N; i++){
        if(!equipado[i]) candidatos[c++] = i;
    }
    return c;
}

void ConsultaQ(Catalogo& cat, Aventureiro& av, int n, int m,
               std::string* metricas, double* pesos){
    int N = cat.NumItens();
    int T = cat.NumAtributos();

    int* bufA = new int[T];
    int* bufV = new int[T];
    long long* build = new long long[T];
    double* valores = new double[N];
    double* pontuacao = new double[N];
    int* ordem = new int[N];
    int* candidatos = new int[N];
    bool* equipado = new bool[N];

    for(int i = 0; i<N; i++){
        pontuacao[i] = 0.0;
    }

    // a build só é usada na SINERGIA, então só calcula se precisar
    bool temSinergia = false;
    for(int q = 0; q<m; q++){
        if(LeMetrica(metricas[q]) == SINERGIA) temSinergia = true;
    }
    
    double normaBuild = 0.0;
    if(temSinergia){
        CalculaBuild(cat, av, build, T);
        normaBuild = NormaBuild(build, T);
    }

    // cada métrica gera um ranking de todos os itens, e a posição vira pontos
    for(int q = 0; q<m; q++){
        CalculaValores(LeMetrica(metricas[q]), cat, bufA, bufV, valores, build, normaBuild);
        for(int i = 0; i<N; i++){
            ordem[i] = i;
        }
        InsertionSort(ordem, N, valores, 1e6);
        Pontua(ordem, N, pesos[q], pontuacao);
    }

    int c = DescartaEquipados(av, N, equipado, candidatos);

    InsertionSort(candidatos, c, pontuacao, 100.0);
    for(int p = 0; p<n && p<c; p++){
        int id = candidatos[p];
        std::printf("Q %d %d %.2f\n", p + 1, id, pontuacao[id]);
    }

    delete[] bufA;
    delete[] bufV;
    delete[] build;
    delete[] valores;
    delete[] pontuacao;
    delete[] ordem;
    delete[] candidatos;
    delete[] equipado;
}
