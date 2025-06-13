#ifndef PEDIDO_H
#define PEDIDO_H

#include "data.h"
#include "itempedido.h" // Se o nome do seu arquivo é itempedido.h

#define MAX_ITENS_DIFERENTES_POR_PEDIDO 10
#define MAX_NOME_SOLICITANTE 100

typedef struct {
    int id_pedido;
    ItemPedido itens[MAX_ITENS_DIFERENTES_POR_PEDIDO];
    int num_itens_diferentes;
    Data dataSolicitacao;
    char nomeSolicitante[MAX_NOME_SOLICITANTE];
} Pedido;

void inicializarPedido(Pedido *p, int id_novo_pedido);
int adicionarItemAoPedido(Pedido *p, const char *codigo_produto, int quantidade);
void imprimirPedido(const Pedido *p); // Alterado para imprimirPedido e passou a receber ponteiro

#endif