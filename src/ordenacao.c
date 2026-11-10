#include "../include/ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

  dados->vetor[dados->indice].id = obter_id(livro);
  strcpy(dados->vetor[dados->indice].titulo, obter_titulo(livro));
  strcpy(dados->vetor[dados->indice].autor, obter_autor(livro));
  dados->vetor[dados->indice].ano = obter_ano(livro);

  dados->indice++;
  
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

  CONTEXTO_COPY dados;

  dados.vetor = p;
  dados.indice = 0;

  percorrer_livros(tree, copiar_livro, &dados);

  for (int i = 1; i < quantidade; i++) {
    DADOS_L chave = p[i];
    int j = i - 1;
    while (j >= 0 && (strcmp(p[j].titulo, chave.titulo) > 0 || (strcmp(p[j].titulo, chave.titulo) == 0 && p[j].id > chave.id))) {
      p[j+1] = p[j];
      j--;
    }

    p[j+1] = chave;

  }

  for (int i = 0; i < quantidade; i++)
  {
    printf("ID:     %d\n", p[i].id);
    printf("Titulo: %s\n", p[i].titulo);
    printf("Autor:  %s\n", p[i].autor);
    printf("Ano:    %d\n\n", p[i].ano);
  }
  
  free(p);
}
