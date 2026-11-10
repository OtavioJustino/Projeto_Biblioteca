#include "../include/grafo.h"
#include "../include/fila.h"
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

static VERTICE *buscar_vertice(const GRAFO *grph, int id) {
  if (grph == NULL || id <= 0) return NULL;

  VERTICE *aux = grph->vertex;
  while (aux != NULL) {
    if (aux->id == id) return aux;
    aux = aux->prox_ver;
  }
  return NULL;
}

static ADJACENCIA *buscar_adjacencia(const VERTICE *vertice, int id) {
  ADJACENCIA *aux = vertice->adjacencias;
  while (aux != NULL) {
    if (aux->id == id) return aux;
    aux = aux->proximo;
  }
  return NULL;
}

static void liberar_adjacencias(ADJACENCIA *adj) {
  while (adj != NULL) {
    ADJACENCIA *proximo = adj->proximo;
    free(adj);
    adj = proximo;
  }
}

static int remover_adjacencia(VERTICE *vertice, int id) {
  ADJACENCIA *atual = vertice->adjacencias;
  ADJACENCIA *anterior = NULL;

  while (atual != NULL && atual->id != id) {
    anterior = atual;
    atual = atual->proximo;
  }
  if (atual == NULL) return 0;

  if (anterior == NULL) vertice->adjacencias = atual->proximo;
  else anterior->proximo = atual->proximo;

  free(atual);
  return 1;
}

GRAFO *criar_grafo(void) {
  GRAFO *p = malloc(sizeof(GRAFO));
  if (p == NULL) return NULL;

  p->vertex = NULL;
  return p;
}

void destruir_grafo(GRAFO *grph) {
  if (grph == NULL) return;

  VERTICE *atual = grph->vertex;
  while (atual != NULL) {
    VERTICE *proximo = atual->prox_ver;
    liberar_adjacencias(atual->adjacencias);
    free(atual);
    atual = proximo;
  }
  free(grph);
}

int add_vertice(GRAFO *grph, int id) {
  if (grph == NULL || id <= 0 || buscar_vertice(grph, id) != NULL) return 0;

  VERTICE *p = malloc(sizeof(VERTICE));
  if (p == NULL) return 0;

  p->id = id;
  p->adjacencias = NULL;
  p->prox_ver = grph->vertex;
  grph->vertex = p;
  return 1;
}

int rmv_vertice(GRAFO *grph, int id) {
  if (grph == NULL || id <= 0) return 0;

  VERTICE *atual = grph->vertex;
  VERTICE *anterior = NULL;
  while (atual != NULL && atual->id != id) {
    anterior = atual;
    atual = atual->prox_ver;
  }
  if (atual == NULL) return 0;

  VERTICE *aux = grph->vertex;
  while (aux != NULL) {
    if (aux != atual) remover_adjacencia(aux, id);
    aux = aux->prox_ver;
  }

  if (anterior == NULL) grph->vertex = atual->prox_ver;
  else anterior->prox_ver = atual->prox_ver;

  liberar_adjacencias(atual->adjacencias);
  free(atual);
  return 1;
}

int conexao_direta(const GRAFO *grph, int id1, int id2) {
  VERTICE *a = buscar_vertice(grph, id1);
  VERTICE *b = buscar_vertice(grph, id2);
  if (a == NULL || b == NULL) return 0;
  return buscar_adjacencia(a, id2) != NULL;
}

int add_conexao(GRAFO *grph, int id1, int id2) {
  if (id1 == id2) return 0;

  VERTICE *a = buscar_vertice(grph, id1);
  VERTICE *b = buscar_vertice(grph, id2);
  if (a == NULL || b == NULL || buscar_adjacencia(a, id2) != NULL) return 0;

  ADJACENCIA *ab = malloc(sizeof(ADJACENCIA));
  if (ab == NULL) return 0;
  ADJACENCIA *ba = malloc(sizeof(ADJACENCIA));
  if (ba == NULL) {
    free(ab);
    return 0;
  }

  ab->id = id2;
  ab->proximo = a->adjacencias;
  ba->id = id1;
  ba->proximo = b->adjacencias;
  a->adjacencias = ab;
  b->adjacencias = ba;
  return 1;
}

int rmv_conexao(GRAFO *grph, int id1, int id2) {
  if (id1 == id2) return 0;

  VERTICE *a = buscar_vertice(grph, id1);
  VERTICE *b = buscar_vertice(grph, id2);
  if (a == NULL || b == NULL || buscar_adjacencia(a, id2) == NULL) return 0;

  remover_adjacencia(a, id2);
  remover_adjacencia(b, id1);
  return 1;
}

/* Os IDs nao precisam ser sequenciais. */
static int indice_vertice(VERTICE **vertices, int quantidade, int id) {
  for (int i = 0; i < quantidade; i++) {
    if (vertices[i]->id == id) return i;
  }
  return -1;
}

static int percorrer_bfs(const GRAFO *grph, int origem, int destino, int listar) {
  if (buscar_vertice(grph, origem) == NULL) return 0;
  if (!listar && buscar_vertice(grph, destino) == NULL) return 0;

  int quantidade = 0;
  for (VERTICE *v = grph->vertex; v != NULL; v = v->prox_ver) quantidade++;

  VERTICE **vertices = malloc((size_t)quantidade * sizeof(VERTICE *));
  unsigned char *visitados = calloc((size_t)quantidade, sizeof(unsigned char));
  FILA *fila = criar_fila();
  if (vertices == NULL || visitados == NULL || fila == NULL) {
    free(vertices);
    free(visitados);
    destruir_fila(fila);
    return 0;
  }

  int i = 0;
  for (VERTICE *v = grph->vertex; v != NULL; v = v->prox_ver) {
    vertices[i++] = v;
  }

  int inicio = indice_vertice(vertices, quantidade, origem);
  visitados[inicio] = 1;
  if (!enfileirar(fila, origem)) {
    free(vertices);
    free(visitados);
    destruir_fila(fila);
    return 0;
  }

  int encontrado = 0;
  int atual;
  while (desenfileirar(fila, &atual)) {
    if (!listar && atual == destino) {
      encontrado = 1;
      break;
    }
    if (listar && atual != origem) printf("%d\n", atual);

    VERTICE *vertice = vertices[indice_vertice(vertices, quantidade, atual)];
    for (ADJACENCIA *adj = vertice->adjacencias; adj != NULL; adj = adj->proximo) {
      int pos = indice_vertice(vertices, quantidade, adj->id);
      if (pos >= 0 && !visitados[pos]) {
        visitados[pos] = 1;
        if (!enfileirar(fila, adj->id)) {
          free(vertices);
          free(visitados);
          destruir_fila(fila);
          return 0;
        }
      }
    }
  }

  free(vertices);
  free(visitados);
  destruir_fila(fila);
  return listar ? 1 : encontrado;
}

int listar_alcancaveis(const GRAFO *grph, int origem) {
  return percorrer_bfs(grph, origem, 0, 1);
}

int verificar_caminho(const GRAFO *grph, int origem, int destino) {
  return percorrer_bfs(grph, origem, destino, 0);
}
