#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/interface.h"
#include <limits.h>
#include <errno.h>
#include <ctype.h>

/* Apresenta as opcoes disponiveis ao usuario. */
void menu() {

  printf("=======================================================\n");
  printf("              BIBLIOTECA ESTRUTURA DE DADOS            \n");
  printf("=======================================================\n");
  printf(" 1 - Cadastrar Livro\n");
  printf(" 2 - Buscar Livros\n");
  printf(" 3 - Remover Livro\n");
  printf(" 4 - Listar Livros\n");
  printf(" 5 - Ordenar Livros por Titulo\n");
  printf(" 6 - Adicionar Conexao\n");
  printf(" 7 - Remover Conexao\n");
  printf(" 8 - Consultar Conexao Direta\n");
  printf(" 9 - Listar Alcancaveis\n");
  printf("10 - Verificar Caminho entre dois IDs\n");
  printf("11 - Consultar Historico\n");
  printf(" 0 - Encerrar\n");
  printf("=======================================================\n");
  printf("ESCOLHA UMA OPCAO: ");

}

/* Le um inteiro com fgets e strtol, verificando caracteres invalidos e limites de int. */
int ler_inteiro (int *numero) {
  if (numero == NULL) {
    return 0;
  }

  long int temp;
  char *p; 
  char palavra[32];

  if (fgets(palavra, sizeof(palavra), stdin) == NULL) {
    return 0;
  }
  
  /* Descarta o restante da linha se a entrada ultrapassar o buffer. */
  if (strchr(palavra, '\n') == NULL) {
    int auxC;
    auxC = getchar();
    if (auxC != '\n' && auxC != EOF){
      while(auxC != '\n' && auxC != EOF){
        auxC = getchar();
      }
      return 0;
    }
  }
  
  /* Zera errno antes da conversao para identificar estouro de intervalo. */
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

/* Le um texto com tamanho limitado e rejeita entradas vazias ou so com espacos. */
int ler_texto(char *texto, size_t tamanho){

  char *p;
  if (texto == NULL) {
    return 0;
  }

  if (tamanho < 2 || tamanho > 80) {
    return 0;
  }

  if (fgets(texto, tamanho, stdin) == NULL){
    return 0;
  }

  /* Descarta caracteres excedentes quando o texto ultrapassa o limite. */
  if (strchr(texto, '\n') == NULL) {
    int auxD;
    auxD = getchar();
    if (auxD != '\n' && auxD != EOF) {
      while(auxD != '\n' && auxD != EOF) {
        auxD = getchar();
      }
      return 0;
    }
  } else {
    p = strchr(texto, '\n');
    *p = '\0';
  }

  if (strlen(texto) == 0) {
    return 0;
  }
  size_t j = strlen(texto);

  for (size_t i = 0; i < j; i++) {
    if (isspace((unsigned char)texto[i]) == 0) {
      return 1;
    }
  }

  return 0;
  
}

/* Solicita os campos, valida cada entrada e cria o livro; retorna NULL em caso de erro. */
LIVROS *cadastrar_livro(void) {
  int id, ano;
  char titulo[80], autor[80];

  printf("ID: ");
  if (!ler_inteiro(&id) || id <= 0) return NULL;

  printf("Titulo: ");
  if (!ler_texto(titulo, sizeof titulo)) return NULL;

  printf("Autor: ");
  if (!ler_texto(autor, sizeof autor)) return NULL;

  printf("Ano: ");
  if (!ler_inteiro(&ano) || ano < 1 || ano > 2026) return NULL;

  return criar_livro(id, titulo, autor, ano);
}
