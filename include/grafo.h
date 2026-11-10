#ifndef grafo_h
#define grafo_h

typedef struct adjacencia ADJACENCIA;
typedef struct vertice VERTICE;
typedef struct grafo GRAFO;

GRAFO *criar_grafo(void);
void destruir_grafo(GRAFO *grafo);

int add_vertice(GRAFO *grafo, int id);
int rmv_vertice(GRAFO *grafo, int id);
int add_conexao(GRAFO *grafo, int id1, int id2);
int rmv_conexao(GRAFO *grafo, int id1, int id2);
int conexao_direta(const GRAFO *grafo, int id1, int id2);
int listar_alcancaveis(const GRAFO *grafo, int origem);
int verificar_caminho(const GRAFO *grafo, int origem, int destino);

#endif
