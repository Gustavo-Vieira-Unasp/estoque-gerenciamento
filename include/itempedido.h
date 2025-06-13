#ifndef ITEM_PEDIDO_H
#define ITEM_PEDIDO_H

#define MAX_CODIGO_PRODUTO 20 // Garanta que este valor seja consistente com produto.h

typedef struct {
    char codigo_produto[MAX_CODIGO_PRODUTO];
    int quantidade_solicitada;
} ItemPedido;

void inicializarItemPedido(ItemPedido *ip);
void imprimirItemPedido(const ItemPedido *ip); // Adicionei/confirmei esta função
#endif