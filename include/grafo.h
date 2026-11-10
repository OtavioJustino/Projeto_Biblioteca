#ifndef grafo_h
#define grafo_h

typedef struct adjacencia ADJACENCIA;

typedef struct grafo GRAFO;

typedef struct vertice VERTICE;

GRAFO *criar_grafo();

void destruir_grafo(GRAFO* grafo);

int add_vertice(GRAFO *grafo, int id);

int rmv_vertice(GRAFO *grafo, int id);

#endif
