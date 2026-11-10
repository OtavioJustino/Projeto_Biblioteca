#include "../include/arvore.h"
#include "../include/livro.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct elemento ELEMENTO;

struct elemento {
  LIVROS *livro;
  ELEMENTO *esquerda;
  ELEMENTO *direita;
};

struct arvore {
  ELEMENTO *raiz;
};


/* Cria a estrutura da BST com a raiz inicialmente vazia. */
ARVORE *cria_arvore() {
  ARVORE *p = malloc(sizeof(ARVORE));

  if (p == NULL) {
    return NULL;
  }

  p->raiz = NULL;

  return p;
}

/* Libera recursivamente os filhos, o livro e o no atual. */
static void destruir_recursiva(ELEMENTO *elemento) {
  if (elemento == NULL) {
    return ;
  }
  
  destruir_recursiva(elemento->esquerda);
  destruir_recursiva(elemento->direita);
  free(elemento->livro);
  free(elemento);
  
}

/* Desaloca todos os nos e a estrutura de controle da arvore. */
void destruir_arvore(ARVORE *tree) {
  if (tree == NULL) {
    return;
  }

  destruir_recursiva(tree->raiz);
  free(tree);
}


/* Insere o livro pela ordem dos IDs, rejeitando IDs duplicados. */
int inserir_livro(ARVORE *tree, LIVROS *livro) {
  if (tree == NULL || livro == NULL) {
    return 0;
  }

  ELEMENTO *p = malloc(sizeof(ELEMENTO));

  if (p == NULL) {
    return 0;
  }

  p->livro = livro;
  p->esquerda = NULL; 
  p->direita = NULL; 
  

  if (tree->raiz == NULL ){
    tree->raiz = p;
    return 1;
  }
  
  int id = obter_id(livro);
  if (id < 0) {
    free(p);
    return 0;
  }
  
  ELEMENTO *atual = tree->raiz;

  
while (atual != NULL) {
    int id_atual = obter_id(atual->livro);

    if (id == id_atual) {
        free(p);
        return 0;
    }

    if (id > id_atual) {
        if (atual->direita == NULL) {
            atual->direita = p;
            break;
        }

        atual = atual->direita;
    } else {
        if (atual->esquerda == NULL) {
            atual->esquerda = p;
            break;
        }

        atual = atual->esquerda;
    }
}

  return 1;

}

/* Busca o livro comparando IDs e seguindo o filho esquerdo ou direito. */
LIVROS *busca_livro(const ARVORE *tree, int id){
  if (tree == NULL || tree->raiz == NULL || id <= 0) {
    return NULL;
  }

  ELEMENTO *aux;


  aux = tree->raiz;

  while (aux != NULL) {
    int atual = obter_id(aux->livro);

    if (id == atual) {
      return aux->livro;
    }

    if (id > atual) {
      aux = aux->direita;
    } else {
      aux = aux->esquerda;
    }
  }

  return NULL;
}

/* Encontra o maior ID percorrendo os filhos a direita. */
int maior_id(const ARVORE *tree) {
  if (tree == NULL || tree->raiz ==  NULL) {
    return 0;
  }

  ELEMENTO *aux = tree->raiz;

  while (aux->direita != NULL) {
    aux = aux->direita;
  }
  
  return obter_id(aux->livro);

}

/* Encontra o menor ID percorrendo os filhos a esquerda. */
int menor_id(const ARVORE *tree) {
  if (tree == NULL || tree->raiz == NULL) {
    return 0;
  }

  ELEMENTO *aux = tree->raiz;

  while (aux->esquerda != NULL) {
    aux = aux->esquerda;
  }

  return obter_id(aux->livro);

}

/* Percorre a BST em ordem, exibindo os livros por ID crescente. */
static void listar_recursivo(ELEMENTO *elemento){
  if (elemento == NULL) {
    return;
  }

  listar_recursivo(elemento->esquerda);
  exibir_livro(elemento->livro);
  putchar('\n');
  
  listar_recursivo(elemento->direita);

}

