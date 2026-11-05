# Automated Tests / Testes Automatizados

## English

### Execution
Run the following command from the repository root:

```sh
make test
```

To clean generated binaries:

```sh
make clean
```

The tests use C `assert` statements and compile with GCC. The sorting test captures standard output using POSIX functions, so Linux/WSL is recommended.

### Test suites
| Test | Modules |
| --- | --- |
| `test_estruturas` | Book, BST, linked list, stack |
| `test_fila` | Queue |
| `test_ordenacao` | Sorting by title and ID |

### Test scenarios
Tests exercise creation, insertion, lookup, removal, ordering, empty structures, and invalid arguments, depending on the module.

---

## Português

### Execução
Execute o comando abaixo na raiz do repositório:

```sh
make test
```

Para limpar os binários gerados:

```sh
make clean
```

Os testes utilizam `assert` em C e são compilados com GCC. O teste de ordenação captura a saída padrão utilizando funções POSIX; por isso, recomenda-se Linux/WSL.

### Conjuntos de testes
| Teste | Módulos |
| --- | --- |
| `test_estruturas` | Livro, BST, lista encadeada, pilha |
| `test_fila` | Fila |
| `test_ordenacao` | Ordenação por título e ID |

### Cenários de teste
Os testes verificam criação, inserção, busca, remoção, ordenação, estruturas vazias e argumentos inválidos, conforme o módulo.
