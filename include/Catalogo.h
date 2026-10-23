#ifndef CATALOGO_H
#define CATALOGO_H
#define CAP_INICIAL_BUF 4

#include "EsparsaT.h"
#include "EsparsaL.h"

// matriz item x atributo; guarda os dados no modo T ou no modo L
class Catalogo{
    private:
        char _modo;
        EsparsaT _modoT;
        EsparsaL _modoL;
        int _N;
        int _T;
        // buffers pra ler uma linha inteira
        int* _bufAtr;
        int* _bufVal;
        int _capBuf;

        void CresceBuffers();

    public:
        Catalogo();
        ~Catalogo();
        Catalogo(const Catalogo& copia) = delete;
        Catalogo& operator=(const Catalogo& copia) = delete;

        void AdicionaLinha();
        void AdicionaColuna();

        char GetModo();
        int NumItens();
        int NumAtributos();

        void MudaModo(char novo);

        int Get(int item, int atributo);
        void Set(int item, int atributo, int valor);
        void Remove(int item, int atributo);

        int GetLinha(int item, int* outAtributos, int* outValores);
        int GetColuna(int atributo, int* outItens, int* outValores);

        void AcumulaLinha(int item, long long* vetor, int sinal);
        long long ProdutoInternoDenso(int item, long long* vetor);
        long long ProdutoInternoMerge(int item, int* atrB, long long* valB, int tamB);

        int NumCelulas();
        long long MemoriaUsada();

        long long Percorridas();
        void ZeraContador();
};

#endif
