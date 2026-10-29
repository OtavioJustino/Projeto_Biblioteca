#ifndef pilha_h
#define pilha_h
//last in first out 

typedef struct pilha PILHA;

typedef enum  {
  CADASTRO,
  REMOCAO,
  ADD_CONEXAO,
  RMV_CONEXAO,
} ACAO;


PILHA *criar_pilha();

void destruir_pilha(PILHA *pi);

int add_topo(PILHA *pi, ACAO tipo, int id1, int id2);

int rmv_topo(PILHA *pi, ACAO *tipo, int *id1, int *id2);

int ver_topo(const PILHA *pi,  ACAO *tipo,int *id1, int *id2);

void historico(const PILHA *pi);

#endif
