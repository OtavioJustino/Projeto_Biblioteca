#include <assert.h>
#include <stdio.h>
#include "../include/grafo.h"

static void teste_vertices(void) {
    GRAFO *g = criar_grafo();
    assert(g != NULL);
    assert(add_vertice(g, 10) == 1);
    assert(add_vertice(g, 20) == 1);
    assert(add_vertice(g, 30) == 1);
    assert(add_vertice(g, 10) == 0);
    assert(add_vertice(g, 0) == 0);
    assert(add_vertice(NULL, 1) == 0);
    assert(conexao_direta(g, 10, 20) == 0);
    assert(rmv_vertice(g, 99) == 0);
    assert(rmv_vertice(g, 20) == 1);
    assert(rmv_vertice(g, 20) == 0);
    assert(add_vertice(g, 20) == 1);
    destruir_grafo(g);
    destruir_grafo(NULL);
}

static void teste_conexoes(void) {
    GRAFO *g = criar_grafo();
    assert(g != NULL);
    for (int id = 1; id <= 4; id++) assert(add_vertice(g, id));
    assert(add_conexao(g, 1, 2));
    assert(add_conexao(g, 2, 3));
    assert(conexao_direta(g, 1, 2));
    assert(conexao_direta(g, 2, 1));
    assert(!conexao_direta(g, 1, 3));
    assert(!add_conexao(g, 1, 2));
    assert(!add_conexao(g, 1, 1));
    assert(!add_conexao(g, 1, 99));
    assert(!add_conexao(NULL, 1, 2));
    assert(verificar_caminho(g, 1, 3));
    assert(verificar_caminho(g, 3, 1));
    assert(verificar_caminho(g, 1, 1));
    assert(!verificar_caminho(g, 1, 4));
    assert(!verificar_caminho(g, 1, 99));
    assert(!verificar_caminho(NULL, 1, 2));
    assert(rmv_conexao(g, 2, 3));
    assert(!conexao_direta(g, 2, 3));
    assert(!conexao_direta(g, 3, 2));
    assert(!verificar_caminho(g, 1, 3));
    assert(!rmv_conexao(g, 2, 3));
    assert(!rmv_conexao(g, 1, 1));
    assert(add_conexao(g, 2, 3));
    assert(rmv_vertice(g, 2));
    assert(!conexao_direta(g, 1, 2));
    assert(!conexao_direta(g, 3, 2));
    assert(!verificar_caminho(g, 1, 3));
    assert(add_conexao(g, 1, 3));
    assert(verificar_caminho(g, 1, 3));
    destruir_grafo(g);
}

static void teste_alcancaveis(void) {
    GRAFO *g = criar_grafo();
    assert(g != NULL);
    assert(add_vertice(g, 10));
    assert(add_vertice(g, 50));
    assert(add_vertice(g, 90));
    assert(add_conexao(g, 10, 50));
    assert(add_conexao(g, 50, 90));
    assert(listar_alcancaveis(g, 10));
    assert(!listar_alcancaveis(g, 999));
    assert(!listar_alcancaveis(NULL, 10));
    assert(rmv_vertice(g, 50));
    assert(!verificar_caminho(g, 10, 90));
    assert(listar_alcancaveis(g, 10));
    destruir_grafo(g);
}

int main(void) {
    teste_vertices();
    teste_conexoes();
    teste_alcancaveis();
    puts("OK: grafo, conexoes e BFS");
    return 0;
}
