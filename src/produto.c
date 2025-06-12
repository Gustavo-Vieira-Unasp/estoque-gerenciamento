#include "produto.h"
#include "data.h"
#include "categoria.h"
#include <stdio.h>
#include <string.h>

void imprimirProduto(Produto produto){
    printf("Detalhes do Produto");
    printf("Código: %s\n", produto.codigo);
    printf("Lote: %s\n", produto.lote);
    printf("Nome: %s\n", produto.nome);
    printf("Fabricação: ");
    imprimirData(produto.dataFabricacao);
    printf("\n");
    printf("Validade: ");
    imprimirData(produto.dataValidade);
    printf("\n");
    printf("Preço Compra: R$ %.2f\n");
    printf("Preço Venda: R$ %.2f\n");
    printf("Categoria: %s\n", getNomeCategoria(produto.categoria));
}