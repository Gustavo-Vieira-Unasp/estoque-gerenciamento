#ifndef ESTOQUE_H
#define ESTOQUE_H

#include "pilhaEngradados.h"
#include "produto.h"

#define LINHAS_ESTOQUE 8
#define COLUNAS_ESTOQUE 5

typedef struct {
    Pilha pilhas[LINHAS_ESTOQUE][COLUNAS_ESTOQUE];
} Estoque;

void inicializarEstoque(Estoque *e);

int inserirEngradadoNoEstoque(Estoque *e, int linha, int coluna, Engradado engradado);

Engradado removerEngradadoDoEstoque(Estoque *e, int linha, int coluna);

void visualizarEstoque(Estoque *e);

void buscarProdutoNoEstoque(Estoque *e, const char *codigo_produto);

#endif