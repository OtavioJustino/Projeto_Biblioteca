#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../include/livro.h"
#include "../include/arvore.h"
#include "../include/lista.h"
#include "../include/pilha.h"

static LIVROS *novo(int id, const char *titulo) {
    return criar_livro(id, (char *)titulo, "Autor", 2020);
}
static void teste_livros(void) {
    LIVROS *l = novo(10, "Estruturas");
    assert(l);
    assert(obter_id(l) == 10);
    assert(obter_ano(l) == 2020);
    assert(strcmp(obter_titulo(l), "Estruturas") == 0);
    assert(strcmp(obter_autor(l), "Autor") == 0);
    destruir_livro(l);
    assert(!novo(0, "Valido"));
    assert(!novo(1, "   "));
    assert(!criar_livro(1, "Valido", "   ", 2020));
    assert(!criar_livro(1, "Valido", "Autor", 0));
    assert(!criar_livro(1, "Valido", "Autor", 2027));
    assert(obter_id(NULL) == -1);
    assert(obter_titulo(NULL) == NULL);
}
typedef struct { int ids[16]; int n; } VISITAS;
static void visitar(const LIVROS *l, void *ctx) {
    VISITAS *v = ctx;
    assert(v->n < 16);
    v->ids[v->n++] = obter_id(l);
}
static void teste_arvore(void) {
    ARVORE *a = cria_arvore();
    assert(a);
    assert(contar_livros(a) == 0);
    assert(menor_id(a) == 0 && maior_id(a) == 0);
    int ids[] = {5, 3, 7, 2, 4, 6, 8};
    for (int i = 0; i < 7; ++i) assert(inserir_livro(a, novo(ids[i], "Livro")) == 1);
    assert(contar_livros(a) == 7);
    assert(menor_id(a) == 2 && maior_id(a) == 8);
    assert(busca_livro(a, 4) && !busca_livro(a, 99));
    LIVROS *duplicado = novo(5, "Duplicado");
    assert(!inserir_livro(a, duplicado));
    destruir_livro(duplicado); /* A arvore nao assume propriedade se a insercao falha. */
    VISITAS v = {{0}, 0};
    percorrer_livros(a, visitar, &v);
    assert(v.n == 7);
    for (int i = 0; i < 7; ++i) assert(v.ids[i] == i + 2);
    assert(remover_livro(a, 2)); /* folha */
    assert(remover_livro(a, 3)); /* um filho */
    assert(remover_livro(a, 5)); /* dois filhos, raiz */
    assert(contar_livros(a) == 4);
    assert(!busca_livro(a, 5));
    assert(!remover_livro(a, 99));
    destruir_arvore(a);
    assert(!inserir_livro(NULL, NULL));
    assert(contar_livros(NULL) == 0);
}
static void teste_lista(void) {
    LISTA *l = criar_lista();
    assert(l);
    assert(inserir_fim(l, 1));
    assert(inserir_fim(l, 2));
    assert(!inserir_fim(NULL, 3));
    destruir_lista(l);
    destruir_lista(NULL);
}
static void teste_pilha(void) {
    PILHA *p = criar_pilha();
    assert(p);
    ACAO acao; int a, b;
    assert(!rmv_topo(p, &acao, &a, &b));
    assert(add_topo(p, CADASTRO, 1, 0));
    assert(add_topo(p, ADD_CONEXAO, 1, 2));
    assert(ver_topo(p, &acao, &a, &b));
    assert(acao == ADD_CONEXAO && a == 1 && b == 2);
    assert(rmv_topo(p, &acao, &a, &b));
    assert(acao == ADD_CONEXAO && a == 1 && b == 2);
    assert(rmv_topo(p, &acao, &a, &b));
    assert(acao == CADASTRO && a == 1);
    assert(!rmv_topo(p, &acao, &a, &b));
    assert(!add_topo(NULL, CADASTRO, 1, 0));
    destruir_pilha(p);
}
int main(void) {
    teste_livros();
    teste_arvore();
    teste_lista();
    teste_pilha();
    puts("OK: livros, BST, lista e pilha");
    return 0;
}
