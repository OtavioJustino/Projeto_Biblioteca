#include "../include/pilha.h"
#include <stdio.h>
#include <stdlib.h>

/* Define o tipo ELEMENTO para representar cada registro armazenado na pilha. */
typedef struct elemento ELEMENTO;

/* A pilha guarda um ponteiro para o elemento do topo. */
struct pilha {
  ELEMENTO *topo;
};

/* Cada elemento armazena o tipo da acao, os IDs envolvidos e o proximo registro. */
struct elemento {
  int id1, id2;
  ACAO tipo;
  ELEMENTO *proximo;
};

/* Cria uma pilha vazia, alocando memoria para sua estrutura de controle.
 * Retorna NULL caso a alocacao falhe. */
PILHA* criar_pilha() {
  PILHA *p = malloc(sizeof(PILHA));
  if (p == NULL) {
    return NULL;
  }

  /* Inicializa o topo com NULL, indicando que ainda nao existem elementos. */
  p->topo = NULL;

  return p;
}

/* Percorre todos os elementos da pilha, liberando cada registro
 * antes de liberar a estrutura de controle. */
void destruir_pilha(PILHA *pi) {
  if (pi == NULL) {
    return;
  }
  
  ELEMENTO *aux_1, *aux_2;

  aux_1 = pi->topo;

  /* Guarda o proximo elemento antes de liberar o atual,
   * evitando acessar uma regiao de memoria ja liberada. */
  while (aux_1 != NULL) {
    aux_2 = aux_1->proximo;
    free(aux_1);
    aux_1 = aux_2;
  }

  free(pi);

}

/* Adiciona uma nova acao ao topo da pilha.
 * Retorna 1 em caso de sucesso e 0 quando nao for possivel inserir. */
int add_topo(PILHA *pi, ACAO tipo, int id1, int id2) {
  if (pi == NULL) {
    return 0;
  }

  ELEMENTO *p = malloc(sizeof(ELEMENTO));
    if(p == NULL) {
      return 0;
    }

  p->id1 = id1;
  p->id2 = id2;
  p->tipo = tipo;
  p->proximo = NULL;

  /* O novo elemento aponta para o topo anterior,
   * preservando a ordem LIFO (ultimo a entrar, primeiro a sair). */
  p->proximo = pi->topo;
  pi->topo = p;
 
  return 1;

}

/* Remove o elemento do topo e devolve seus dados pelos parametros ponteiro.
 * Retorna 0 se a pilha estiver vazia ou os parametros forem invalidos. */
int rmv_topo(PILHA *pi, ACAO *tipo, int *id1, int *id2) {
  if (pi == NULL) {
    return 0;
  }

  ELEMENTO *aux;

  if (tipo == NULL || id1 == NULL || id2 == NULL){
    return 0;
  }

  aux = pi->topo;
  if (aux == NULL) {
    return 0;
  }

  *id1 = aux->id1;
  *id2 = aux->id2;
  *tipo = aux->tipo;

  /* Atualiza o topo para o elemento seguinte e libera o antigo topo. */
  pi->topo = aux->proximo;
  free(aux);

  return 1;
  
}

/* Consulta os dados da ultima acao sem remover o elemento da pilha.
 * Retorna 1 quando existe um topo valido e 0 caso contrario. */
int ver_topo(const PILHA *pi, ACAO *tipo, int *id1, int *id2) {
    if (pi == NULL || tipo == NULL || id1 == NULL || id2 == NULL) {
        return 0;
    }

    if (pi->topo == NULL) {
        return 0;
    }

    *tipo = pi->topo->tipo;
    *id1 = pi->topo->id1;
    *id2 = pi->topo->id2;

    return 1;
}

/* Exibe as cinco modificacoes mais recentes, comecando pelo topo.
 * A consulta nao altera nem remove os registros armazenados. */
void historico(const PILHA *pi) {
  if (pi == NULL || pi->topo == NULL) {
    return;
  }
  
  ELEMENTO *aux;
  int contador = 0;

  aux = pi->topo;

  /* Percorre no maximo cinco elementos, identificando a operacao
   * pelo valor do enum ACAO armazenado em cada registro. */
  while (aux != NULL && contador < 5) {
    switch (aux->tipo) {
      case CADASTRO : printf("Cadastro: %d\n", aux->id1);
        break;
      case REMOCAO: printf("Remoção: %d\n", aux->id1);
        break;
      case ADD_CONEXAO: printf("Conexão Adicionada: IDs %d e %d\n", aux->id1, aux->id2);
        break;
      case RMV_CONEXAO: printf("Conexão Removida: IDs %d e %d\n", aux->id1, aux->id2);
        break;
    }
    aux = aux->proximo;
    contador++;
  }

}
