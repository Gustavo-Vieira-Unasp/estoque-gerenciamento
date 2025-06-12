#include "filaPedidos.h"
#include "pedido.h" // Para Pedido e imprimirPedido
#include <stdio.h>
#include <stdlib.h> // Para EXIT_FAILURE

// Inicializa a fila
void inicializarFila(Fila *f) {
    if (f != NULL) {
        f->frente = 0;
        f->tras = -1;
        f->tamanho = 0;
    }
}

// Verifica se a fila está vazia
int estaVaziaFila(const Fila *f) {
    return (f == NULL || f->tamanho == 0);
}

// Verifica se a fila está cheia
int estaCheiaFila(const Fila *f) {
    return (f != NULL && f->tamanho == MAX_PEDIDOS_FILA);
}

// Adiciona um elemento à fila
void enqueue(Fila *f, Pedido novoPedido) {
    if (f == NULL || estaCheiaFila(f)) {
        printf("Erro: Fila de pedidos cheia ou não inicializada. Não é possível adicionar.\n");
        return;
    }
    f->tras = (f->tras + 1) % MAX_PEDIDOS_FILA; // Circular
    f->itens[f->tras] = novoPedido;
    f->tamanho++;
}

// Remove e retorna um elemento da fila
Pedido dequeue(Fila *f) {
    if (f == NULL || estaVaziaFila(f)) {
        printf("Erro: Fila de pedidos vazia ou não inicializada. Não é possível remover.\n");
        // Retorna um pedido vazio/inválido
        Pedido pedidoVazio;
        inicializarPedido(&pedidoVazio, 0); // Exemplo de inicialização de pedido vazio
        return pedidoVazio;
    }
    Pedido pedido = f->itens[f->frente];
    f->frente = (f->frente + 1) % MAX_PEDIDOS_FILA; // Circular
    f->tamanho--;
    return pedido;
}

// Retorna o elemento da frente sem remover
Pedido frontFila(const Fila *f) {
    if (f == NULL || estaVaziaFila(f)) {
        printf("Erro: Fila de pedidos vazia ou não inicializada. Nenhum pedido na frente.\n");
        Pedido pedidoVazio;
        inicializarPedido(&pedidoVazio, 0);
        return pedidoVazio;
    }
    return f->itens[f->frente];
}

// Imprime todos os pedidos na fila
void imprimirFilaPedidos(const Fila *f) {
    if (f == NULL || estaVaziaFila(f)) {
        printf("Fila de pedidos vazia.\n");
        return;
    }
    printf("\n--- Conteúdo da Fila de Pedidos (%d pedidos) ---\n", f->tamanho);
    int current_idx = f->frente;
    for (int i = 0; i < f->tamanho; i++) {
        printf("  Pedido %d:\n", i + 1);
        imprimirPedido(&(f->itens[current_idx])); // Passar por ponteiro para evitar cópia desnecessária ou erros
        current_idx = (current_idx + 1) % MAX_PEDIDOS_FILA;
    }
    printf("--------------------------------------------------\n");
}