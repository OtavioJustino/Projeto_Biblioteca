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

LIVROS *criar_livro(int id, char titulo[], char autor[], int ano) {
  LIVROS *p = malloc(sizeof(LIVROS));//alocaçao de memoria para um ponteiro LIVROS *

  if (p != NULL) { //Verifica se foi possivel a alocação de memoria

    //validação de id (funciona se id > 0) 
    if (id > 0 ) {
      p->id = id;
    } else {
      free(p);
      return NULL;
    }
    
    /*validação de titulo, caso o titulo seja > 0 e <= 79 
     * inicia uma variavel de controle booleana 
     * cria um laço de repetição para verificar casa por casa
     * se houver pelo menos 1 (um) caractere diferente de espaço
     * a variavel de controle se torna verdadeira
     * e a estrutura (for) é finalizada pois o titulo é valido*/
    if (titulo != NULL && strlen(titulo) > 0 && strlen(titulo) <=79) {  
      size_t i;
      bool controle = false;
      for (i = 0; i < strlen(titulo); i++){

        if (isspace(titulo[i]) == false) {
          controle = true;
          break;
        }
      }
      
      /*verifica se o controle permanece falso
      *se permanecer libera a memoria*/
      if (controle == false) {
        free(p);
        return NULL;
      }

      strcpy(p->titulo, titulo); 
    
    } else {
      /*caso a primeira verificação de tamanho nao seja correspondida
       * libera a memoria e retorna NULL*/
      free(p);
      return NULL;
    }
    
    //valida o autor utilizando os mesmos criterios da validação de titulo
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

  } else { //caso a alocação de memoria falhe, retorna NULL
    return NULL; 
  }
}

void destruir_livro(LIVROS *livro) {
  if(livro != NULL) {
    free(livro);
  }
} 

int obter_id(const LIVROS *livro) {
  if (livro == NULL) {
    return -1;
  }
  
  return livro->id;
}

int obter_ano(const LIVROS *livro) {
  if (livro == NULL) {
    return -1;
  }
  
  return livro->ano;
}

const char *obter_titulo(const LIVROS *livro){
  if (livro == NULL) {
    return NULL;
  }

  return livro->titulo;
}

const char *obter_autor(const LIVROS *livro) {
  if (livro == NULL) {
    return NULL;
  }

  return livro->autor;
}

void exibir_livro(const LIVROS *livro) {
  if (livro == NULL) {
    return;
  }

  printf("%d\n", livro->id);

  printf("%s\n", livro->titulo);

  printf("%s\n", livro->autor);

  printf("%d\n", livro->ano);

}

