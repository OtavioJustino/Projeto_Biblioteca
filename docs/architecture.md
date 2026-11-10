# Architecture / Arquitetura

## English

### Organization and ownership
The project implements opaque abstract data types (ADTs): public declarations are in `include/`, and implementations are in `src/`. The BST owns each book after successful insertion; if insertion fails, the caller must destroy the book. The main program creates and destroys the data structures.

### Modules
| Module | Responsibility |
| --- | --- |
| Book (`livro`) | Validate and store ID, title, author, and publication year |
| BST (`arvore`) | Insert, search, remove, count, and traverse books by ID |
| Linked list (`lista`) | Keep a linked sequence of registered book IDs |
| Stack (`pilha`) | Record changes and display the five latest actions (LIFO) |
| Queue (`fila`) | Provide FIFO operations for breadth-first search |
| Graph (`grafo`) | Represent books as vertices and undirected connections as adjacency lists |
| Sorting (`ordenacao`) | Display books ordered by title, breaking ties by ID |
| Interface (`interface`) | Read validated input and present the menu |
| Main (`main`) | Coordinate registration, removal, queries, history, and cleanup |

### Application flow
On registration, the program validates the input, checks for an existing ID, adds the ID to the list and graph, and inserts the book into the BST. If an intermediate step fails, earlier insertions are rolled back. On removal, it removes the book from the BST, the corresponding graph vertex (including its edges), and the ID from the list. Successful changes are recorded in the stack when memory allocation permits.

The graph uses adjacency lists and treats connections as undirected. Reachability and path checks use BFS with the queue. The reachable-ID listing excludes the origin. Sorting copies book data into a temporary array and does not modify the BST.

### Memory management
Each dynamically allocated structure has a destruction function. Graph traversal allocates temporary arrays and a queue, then releases them. The main program releases the stack, list, graph, and BST on exit.

---

## Português

### Organização e propriedade dos dados
O projeto utiliza tipos abstratos de dados (TADs) opacos: as declarações públicas ficam em `include/` e as implementações em `src/`. A BST assume a propriedade do livro após uma inserção bem-sucedida; se a inserção falhar, o chamador deve destruir o livro. O programa principal cria e destrói as estruturas.

### Módulos
| Módulo | Responsabilidade |
| --- | --- |
| Livro (`livro`) | Validar e armazenar ID, título, autor e ano de publicação |
| BST (`arvore`) | Inserir, buscar, remover, contar e percorrer livros por ID |
| Lista (`lista`) | Manter uma sequência encadeada dos IDs cadastrados |
| Pilha (`pilha`) | Registrar alterações e mostrar as cinco ações mais recentes (LIFO) |
| Fila (`fila`) | Oferecer operações FIFO para a busca em largura |
| Grafo (`grafo`) | Representar livros como vértices e conexões não direcionadas como listas de adjacência |
| Ordenação (`ordenacao`) | Exibir livros por título, com desempate por ID |
| Interface (`interface`) | Ler dados validados e apresentar o menu |
| Principal (`main`) | Coordenar cadastro, remoção, consultas, histórico e liberação de memória |

### Fluxo do programa
No cadastro, o programa valida os dados, verifica se o ID já existe, adiciona o ID à lista e ao grafo e insere o livro na BST. Se uma etapa intermediária falhar, as inserções anteriores são desfeitas. Na remoção, exclui o livro da BST, o vértice correspondente do grafo (inclusive suas arestas) e o ID da lista. As alterações bem-sucedidas são registradas na pilha quando a alocação de memória permite.

O grafo usa listas de adjacência e conexões não direcionadas. A listagem de alcançáveis e a verificação de caminhos utilizam BFS com a fila. A listagem exclui o vértice de origem. A ordenação copia os dados dos livros para um vetor temporário, sem modificar a BST.

### Gerenciamento de memória
Cada estrutura alocada dinamicamente possui função de destruição. A busca no grafo aloca vetores temporários e uma fila, liberados ao final. O programa principal libera pilha, lista, grafo e BST ao encerrar.
