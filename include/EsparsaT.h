#ifndef ESPARSA_T_H
#define ESPARSA_T_H
#define MAXTAM_ESPARSA 4

// triplas (item, atributo, valor) ordenadas por item e depois por atributo
class EsparsaT{
    private:
        int* _itens;
        int* _atributos;
        int* _valores;
        int tamanho;
        int capacidade = MAXTAM_ESPARSA;
        long long percorridas;

        void Resize();
        int Busca(int id_item, int id_atributo);
        void InsereEm(int p, int id_item, int id_atributo, int valor);
        void RemoveEm(int p);

    public:
        EsparsaT();
        ~EsparsaT();
        EsparsaT(const EsparsaT& copia) = delete;
        EsparsaT& operator=(const EsparsaT& copia) = delete;

        int Get(int id_item, int id_atributo);
        void Set(int id_item, int id_atributo, int valor);
        void Remove(int id_item, int id_atributo);

        int GetLinha(int id_item, int* atributos, int* valores);
        int GetColuna(int id_atributo, int* itens, int* valores);

        void AdicionaNoFim(int id_item, int id_atributo, int valor);
        void Limpa();

        int NumCelulas();
        long long MemoriaUsada();

        long long Percorridas();
        void ZeraContador();
};

#endif
