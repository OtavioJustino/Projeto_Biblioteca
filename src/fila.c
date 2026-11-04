#include "../include/fila.h"
#include <stdlib.h>

typedef struct elemento ELEMENTO;

struct fila {
  ELEMENTO *inicio;
  ELEMENTO *fim;
};

struct elemento {
  ELEMENTO *proximo;
  int id;
};

FILA *criar_fila() {
  FILA *p = malloc(sizeof(FILA));

  if (p == NULL) {
    return NULL;
  }

  p->inicio = NULL;
  p->fim = NULL;

  return p;
}


void destruir_fila(FILA *fi) { 
  if (fi == NULL) {
    return;
  }

  ELEMENTO *aux_1;

  ELEMENTO *aux_2;

  aux_1 = fi->inicio;
  
  while (aux_1 != NULL) {
    aux_2 = aux_1->proximo;
    free(aux_1);
    aux_1 = aux_2;
  }

  free(fi);
}

int enfileirar(FILA *fi, int id) {
  if (fi == NULL) {
    return 0;
  }

  ELEMENTO *p = malloc(sizeof(ELEMENTO)); 
  if (p == NULL) {
    return 0;
  }

  p->id = id;
  p->proximo = NULL;

  if (fi-> inicio != NULL) {
    fi->fim->proximo = p;
    fi->fim = p;
    return 1;
  } else {
    fi->inicio = p;
    fi->fim = p;
    return 1;
  }
}

int desenfileirar(FILA *fi, int *id) {
  if (fi == NULL) {
    return 0;
  }

  ELEMENTO *aux;

  if (id == NULL) {
    return 0;
  }

  aux = fi->inicio;
  if ( aux == NULL) {
    return 0;
  }

  *id = aux->id;

  if (aux->proximo == NULL) {
    fi->fim = NULL;
  }
  fi->inicio = aux->proximo;
  free(aux);

  return 1;
}

int consultar_inicio(const FILA *fi, int *id) {
  if (fi == NULL || id == NULL) {
    return 0;
  }

  if (fi->inicio == NULL) {
    return 0;
  }

  *id = fi->inicio->id;

  return 1;
}
