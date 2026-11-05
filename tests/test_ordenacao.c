#define _POSIX_C_SOURCE 200809L
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/livro.h"
#include "../include/arvore.h"
#include "../include/ordenacao.h"

/* Captura a saida atual da funcao, sem modificar sua implementacao. */
static void verificar_saida(ARVORE *arvore, const char *esperado) {
    FILE *temporario = tmpfile();
    assert(temporario != NULL);
    fflush(stdout);
    int original = dup(STDOUT_FILENO);
    assert(original >= 0);
    assert(dup2(fileno(temporario), STDOUT_FILENO) >= 0);
    ordenar_por_titulo(arvore);
    fflush(stdout);
    assert(dup2(original, STDOUT_FILENO) >= 0);
    close(original);
    rewind(temporario);
    char saida[2048] = {0};
    size_t n = fread(saida, 1, sizeof(saida) - 1, temporario);
    saida[n] = '\0';
    fclose(temporario);
    if (strcmp(saida, esperado) != 0) {
        fprintf(stderr, "Saida esperada: [%s]\nSaida obtida: [%s]\n", esperado, saida);
        abort();
    }
}
static void adicionar(ARVORE *arvore, int id, const char *titulo) {
    LIVROS *livro = criar_livro(id, (char *)titulo, "Autor", 2020);
    assert(livro != NULL);
    assert(inserir_livro(arvore, livro) == 1);
}
int main(void) {
    ordenar_por_titulo(NULL);
    ARVORE *arvore = cria_arvore();
    assert(arvore != NULL);
    verificar_saida(arvore, "");
    adicionar(arvore, 10, "Zeta");
    verificar_saida(arvore, "10ZetaAutor2020");
    adicionar(arvore, 5, "Alfa");
    adicionar(arvore, 20, "Alfa");
    adicionar(arvore, 15, "Beta");
    /* Formato de impressao atual: campos concatenados, sem separadores. */
    verificar_saida(arvore, "5AlfaAutor202020AlfaAutor202015BetaAutor202010ZetaAutor2020");
    assert(contar_livros(arvore) == 4); /* Ordenar nao altera a BST. */
    assert(obter_id(busca_livro(arvore, 10)) == 10);
    destruir_arvore(arvore);
    puts("OK: ordenacao por titulo e desempate por ID");
    return 0;
}
