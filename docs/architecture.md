# Architecture / Arquitetura

## English

### Organization
The project uses opaque abstract data types (ADTs). Public declarations are kept in `include/`, and implementations are stored in `src/`.

### Modules
- **Book:** manages book identifiers, titles, authors, and publication years.
- **Binary Search Tree (BST):** stores books indexed by ID and supports insertion, search, removal, counting, and traversal.
- **Linked List:** stores integer identifiers in a singly linked structure.
- **Queue:** manages identifiers using FIFO order.
- **Stack:** records actions using LIFO order.
- **Sorting:** orders books by title, using ID to break ties.
- **Interface:** handles user input and menu presentation.

### Memory management
Dynamically allocated structures provide destruction functions. After a successful insertion, the BST takes ownership of the book; otherwise, the caller retains responsibility for it.

---

## Português

### Organização
O projeto utiliza tipos abstratos de dados (TADs) opacos. As declarações públicas ficam em `include/` e as implementações em `src/`.

### Módulos
- **Livro:** gerencia identificadores, títulos, autores e anos de publicação.
- **Árvore Binária de Busca (BST):** armazena livros por ID e permite inserção, busca, remoção, contagem e percurso.
- **Lista Encadeada:** armazena identificadores inteiros em uma estrutura simplesmente encadeada.
- **Fila:** gerencia identificadores seguindo a ordem FIFO.
- **Pilha:** registra ações seguindo a ordem LIFO.
- **Ordenação:** organiza livros por título, com desempate por ID.
- **Interface:** realiza leitura de dados e apresenta o menu.

### Gerenciamento de memória
As estruturas alocadas dinamicamente possuem funções de destruição. Após uma inserção bem-sucedida, a BST assume a propriedade do livro; caso contrário, a responsabilidade permanece com o chamador.
