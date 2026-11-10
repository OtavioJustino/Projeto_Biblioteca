# Library Management — Data Structures

## English

Academic C project for the Data Structures course at FATEC. The terminal application manages books and their connections using opaque abstract data types.

### Features
- Register, find, remove, and list books by ID using a binary search tree (BST).
- Display books sorted by title, breaking ties by ID.
- Add and remove undirected connections between books.
- Check direct connections, list reachable IDs, and check paths using breadth-first search (BFS).
- Display the five most recent changes using a stack.

### Structure
- `include/` — public ADT interfaces.
- `src/` — implementations and interactive menu.
- `tests/` — automated C tests.
- `docs/` — architecture and test documentation.

### Requirements and commands
GCC with C11 support, GNU Make, and a Linux/WSL environment for the supplied Makefile and tests.

```sh
make          # Build the application
make run      # Run the interactive menu
make test     # Run automated tests
make clean    # Remove generated binaries
```

The application uses `clear` on Linux and `cls` on Windows to clear the terminal. The supplied Makefile uses Unix shell commands.

### Documentation
- [Architecture / Arquitetura](docs/architecture.md)
- [Automated Tests / Testes Automatizados](docs/tests.md)

---

## Português

Projeto acadêmico em C para a disciplina de Estrutura de Dados da FATEC. O programa de terminal gerencia livros e suas conexões utilizando tipos abstratos de dados (TADs) opacos.

### Funcionalidades
- Cadastrar, buscar, remover e listar livros por ID utilizando uma árvore binária de busca (BST).
- Exibir livros ordenados por título, com desempate por ID.
- Adicionar e remover conexões não direcionadas entre livros.
- Consultar conexões diretas, listar IDs alcançáveis e verificar caminhos usando busca em largura (BFS).
- Consultar as cinco modificações mais recentes por meio de uma pilha.

### Estrutura
- `include/` — interfaces públicas dos TADs.
- `src/` — implementações e menu interativo.
- `tests/` — testes automatizados em C.
- `docs/` — documentação de arquitetura e testes.

### Requisitos e comandos
GCC com suporte a C11, GNU Make e ambiente Linux/WSL para o Makefile e os testes fornecidos.

```sh
make          # Compilar o programa
make run      # Executar o menu interativo
make test     # Executar os testes automatizados
make clean    # Remover os binários gerados
```

O programa usa `clear` no Linux e `cls` no Windows para limpar o terminal. O Makefile fornecido utiliza comandos de shell Unix.

### Documentação
- [Arquitetura / Architecture](docs/architecture.md)
- [Testes Automatizados / Automated Tests](docs/tests.md)
