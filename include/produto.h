#ifndef PRODUTO_H
#define PRODUTO_H

#include "data.h"
#include "categoria.h"

#define MAX_CODIGO_PRODUTO 99
#define MAX_LOTE 99
#define MAX_NOME_PRODUTO 99

typedef struct {
    char codigo[MAX_CODIGO_PRODUTO];
    char lote[MAX_LOTE];
    char nome[MAX_NOME_PRODUTO];
    Data dataFabricacao;
    Data dataValidade;
    float precoCompra;
    float precoVenda;
    Categoria categoria;
} Produto;

void inicializarProduto(Produto *p);
void imprimirProduto(const Produto produto);
Produto cadastrarProduto();

#endif