/* Inicia a listagem em ordem a partir da raiz. */
void listar_ordem(ARVORE *tree) {
  if (tree == NULL || tree->raiz == NULL) {
    return;
  }

  listar_recursivo(tree->raiz);
}

/* Remove um livro tratando os casos de folha, um filho e dois filhos. */
int remover_livro(ARVORE *tree, int id) {
  if (tree == NULL || id <= 0) {
    return 0;
  }

  ELEMENTO *atual = tree->raiz;
  ELEMENTO *pai = NULL;

  while (atual != NULL) {

    if (id == obter_id(atual->livro)) {
      break;
    } else {
      pai = atual;

      if (id > obter_id(atual->livro)){
        atual = atual->direita;
      } else {
        atual = atual->esquerda;
      }
    }
  }

  if (atual == NULL) {
    return 0;
  }

  /* Caso 1: desliga e libera um no que nao possui filhos. */
  if (atual->esquerda == NULL && atual->direita == NULL) {
    if(pai == NULL) {
      tree->raiz = NULL;
    } else if(pai->esquerda == atual) 
    {
      pai->esquerda = NULL;
    } else 
    {
      pai->direita = NULL;
    }

    free(atual->livro);
    free(atual);
    return 1;
  }

  ELEMENTO *filho = NULL;

  if (atual->esquerda != NULL && atual->direita == NULL) {
    filho = atual->esquerda;
  } else if(atual->esquerda == NULL && atual->direita != NULL) {
    filho =  atual->direita;
  }

  /* Caso 2: substitui o no pelo seu unico filho. */
  if(filho != NULL) {
    if (pai == NULL ) {
      tree->raiz = filho;
    } else if (pai->esquerda == atual)
    {
      pai->esquerda = filho;
    } else 
    {
      pai->direita = filho;
    }
    free(atual->livro);
    free(atual);
    return 1;
  }

  
  /* Caso 3: encontra o sucessor em ordem na subarvore direita. */
  if (atual->esquerda != NULL && atual->direita != NULL){
    ELEMENTO *sucessor = atual->direita;
    ELEMENTO *pai_sucessor = atual;
    while (sucessor->esquerda != NULL) {
      pai_sucessor = sucessor;
      sucessor = sucessor->esquerda;
    } 
    
    LIVROS *aux = atual->livro;
    atual->livro = sucessor->livro;
    sucessor->livro = aux;

    if (pai_sucessor == atual) {
      atual->direita = sucessor->direita;
    } else {
      pai_sucessor->esquerda = sucessor->direita;
    }
    
    free(sucessor->livro);
    free(sucessor);
    return 1;
  }

  return 0;
}

/* Conta recursivamente os nos das duas subarvores e o no atual. */
static int auxiliar_ordem(ELEMENTO *elemento) {
  if (elemento == NULL) {
    return 0;
  }

  return 1 + auxiliar_ordem(elemento->esquerda) + auxiliar_ordem(elemento->direita);


}

/* Retorna a quantidade de livros armazenados na BST. */
int contar_livros(const ARVORE *tree) {
  if (tree == NULL) {
    return 0;
  }

  return auxiliar_ordem(tree->raiz);
}

/* Visita os livros em ordem e executa a funcao recebida em cada um. */
static void auxiliar_percorrer (ELEMENTO *elemento,  void (*visitar) (const LIVROS *, void *), void *contexto) {
  if (elemento == NULL) {
    return;
  }
  
  auxiliar_percorrer(elemento->esquerda, visitar, contexto);

  visitar(elemento->livro, contexto);

  auxiliar_percorrer(elemento->direita, visitar, contexto); 
}

/* Percorre os livros usando uma funcao de visita fornecida pelo chamador. */
void percorrer_livros(const ARVORE *tree, void (*visitar)(const LIVROS *, void *), void *contexto) {
  if (tree == NULL || tree->raiz == NULL || visitar == NULL) {
    return;
  }

  auxiliar_percorrer(tree->raiz, visitar, contexto);
}
