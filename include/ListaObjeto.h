#ifndef LISTA_OBJETO_H
#define LISTA_OBJETO_H
#define MAXTAM_LISTA 4

template <typename T>
class ListaObjeto{
    private:
        T** elementos;
        int tamanho;
        int capacidade = MAXTAM_LISTA;
        void Resize();
    public:
        ListaObjeto();
        ~ListaObjeto();
        ListaObjeto(const ListaObjeto& copia) = delete;
        ListaObjeto& operator=(const ListaObjeto& copia) = delete;

        void Adicionar(T* entrada);
        T* Acessar(int id);
        int Tamanho();
};

template <typename T>
ListaObjeto<T>::ListaObjeto(){
    elementos = new T*[capacidade];
    tamanho = 0;
}

template <typename T>
ListaObjeto<T>::~ListaObjeto(){
    for(int i = 0; i<tamanho; i++){
        delete elementos[i];
    }

    delete[] elementos;
}


template <typename T>
void ListaObjeto<T>::Resize(){
    capacidade *= 2;
    T** aux = new T*[capacidade];

    for(int i = 0; i<tamanho; i++){
        aux[i] = elementos[i];
    }

    delete[] elementos;
    elementos = aux;
}

template <typename T>
void ListaObjeto<T>::Adicionar(T* entrada){
    if(tamanho == capacidade) Resize();

    elementos[tamanho] = entrada;
    tamanho++;
}

template <typename T>
T* ListaObjeto<T>::Acessar(int id){
    return elementos[id];
}

template <typename T>
int ListaObjeto<T>::Tamanho(){
    return tamanho;
}

#endif