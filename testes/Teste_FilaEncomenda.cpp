#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "FilaEncomenda.h"

TEST_CASE("Fila nova esta vazia e com tamanho 0") {
    FilaEncomenda fila;
    CHECK(fila.Vazia() == true);
    CHECK(fila.Tamanho() == 0);
}

TEST_CASE("Adicionar incrementa tamanho e Remover respeita ordem FIFO") {
    FilaEncomenda fila;
    fila.Adicionar({1, 10});
    fila.Adicionar({2, 20});
    fila.Adicionar({3, 30});

    CHECK(fila.Vazia() == false);
    CHECK(fila.Tamanho() == 3);

    Encomenda e1 = fila.Remover();
    CHECK(e1.id_aventureiro == 1);
    CHECK(e1.id_item == 10);
    CHECK(fila.Tamanho() == 2);

    Encomenda e2 = fila.Remover();
    CHECK(e2.id_aventureiro == 2);
    CHECK(e2.id_item == 20);

    Encomenda e3 = fila.Remover();
    CHECK(e3.id_aventureiro == 3);
    CHECK(e3.id_item == 30);

    CHECK(fila.Vazia() == true);
}

TEST_CASE("Remover de fila vazia lanca excecao") {
    FilaEncomenda fila;
    CHECK_THROWS(fila.Remover());
}

TEST_CASE("Fila mantem ordem apos intercalar Adicionar e Remover (sem Resize)") {
    FilaEncomenda fila;
    fila.Adicionar({1, 1});
    fila.Adicionar({2, 2});
    CHECK(fila.Remover().id_aventureiro == 1);
    fila.Adicionar({3, 3});
    // inicio avancou, entao esse ciclo testa o wraparound do indice circular
    // sem precisar de Resize, ja que capacidade inicial e 4.
    CHECK(fila.Tamanho() == 2);
    CHECK(fila.Remover().id_aventureiro == 2);
    CHECK(fila.Remover().id_aventureiro == 3);
    CHECK(fila.Vazia() == true);
}

TEST_CASE("Adicionar alem da capacidade inicial aciona Resize e preserva os dados") {
    FilaEncomenda fila;

    // MAXTAM_INITIAL = 4: inserir um 5o elemento forca o Resize().
    for (int i = 1; i <= 5; i++) {
        fila.Adicionar({i, i * 100});
    }

    CHECK(fila.Tamanho() == 5);

    for (int i = 1; i <= 5; i++) {
        Encomenda e = fila.Remover();
        CHECK(e.id_aventureiro == i);
        CHECK(e.id_item == i * 100);
    }

    CHECK(fila.Vazia() == true);
}

TEST_CASE("Resize preserva ordem quando inicio nao esta em 0 (fila circular 'enrolada')") {
    FilaEncomenda fila;

    // Avanca o indice 'inicio' para o meio do buffer antes de forcar o Resize,
    // garantindo que o bloco [inicio, capacidade) + [0, fim) seja realinhado
    // corretamente para o novo buffer, a partir do indice 0.
    fila.Adicionar({1, 1});
    fila.Adicionar({2, 2});
    fila.Remover();
    fila.Remover();

    fila.Adicionar({3, 3});
    fila.Adicionar({4, 4});
    fila.Adicionar({5, 5});
    // tamanho == 3, capacidade == 4, inicio == 2: ainda nao enche o buffer.
    CHECK(fila.Tamanho() == 3);

    fila.Adicionar({6, 6});
    // tamanho == 4 == capacidade, com 'fim' tendo dado a volta: proxima
    // insercao forca o Resize() e deve manter a ordem 3,4,5,6,7.
    fila.Adicionar({7, 7});

    CHECK(fila.Tamanho() == 5);
    for (int i = 3; i <= 7; i++) {
        Encomenda e = fila.Remover();
        CHECK(e.id_aventureiro == i);
        CHECK(e.id_item == i);
    }
    CHECK(fila.Vazia() == true);
}

TEST_CASE("Fila suporta multiplos Resizes consecutivos") {
    FilaEncomenda fila;
    const int N = 50; // forca varias duplicacoes de capacidade (4 -> 8 -> 16 -> 32 -> 64)

    for (int i = 0; i < N; i++) {
        fila.Adicionar({i, i});
    }
    CHECK(fila.Tamanho() == N);

    for (int i = 0; i < N; i++) {
        Encomenda e = fila.Remover();
        CHECK(e.id_aventureiro == i);
    }
    CHECK(fila.Vazia() == true);
}
