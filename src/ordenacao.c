#include "../include/ordenacao.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct dados_livro DADOS_L; 

struct dados_livro {
  int id;
  char titulo[80];
  char autor[80];
  int ano;
};

typedef struct contexto_copy CONTEXTO_COPY;

struct contexto_copy {
  DADOS_L *vetor;
  int indice;
};

static void copiar_livro(const LIVROS *livro, void *contexto) {
  if (livro == NULL || contexto == NULL) {
    return;
  }
  
  CONTEXTO_COPY *dados = contexto;

  

}


void ordenar_por_titulo(const ARVORE *tree) {
  if (tree == NULL) {
    return;
  }
    
  int quantidade = contar_livros(tree);

  if (quantidade == 0) {
    return;
  }

  DADOS_L *p = malloc(quantidade * sizeof(DADOS_L));

  if (p == NULL) {
    return;
  }

  

}
