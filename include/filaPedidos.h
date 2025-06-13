#ifndef FILA_PEDIDOS_H
#define FILA_PEDIDOS_H

#include "pedido.h" // Garante que Pedido é conhecido

#define MAX_PEDIDOS_FILA 50 // Capacidade máxima da fila de pedidos

typedef struct {
    Pedido itens[MAX_PEDIDOS_FILA];
    int frente; // Índice do primeiro elemento (próximo a ser removido)
    int tras;   // Índice do último elemento (próximo a ser adicionado)
    int tamanho; // Número atual de elementos na fila
} Fila;

// Protótipos das funções da Fila de Pedidos
void inicializarFila(Fila *f);
int estaVaziaFila(const Fila *f);
int estaCheiaFila(const Fila *f);
void enqueue(Fila *f, Pedido novoPedido); // Adiciona um pedido
Pedido dequeue(Fila *f);                 // Remove um pedido
Pedido frontFila(const Fila *f);        // Retorna o primeiro pedido sem remover
void imprimirFilaPedidos(const Fila *f); // Assinatura que operacoes.c espera

#endif