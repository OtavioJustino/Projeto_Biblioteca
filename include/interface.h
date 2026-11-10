#ifndef interface_h
#define interface_h

#include <stddef.h>
#include "livro.h"

void menu(void);
int ler_inteiro(int *numero);
int ler_texto(char *texto, size_t tamanho);
LIVROS *cadastrar_livro(void);

#endif
