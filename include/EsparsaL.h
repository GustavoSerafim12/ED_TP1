#ifndef ESPARSA_L_H
#define ESPARSA_L_H
#define CAP_INICIAL_CABECAS 4

// nas cabeças item e atributo ficam -1
struct CelulaL{
    int item;
    int atributo;
    int valor;
    CelulaL* proxLin;
    CelulaL* proxCol;
};

// lista cruzada: cada célula está na lista da sua linha e da sua coluna
class EsparsaL{
    private:
        CelulaL** _cabLin;
        CelulaL** _cabCol;
        int _numLinhas;
        int _numColunas;
        int _capLin;
        int _capCol;
        int tamanho;
        long long percorridas;

        CelulaL* AntLinha(int id_item, int id_atributo);
        CelulaL* AntColuna(int id_item, int id_atributo);
        void CresceLinhas();
        void CresceColunas();

    public:
        EsparsaL();
        ~EsparsaL();
        EsparsaL(const EsparsaL& copia) = delete;
        EsparsaL& operator=(const EsparsaL& copia) = delete;

        void AdicionaLinha();
        void AdicionaColuna();

        int Get(int id_item, int id_atributo);
        void Set(int id_item, int id_atributo, int valor);
        void Remove(int id_item, int id_atributo);

        int GetLinha(int id_item, int* outAtributos, int* outValores);
        int GetColuna(int id_atributo, int* outItens, int* outValores);

        void AdicionaNoFim(int id_item, int id_atributo, int valor);
        void Limpa();

        int NumCelulas();
        long long MemoriaUsada();

        long long Percorridas();
        void ZeraContador();
};

#endif
