#include "itempedido.h"
#include <stdio.h>
#include <string.h>

void inicializarItemPedido(ItemPedido *ip) {
    if (ip != NULL) {
        memset(ip->codigo_produto, 0, sizeof(ip->codigo_produto));
        ip->quantidade_solicitada = 0;
    }
}

void imprimirItemPedido(const ItemPedido *ip) {
    if (ip != NULL) {
        printf("Produto (Cód): %s, Quantidade: %d\n", ip->codigo_produto, ip->quantidade_solicitada);
    }
}