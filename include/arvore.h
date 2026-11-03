#include "livro.h"
#ifndef arvore_h
#define arvore_h

typedef struct arvore ARVORE;

ARVORE *cria_arvore();

int inserir_livro(ARVORE *tree, LIVROS* livro);

#endif
