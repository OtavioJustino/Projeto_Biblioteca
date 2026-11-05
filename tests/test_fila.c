#include <assert.h>
#include <stdio.h>
#include "../include/fila.h"

int main(void) {
    FILA *fila = criar_fila();
    assert(fila != NULL);
    int id = -1;
    assert(desenfileirar(fila, &id) == 0);
    assert(consultar_inicio(fila, &id) == 0);
    assert(enfileirar(fila, 10) == 1);
    assert(enfileirar(fila, 20) == 1);
    assert(enfileirar(fila, 30) == 1);
    assert(consultar_inicio(fila, &id) == 1 && id == 10);
    assert(desenfileirar(fila, &id) == 1 && id == 10);
    assert(consultar_inicio(fila, &id) == 1 && id == 20);
    assert(desenfileirar(fila, &id) == 1 && id == 20);
    assert(desenfileirar(fila, &id) == 1 && id == 30);
    assert(desenfileirar(fila, &id) == 0);
    assert(enfileirar(fila, 40) == 1);
    assert(desenfileirar(fila, &id) == 1 && id == 40);
    assert(enfileirar(NULL, 1) == 0);
    assert(desenfileirar(NULL, &id) == 0);
    assert(desenfileirar(fila, NULL) == 0);
    assert(consultar_inicio(fila, NULL) == 0);
    destruir_fila(fila);
    destruir_fila(NULL);
    puts("OK: fila FIFO");
    return 0;
}
