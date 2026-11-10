#include "../include/grafo.h"
#include <stdio.h>
#include <stdlib.h>

struct adjacencia {
  int id;
  ADJACENCIA *proximo;
};

struct vertice {
  int id;
  ADJACENCIA *adjacencias;
  VERTICE *prox_ver;
};

struct grafo {
  VERTICE *vertex;
};

GRAFO *criar_grafo(){
  GRAFO *p = malloc(sizeof(GRAFO));
  if (p == NULL) {
    return NULL;
  }
  
  p->vertex = NULL;
  return p;
}

void destruir_grafo(GRAFO *grph) {
  if (grph == NULL) {
    return;
  }
  
  VERTICE *aux_1;
  VERTICE *aux_2;
  ADJACENCIA *aux_3;
  ADJACENCIA *aux_4;

  aux_1 = grph->vertex;

  while (aux_1 != NULL) {  
    aux_2 = aux_1->prox_ver;
    aux_3 = aux_1->adjacencias;
    while (aux_3 != NULL) {
      aux_4 = aux_3->proximo;
      free(aux_3);
      aux_3 = aux_4;
    }
    free(aux_1);
    aux_1 = aux_2;
  }

  free(grph);
}

int add_vertice(GRAFO *grph, int id) {
  if (grph == NULL && id > 0) {
    return 0;
  }  

  VERTICE *aux;
  aux = grph->vertex;
  
  while (aux != NULL) {
    if (aux->id == id) {
      return 0;
    } else {
      aux = aux->prox_ver;
    }
  }

  VERTICE *p = malloc(sizeof(VERTICE));

  if (p == NULL) {
    return 0;
  }

  p->id = id;
  p->adjacencias = NULL;
  p->prox_ver = grph->vertex;
  grph->vertex = p;

  return 1;

}

int rmv_vertice(GRAFO *grph, int id) {
  if (grph == NULL) {
    return 0;
  }

  VERTICE *atual;
  VERTICE *anterior;

  atual = grph->vertex;
  anterior = NULL;

  while (atual != NULL && atual->id != id) {
    anterior = atual;
    atual = atual->prox_ver;
  }

  if (atual == NULL) {
    return 0;
  }

  VERTICE *aux;

  aux = grph->vertex;

  while (aux != NULL) {
    ADJACENCIA *adj_atual;
    adj_atual = aux->adjacencias;
    ADJACENCIA *adj_anterior;
    adj_anterior = NULL;
    while (adj_atual != NULL && adj_atual->id != id) {
      adj_anterior = adj_atual;
      adj_atual = adj_atual->proximo;
    }
    if (adj_atual != NULL) {
      aux->adjacencias = adj_atual->proximo;
    } else {
      adj_anterior->proximo = adj_atual->proximo; 
    }
    

    free(adj_atual);
    

  }


}



