#include "../include/lista.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct elemento ELEMENTO;

struct elemento {
  int id;
  ELEMENTO *proximo;
};


struct lista {
  ELEMENTO *inicio;
  ELEMENTO *fim;
};

LISTA *criar_lista() {
  LISTA *p = malloc(sizeof(LISTA));

  if (p == NULL) {
    return NULL;
  }

  p->inicio = NULL;
  p->fim = NULL;

  return p;

}

void destruir_lista(LISTA *li) {
  if (li == NULL) {
    return;
  }
  
  ELEMENTO *aux_1;
  
  ELEMENTO *aux_2;

  aux_1 = li->inicio;
    
  while (aux_1 != NULL) {
    aux_2 = aux_1->proximo;
    free(aux_1);
    aux_1 = aux_2;
  }

  free(li);
}

int inserir_fim(LISTA *li, int id) {
  if (li == NULL) {
    return 0;
  }

  ELEMENTO *p = malloc(sizeof(ELEMENTO));
    if(p == NULL) {
    return 0;
  }

  p->id = id;
  p->proximo = NULL;

  if (li->inicio != NULL) {
    li->fim->proximo = p;
    li->fim = p;
    return 1;
  } else {
    li->inicio = p;
    li->fim =p;
    return 1;
  }
}

void exibir_lista(const LISTA *li) {
  if (li == NULL) {
    return;
  } 
  
  ELEMENTO *aux;

  aux = li->inicio;

  if (aux == NULL) {
    printf("lista vazia");
  }

  while (aux != NULL){
    printf("%d ", aux->id);
    aux = aux->proximo;
  }
}


int remover_lista(LISTA *li, int id) {
  if (li == NULL) return 0;

  ELEMENTO *atual = li->inicio;
  ELEMENTO *anterior = NULL;
  while (atual != NULL && atual->id != id) {
    anterior = atual;
    atual = atual->proximo;
  }
  if (atual == NULL) return 0;

  if (anterior == NULL) li->inicio = atual->proximo;
  else anterior->proximo = atual->proximo;

  if (li->fim == atual) li->fim = anterior;
  free(atual);
  return 1;
}
