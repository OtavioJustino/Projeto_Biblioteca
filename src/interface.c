#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include <limits.h>
#include <errno.h>

void menu() {

  printf("=======================================================\n");
  printf("              BIBLIOTECA ESTRUTURA DE DADOS            \n");
  printf("=======================================================\n");
  printf(" 1 - Cadastrar Livro\n");
  printf(" 2 - Buscar Buscar Livros\n");
  printf(" 3 - Remover Livros e vertices/aresta\n");
  printf(" 4 - Listar Livros\n");
  printf(" 5 - Ordenar Livros por Titulo\n");
  printf(" 6 - Adicionar Conexao\n");
  printf(" 7 - Remover Conexao\n");
  printf(" 8 - Consultar Conexao Direta\n");
  printf(" 9 - Listar Alcacaveis\n");
  printf("10 - Verificar Caminho entre dois IDs\n");
  printf("11 - Consultar Historico\n");
  printf(" 0 - Encerrar\n");
  printf("=======================================================\n");
  printf("ESCOLHA UMA OPCAO: ");

}

LIVROS *cadastrar_livro() {
  int id;
  char titulo[80]; 
  char autor[80];
  int ano;
  char entrada[32];
  char *p;
  long int temp;


  if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
    return NULL;
  }


  errno = 0;

  temp = strtol(entrada, &p, 10);
  if (p == entrada) {
    return NULL;
  } else if (*p != '\n' && *p!='\O') {
    return NULL;
  }

  
  if (errno == ERANGE || temp < INT_MIN || temp > INT_MAX){
    return NULL;
  }
  
  id = (int) temp; 

  if (strchr(entrada, '\n') == NULL) {
    int auxC;
    while ((auxC =getchar()) != '\n' && auxC != EOF);
    return NULL;
  }


}


