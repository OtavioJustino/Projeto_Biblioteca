#ifndef lista_h
#define lista_h

typedef struct lista LISTA;

LISTA *criar_lista();

void destruir_lista(LISTA *li);

int inserir_fim(LISTA *li, int id);

void exibir_lista(const LISTA *li);


#endif
