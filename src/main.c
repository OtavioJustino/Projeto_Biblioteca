#include <stdio.h>
#include <stdlib.h>
#include "../include/arvore.h"
#include "../include/grafo.h"
#include "../include/interface.h"
#include "../include/lista.h"
#include "../include/ordenacao.h"
#include "../include/pilha.h"

/* Limpa o terminal conforme o sistema operacional. */
static void limpar_tela(void) {
  #ifdef _WIN32
  system("cls");
  #else
  system("clear");
  #endif
}

/* Aguarda o ENTER para permitir a leitura do resultado antes de voltar ao menu. */
static void aguardar_enter(void) {
  int caractere;
  printf("\nPressione ENTER para voltar ao menu...");
  fflush(stdout);
  while ((caractere = getchar()) != '\n' && caractere != EOF) { }
}

/* Solicita e valida um ID inteiro positivo. */
static int ler_id(const char *mensagem, int *id) {
  printf("%s", mensagem);
  return ler_inteiro(id) && *id > 0;
}

/* Inicializa as estruturas e controla as operacoes do menu principal. */
int main(void) {
  ARVORE *arvore = cria_arvore();
  GRAFO *grafo = criar_grafo();
  LISTA *lista = criar_lista();
  PILHA *pilha = criar_pilha();

  /* Se alguma inicializacao falhar, libera as estruturas ja criadas. */
  if (arvore == NULL || grafo == NULL || lista == NULL || pilha == NULL) {
    puts("Erro ao inicializar as estruturas.");
    /* Libera as estruturas antes de encerrar o programa. */
  destruir_pilha(pilha);
    destruir_lista(lista);
    destruir_grafo(grafo);
    destruir_arvore(arvore);
    return 1;
  }

  int opcao;
  for (;;) {
    limpar_tela();
    menu();
    if (!ler_inteiro(&opcao)) {
      if (feof(stdin)) break;
      puts("Opcao invalida.");
      aguardar_enter();
      continue;
    }
    if (opcao == 0) break;

    limpar_tela();
    int id1, id2;
    switch (opcao) {
  /* O cadastro atualiza lista, grafo e BST; em caso de falha, desfaz etapas anteriores. */
      case 1: {
        LIVROS *livro = cadastrar_livro();
        if (livro == NULL) {
          puts("Dados invalidos.");
          break;
        }
        id1 = obter_id(livro);
        if (busca_livro(arvore, id1) != NULL) {
          destruir_livro(livro);
          puts("Este ID ja esta cadastrado.");
          break;
        }
        if (!inserir_fim(lista, id1)) {
          destruir_livro(livro);
          puts("Erro ao atualizar a lista.");
          break;
        }
        if (!add_vertice(grafo, id1)) {
          remover_lista(lista, id1);
          destruir_livro(livro);
          puts("Erro ao adicionar o vertice.");
          break;
        }
        if (!inserir_livro(arvore, livro)) {
          rmv_vertice(grafo, id1);
          remover_lista(lista, id1);
          destruir_livro(livro);
          puts("Erro ao cadastrar o livro.");
          break;
        }
        if (!add_topo(pilha, CADASTRO, id1, 0))
          puts("Aviso: nao foi possivel registrar a acao no historico.");
        puts("Livro cadastrado com sucesso.");
        break;
      }
      case 2: {
        if (!ler_id("ID do livro: ", &id1)) {
          puts("ID invalido.");
          break;
        }
        LIVROS *livro = busca_livro(arvore, id1);
        if (livro == NULL) puts("Livro nao encontrado.");
        else exibir_livro(livro);
        break;
      }
  /* A remocao retira o livro e as referencias correspondentes nas outras estruturas. */
      case 3:
        if (!ler_id("ID do livro: ", &id1)) {
          puts("ID invalido.");
          break;
        }
        if (busca_livro(arvore, id1) == NULL) {
          puts("Livro nao encontrado.");
          break;
        }
        if (remover_livro(arvore, id1)) {
          rmv_vertice(grafo, id1);
          remover_lista(lista, id1);
          if (!add_topo(pilha, REMOCAO, id1, 0))
            puts("Aviso: nao foi possivel registrar a acao no historico.");
          puts("Livro removido com sucesso.");
        } else {
          puts("Erro ao remover o livro.");
        }
        break;
      case 4:
        if (contar_livros(arvore) == 0) puts("Nenhum livro cadastrado.");
        else listar_ordem(arvore);
        break;
      case 5:
        if (contar_livros(arvore) == 0) puts("Nenhum livro cadastrado.");
        else ordenar_por_titulo(arvore);
        break;
      case 6:
        if (!ler_id("Primeiro ID: ", &id1) ||
            !ler_id("Segundo ID: ", &id2)) {
          puts("ID invalido.");
          break;
        }
        if (add_conexao(grafo, id1, id2)) {
          if (!add_topo(pilha, ADD_CONEXAO, id1, id2))
            puts("Aviso: nao foi possivel registrar a acao no historico.");
          puts("Conexao adicionada.");
        } else {
          puts("Nao foi possivel adicionar a conexao.");
        }
        break;
      case 7:
        if (!ler_id("Primeiro ID: ", &id1) ||
            !ler_id("Segundo ID: ", &id2)) {
          puts("ID invalido.");
          break;
        }
        if (rmv_conexao(grafo, id1, id2)) {
          if (!add_topo(pilha, RMV_CONEXAO, id1, id2))
            puts("Aviso: nao foi possivel registrar a acao no historico.");
          puts("Conexao removida.");
        } else {
          puts("Conexao inexistente.");
        }
        break;
      case 8:
        if (!ler_id("Primeiro ID: ", &id1) ||
            !ler_id("Segundo ID: ", &id2)) {
          puts("ID invalido.");
          break;
        }
        puts(conexao_direta(grafo, id1, id2)
             ? "Existe conexao direta." : "Nao existe conexao direta.");
        break;
      case 9:
        if (!ler_id("ID de origem: ", &id1)) {
          puts("ID invalido.");
          break;
        }
        puts("IDs alcancaveis:");
        if (!listar_alcancaveis(grafo, id1))
          puts("Vertice nao encontrado ou falha ao percorrer o grafo.");
        break;
      case 10:
        if (!ler_id("Primeiro ID: ", &id1) ||
            !ler_id("Segundo ID: ", &id2)) {
          puts("ID invalido.");
          break;
        }
        puts(verificar_caminho(grafo, id1, id2)
             ? "Existe um caminho." : "Nao existe caminho.");
        break;
      case 11:
        puts("Ultimas cinco modificacoes:");
        historico(pilha);
        break;
      default:
        puts("Opcao inexistente.");
    }
    aguardar_enter();
  }

  destruir_pilha(pilha);
  destruir_lista(lista);
  destruir_grafo(grafo);
  destruir_arvore(arvore);
  return 0;
}
