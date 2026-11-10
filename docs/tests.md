# Automated Tests / Testes Automatizados

## English

### Running the tests
From the repository root, with GCC, GNU Make, and Linux/WSL:

```sh
make test
make clean
```

The suites use C `assert` statements. The sorting test captures standard output using POSIX functions (`dup`, `dup2`, and `fileno`); the supplied test Makefile targets a Unix-like environment.

### Test suites
| Executable | Coverage |
| --- | --- |
| `test_estruturas` | Book validation, BST insertion/search/removal/traversal, linked list, stack |
| `test_fila` | FIFO ordering, empty queue, null arguments |
| `test_ordenacao` | Title ordering, ID tie-breaker, formatted output, unchanged BST |
| `test_grafo` | Vertex/edge insertion and removal, duplicate and invalid IDs, undirected edges, BFS reachability and paths |

### Scope
The graph suite checks the return values of reachable-ID listing, but does not compare the printed list of IDs. These are automated module tests; they do not simulate interactive input through the complete menu. Allocation-failure scenarios are not injected.

---

## Português

### Executando os testes
Na raiz do repositório, com GCC, GNU Make e Linux/WSL:

```sh
make test
make clean
```

Os testes utilizam `assert` em C. O teste de ordenação captura a saída padrão usando funções POSIX (`dup`, `dup2` e `fileno`); o Makefile de testes fornecido é destinado a ambientes semelhantes ao Unix.

### Conjuntos de testes
| Executável | Cobertura |
| --- | --- |
| `test_estruturas` | Validação de livros, inserção/busca/remoção/percurso da BST, lista e pilha |
| `test_fila` | Ordem FIFO, fila vazia e argumentos nulos |
| `test_ordenacao` | Ordenação por título, desempate por ID, formato de saída e preservação da BST |
| `test_grafo` | Inserção e remoção de vértices e arestas, IDs duplicados e inválidos, conexões não direcionadas, alcançabilidade e caminhos com BFS |

### Escopo
O teste do grafo verifica os valores de retorno da listagem de alcançáveis, mas não compara os IDs impressos. São testes automatizados dos módulos; não simulam a entrada interativa pelo menu completo. Não são simuladas falhas de alocação de memória.
