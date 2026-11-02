#include "../include/pilha.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct elemento ELEMENTO;

struct pilha {
  ELEMENTO *topo;
};

struct elemento {
  int id1, id2;
  ACAO tipo;
  ELEMENTO *proximo;
};

PILHA* criar_pilha() {
  PILHA *p = malloc(sizeof(PILHA));
  if (p == NULL) {
    return NULL;
  }

  p->topo = NULL;

  return p;
}

void destruir_pilha(PILHA *pi) {
  if (pi == NULL) {
    return;
  }
  
  ELEMENTO *aux_1, *aux_2;

  aux_1 = pi->topo;

  while (aux_1 != NULL) {
    aux_2 = aux_1->proximo;
    free(aux_1);
    aux_1 = aux_2;
  }

  free(pi);

}

int add_topo(PILHA *pi, ACAO tipo, int id1, int id2) {
  if (pi == NULL) {
    return 0;
  }

  ELEMENTO *p = malloc(sizeof(ELEMENTO));
    if(p == NULL) {
      return 0;
    }

  p->id1 = id1;
  p->id2 = id2;
  p->tipo = tipo;
  p->proximo = NULL;

  p->proximo = pi->topo;
  pi->topo = p;
 
  return 1;

}

int rmv_topo(PILHA *pi, ACAO *tipo, int *id1, int *id2) {
  if (pi == NULL) {
    return 0;
  }

  ELEMENTO *aux;

  if (tipo == NULL || id1 == NULL || id2 == NULL){
    return 0;
  }

  aux = pi->topo;
  if (aux == NULL) {
    return 0;
  }

  *id1 = aux->id1;
  *id2 = aux->id2;
  *tipo = aux->tipo;

  pi->topo = aux->proximo;
  free(aux);

  return 1;
  
}

int ver_topo(const PILHA *pi, ACAO *tipo, int *id1, int *id2) {
    if (pi == NULL || tipo == NULL || id1 == NULL || id2 == NULL) {
        return 0;
    }

    if (pi->topo == NULL) {
        return 0;
    }

    *tipo = pi->topo->tipo;
    *id1 = pi->topo->id1;
    *id2 = pi->topo->id2;

    return 1;
}

void historico(const PILHA *pi) {
  if (pi == NULL || pi->topo == NULL) {
    return;
  }
  
  ELEMENTO *aux;
  int contador = 0;

  aux = pi->topo;

  while (aux != NULL && contador < 5) {
    switch (aux->tipo) {
      case CADASTRO : printf("Cadastro: %d\n", aux->id1);
        break;
      case REMOCAO: printf("Remoção: %d\n", aux->id1);
        break;
      case ADD_CONEXAO: printf("Conexão Adicionada: IDs %d e %d\n", aux->id1, aux->id2);
        break;
      case RMV_CONEXAO: printf("Conexão Removida: IDs %d e %d\n", aux->id1, aux->id2);
        break;
    }
    aux = aux->proximo;
    contador++;
  }

}
