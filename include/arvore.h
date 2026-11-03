#include "livro.h"
#ifndef arvore_h
#define arvore_h

typedef struct arvore ARVORE;

ARVORE *cria_arvore();

void destruir_arvore(ARVORE *tree);

int inserir_livro(ARVORE *tree, LIVROS* livro);

LIVROS *busca_livro(const ARVORE *tree, int id);

int menor_id(const ARVORE *tree);

int maior_id(const ARVORE *tree);

void listar_ordem(ARVORE *tree);

int remover_livro(ARVORE *tree, int id);

#endif
