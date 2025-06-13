#include "produto.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Para system("cls") ou system("clear") se for usar

// --- Funções Auxiliares (idealmente estariam em utilidades.h/utilidades.c) ---
// Copiadas de operacoes.c para que cadastrarProduto funcione aqui
Data lerDataDoUsuario() {
    Data d;
    printf("Digite o dia (DD): ");
    scanf("%d", &d.dia);
    printf("Digite o mês (MM): ");
    scanf("%d", &d.mes);
    printf("Digite o ano (AAAA): ");
    scanf("%d", &d.ano);
    while (getchar() != '\n'); // Limpa o buffer
    return d;
}

void lerStringComEspacos(char *buffer, int max_len) {
    fgets(buffer, max_len, stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Remove o newline
}
// --- Fim das Funções Auxiliares ---


// Inicializa um produto com valores padrão
void inicializarProduto(Produto *p) {
    if (p != NULL) {
        memset(p->codigo, 0, sizeof(p->codigo));
        memset(p->nome, 0, sizeof(p->nome));
        memset(p->lote, 0, sizeof(p->lote));
        p->precoCompra = 0.0;
        p->precoVenda = 0.0;
        p->categoria = CATEGORIA_INVALIDA; // Assumindo que CATEGORIA_INVALIDA existe
        inicializarData(&(p->dataFabricacao), 0, 0, 0);
        inicializarData(&(p->dataValidade), 0, 0, 0);
    }
}

// Imprime os detalhes de um produto
void imprimirProduto(const Produto *p) {
    if (p != NULL) {
        printf("Código: %s\n", p->codigo);
        printf("Nome: %s\n", p->nome);
        printf("Lote: %s\n", p->lote);
        printf("Preço de Compra: %.2f\n", p->precoCompra);
        printf("Preço de Venda: %.2f\n", p->precoVenda);
        printf("Categoria: %s\n", getNomeCategoria(p->categoria)); // Assumindo getNomeCategoria existe
        printf("Data de Fabricação: ");
        imprimirData(p->dataFabricacao); // Passando por valor
        printf("\nData de Validade: ");
        imprimirData(p->dataValidade); // Passando por valor
        printf("\n");
    } else {
        printf("Produto inválido.\n");
    }
}


// Cadastra um produto interativamente com o usuário
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
    for (int i = 1; i < NUM_CATEGORIAS; i++) { // Começa de 1 para pular CATEGORIA_INVALIDA
        printf("%d. %s\n", i, getNomeCategoria((Categoria)i));
    }
    int cat_escolhida;
    printf("Opção: ");
    scanf("%d", &cat_escolhida);
    while (getchar() != '\n'); // Limpa o buffer

    if (cat_escolhida > 0 && cat_escolhida < NUM_CATEGORIAS) {
        novoProduto.categoria = (Categoria)cat_escolhida;
    } else {
        printf("Categoria inválida, definindo como 'Inválida'.\n");
        novoProduto.categoria = CATEGORIA_INVALIDA;
    }

    printf("\nProduto cadastrado com sucesso!\n");
    return novoProduto;
}