#ifndef fila_h
#define fila_h

typedef struct fila FILA;

FILA *criar_fila();

void destruir_fila(FILA *fi);

int enfileirar(FILA *fi, int id);

int desenfileirar(FILA *fi, int *id);

int consultar_inicio(const FILA *fi, int *id);

#endif
