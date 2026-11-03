#include "../include/arvore.h"
#include "../include/livro.h"
#include <stdlib.h>

typedef struct elemento ELEMENTO;

struct elemento {
  LIVROS *livro;
  ELEMENTO *esquerda;
  ELEMENTO *direita;
};

struct arvore {
  ELEMENTO *raiz;
};


ARVORE *cria_arvore() {
  ARVORE *p = malloc(sizeof(ARVORE));

  if (p == NULL) {
    return NULL;
  }

  p->raiz = NULL;

  return p;
}

int inserir_livro(ARVORE *tree, LIVROS *livro) {
  if (tree == NULL || livro == NULL) {
    return 0;
  }

  ELEMENTO *p = malloc(sizeof(ELEMENTO));

  if (p == NULL) {
    return 0;
  }

  p->livro = livro;
  p->esquerda = NULL; 
  p->direita = NULL; 
  

  if (tree->raiz == NULL ){
    tree->raiz = p;
    return 1;
  }
  
  int id = obter_id(livro);
  
  ELEMENTO *atual = tree->raiz;

  
while (atual != NULL) {
    int id_atual = obter_id(atual->livro);

    if (id == id_atual) {
        free(p);
        return 0;
    }

    if (id > id_atual) {
        if (atual->direita == NULL) {
            atual->direita = p;
            break;
        }

        atual = atual->direita;
    } else {
        if (atual->esquerda == NULL) {
            atual->esquerda = p;
            break;
        }

        atual = atual->esquerda;
    }
}

  return 1;

}


