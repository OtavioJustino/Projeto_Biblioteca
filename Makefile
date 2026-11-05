CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -g
CPPFLAGS ?= -Iinclude
BUILD_DIR := build
TEST_BIN := $(BUILD_DIR)/test_estruturas
FILA_BIN := $(BUILD_DIR)/test_fila
ORDENACAO_BIN := $(BUILD_DIR)/test_ordenacao
TEST_SOURCES := tests/test_estruturas.c src/livro.c src/arvore.c src/lista.c src/pilha.c

.PHONY: all test clean check
all: test

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TEST_BIN): $(TEST_SOURCES) | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(TEST_SOURCES) -o $@

$(FILA_BIN): tests/test_fila.c src/fila.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@

$(ORDENACAO_BIN): tests/test_ordenacao.c src/ordenacao.c src/arvore.c src/livro.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@

test: $(TEST_BIN) $(FILA_BIN) $(ORDENACAO_BIN)
	./$(TEST_BIN)
	./$(FILA_BIN)
	./$(ORDENACAO_BIN)

check: test

clean:
	rm -rf $(BUILD_DIR)
