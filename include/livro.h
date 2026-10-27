#ifndef livro_h
#define livro_h

typedef struct livros LIVROS;

LIVROS *criar_livro(int id, char titulo[], char autor[], int ano);

void destruir_livro(LIVROS *livro);

int obter_id(const LIVROS *livro);

int obter_ano(const LIVROS *livro);

const char *obter_titulo(const LIVROS *livro);

const char *obter_autor(const LIVROS *livro);

void exibir_livro(const LIVROS *livro);


#endif

