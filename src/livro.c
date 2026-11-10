#include "../include/livro.h" 
#include <stddef.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h>
#include <stdbool.h>

struct livros {
  int id;
  char titulo[80];
  char autor[80];
  int ano;
};

/* Aloca e inicializa um livro, validando ID, titulo, autor e ano.
 * Retorna NULL quando algum dado e invalido ou a alocacao falha. */
LIVROS *criar_livro(int id, char titulo[], char autor[], int ano) {
  LIVROS *p = malloc(sizeof(LIVROS));

  if (p != NULL) {

    /* Um ID valido deve ser positivo. */
    if (id > 0 ) {
      p->id = id;
    } else {
      free(p);
      return NULL;
    }
    
    /* Valida o tamanho do titulo e verifica se existe
     * pelo menos um caractere diferente de espaco. */
    if (titulo != NULL && strlen(titulo) > 0 && strlen(titulo) <=79) {  
      size_t i;
      bool controle = false;
      for (i = 0; i < strlen(titulo); i++){

        if (isspace(titulo[i]) == false) {
          controle = true;
          break;
        }
      }
      
      /* Rejeita titulos compostos apenas por espacos em branco. */
      if (controle == false) {
        free(p);
        return NULL;
      }

      strcpy(p->titulo, titulo); 
    
    } else {
      /* Libera a memoria se o titulo nao atender aos limites definidos. */
      free(p);
      return NULL;
    }
    
    /* Aplica ao autor os mesmos criterios de validacao do titulo. */
    if (autor != NULL && strlen(autor) > 0 && strlen(autor) <=79){
      size_t i; 
      bool controle = false;
      for (i = 0; i < strlen(autor); i++) {

       if (isspace(autor[i]) == false) {
        controle = true;
        break;
        }
      }

      if (controle == false) {
        free(p);
        return NULL;
      }

      strcpy(p->autor, autor);

    } else {
      free(p);
      return NULL;
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

/* Libera a memoria alocada para um livro, se o ponteiro for valido. */
void destruir_livro(LIVROS *livro) {
  if(livro != NULL) {
    free(livro);
  }
} 

/* Retorna o ID do livro ou -1 se o ponteiro for NULL. */
int obter_id(const LIVROS *livro) {
  if (livro == NULL) {
    return -1;
  }
  
  return livro->id;
}

/* Retorna o ano do livro ou -1 se o ponteiro for NULL. */
int obter_ano(const LIVROS *livro) {
  if (livro == NULL) {
    return -1;
  }
  
  return livro->ano;
}

/* Retorna o titulo do livro ou NULL se o ponteiro for invalido. */
const char *obter_titulo(const LIVROS *livro){
  if (livro == NULL) {
    return NULL;
  }

  return livro->titulo;
}

/* Retorna o autor do livro ou NULL se o ponteiro for invalido. */
const char *obter_autor(const LIVROS *livro) {
  if (livro == NULL) {
    return NULL;
  }

  return livro->autor;
}

/* Exibe os dados do livro sem modificar seu conteudo. */
void exibir_livro(const LIVROS *livro) {
  if (livro == NULL) {
    return;
  }

  printf("ID:     %d\n", livro->id);
  printf("Titulo: %s\n", livro->titulo);
  printf("Autor:  %s\n", livro->autor);
  printf("Ano:    %d\n", livro->ano);

}

