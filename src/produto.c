#include "produto.h"
#include "data.h"
#include "categoria.h"
#include <stdio.h>
#include <string.h>

Data lerDataDoUsuario() {
    Data d;
    printf("Digite o dia (DD): ");
    scanf("%d", &d.dia);
    printf("Digite o mês (MM): ");
    scanf("%d", &d.mes);
    printf("Digite o ano (AAAA): ");
    scanf("%d", &d.ano);
    while (getchar() != '\n');
    return d;
}

void lerStringComEspacos(char *buffer, int max_len) {
    fgets(buffer, max_len, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
}

void inicializarProduto(Produto *p) {
    if (p != NULL) {
        memset(p->codigo, 0, sizeof(p->codigo));
        memset(p->nome, 0, sizeof(p->nome));
        memset(p->lote, 0, sizeof(p->lote));
        p->precoCompra = 0.0;
        p->precoVenda = 0.0;
        p->categoria = CATEGORIA_INVALIDA;
        inicializarData(&(p->dataFabricacao), 0, 0, 0);
        inicializarData(&(p->dataValidade), 0, 0, 0);
    }
}

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

Produto cadastrarProduto() {
    Produto novoProduto;
    inicializarProduto(&novoProduto);

    printf("\n--- CADASTRO DE NOVO PRODUTO ---\n");

    printf("Código do Produto (até %d caracteres): ", MAX_CODIGO_PRODUTO - 1);
    lerStringComEspacos(novoProduto.codigo, MAX_CODIGO_PRODUTO);

    printf("Nome do Produto (até %d caracteres): ", MAX_NOME_PRODUTO - 1);
    lerStringComEspacos(novoProduto.nome, MAX_NOME_PRODUTO);

    printf("Lote do Produto (até %d caracteres): ", MAX_LOTE - 1);
    lerStringComEspacos(novoProduto.lote, MAX_LOTE);

    printf("Preço de Compra: ");
    scanf("%f", &novoProduto.precoCompra);
    while (getchar() != '\n'); // Limpa o buffer

    printf("Preço de Venda: ");
    scanf("%f", &novoProduto.precoVenda);
    while (getchar() != '\n'); // Limpa o buffer

    printf("--- Data de Fabricação ---\n");
    novoProduto.dataFabricacao = lerDataDoUsuario();

    printf("--- Data de Validade ---\n");
    novoProduto.dataValidade = lerDataDoUsuario();

    printf("Escolha a Categoria:\n");
    for (int i = 1; i < NUM_CATEGORIAS; i++) { 
        printf("%d. %s\n", i, getNomeCategoria((Categoria)i));
    }
    int cat_escolhida;
    printf("Opção: ");
    scanf("%d", &cat_escolhida);
    while (getchar() != '\n');

    if (cat_escolhida > 0 && cat_escolhida < NUM_CATEGORIAS) {
        novoProduto.categoria = (Categoria)cat_escolhida;
    } else {
        printf("Categoria inválida, definindo como 'Inválida'.\n");
        novoProduto.categoria = CATEGORIA_INVALIDA;
    }

    printf("\nProduto cadastrado com sucesso!\n");
    return novoProduto;
}