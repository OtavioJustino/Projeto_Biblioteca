#include "livro.h" 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h>


struct livros {
  int id;
  char titulo[80];
  char autor[80];
  int ano;
};

LIVROS *criar_livro(int id, char titulo[], char autor[], int ano) {
  LIVROS *p = malloc(sizeof(LIVROS));

  if (p != NULL) {
    if (id > 0 ) {
      p->id = id;
    } else {
      free(p);
      return NULL;
    }

    if (strelen(titulo) > 0 && strlen(titulo) <=79) {  
      
    }


    if (ano >=1 && ano <=2026) {
      p->ano = ano; 
    }else {
      free(p);
      return NULL;
    }

    return p;

  } else {
     return NULL; 
  }
}
