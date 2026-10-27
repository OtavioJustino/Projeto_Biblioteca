#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/interface.h"
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

int ler_inteiro (int *numero) {
  long int temp;
  char *p; 
  char palavra[32];

  if (fgets(palavra, sizeof(palavra), stdin) == NULL) {
    return 0;
  }
  
  if (strchr(palavra, '\n') == NULL) {
    int auxC;
    while((auxC = getchar()) != '\n' && auxC != EOF);
    return 0;
  }
  
  errno = 0;

  temp = strtol(palavra, &p, 10); 
  if (p == palavra) {
    return 0;
  } else if (*p != '\n' && *p != '\0') {
    return 0;
  }
  
  if (errno == ERANGE || temp < INT_MIN || temp > INT_MAX) {
    return 0;
  }
  
  *numero = (int) temp;
  return 1;

}

int ler_texto(char *texto, size_t tamanho){

  if (fgets(texto, tamanho, stdin) == NULL){
    return 0;
  }

  if (strchr(texto, '\n') == NULL) {
    int auxD;
    while((auxD = getchar()) != '\n' && auxD != EOF);
    return 0;
  }

  if (tamanho <= 0 && tamanho >  {
    return 0;
  }
  
}


LIVROS *cadastrar_livro() {
  int id;
  char titulo[80]; 
  char autor[80];
  int ano;

  if (ler_inteiro(&id) != 1) {
    return NULL;
  }

  if (id <= 0) {
    return NULL;
  }

  if (ler_inteiro(&ano) != 1) {
    return NULL;
  }

  if (ano < 1 || ano > 2026) {
  return NULL; 
}


