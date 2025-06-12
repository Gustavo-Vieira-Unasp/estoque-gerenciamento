#include "pedido.h"
#include "itempedido.h" // Para ItemPedido e imprimirItemPedido
#include "data.h"       // Para Data e imprimirData
#include <stdio.h>
#include <string.h>

// Inicializa um novo pedido
void inicializarPedido(Pedido *p, int id_novo_pedido) {
    if (p != NULL) {
        p->id_pedido = id_novo_pedido;
        p->num_itens_diferentes = 0;
        memset(p->nomeSolicitante, 0, sizeof(p->nomeSolicitante)); // Limpa o nome
        // Data de solicitação pode ser preenchida posteriormente
        p->dataSolicitacao.dia = 0;
        p->dataSolicitacao.mes = 0;
        p->dataSolicitacao.ano = 0;

        // Opcional: inicializar itens do pedido
        for (int i = 0; i < MAX_ITENS_DIFERENTES_POR_PEDIDO; i++) {
            inicializarItemPedido(&(p->itens[i]));
        }
    }
}

// Adiciona um item (tipo de produto e quantidade) ao pedido
// Retorna 1 em caso de sucesso, 0 em caso de falha (ex: pedido cheio, item já existe)
int adicionarItemAoPedido(Pedido *p, const char *codigo_produto, int quantidade) {
    if (p == NULL || codigo_produto == NULL || quantidade <= 0) {
        return 0; // Dados inválidos
    }

    if (p->num_itens_diferentes >= MAX_ITENS_DIFERENTES_POR_PEDIDO) {
        printf("Limite de itens diferentes por pedido atingido.\n");
        return 0;
    }

    // Verifica se o item (pelo código do produto) já está no pedido
    for (int i = 0; i < p->num_itens_diferentes; i++) {
        if (strcmp(p->itens[i].codigo_produto, codigo_produto) == 0) {
            // Se o item já existe, apenas atualiza a quantidade
            p->itens[i].quantidade_solicitada += quantidade; // Use 'quantidade' aqui, não 'quantity'
            return 1;
        }
    }

    // Se o item não existe, adiciona um novo
    inicializarItemPedido(&(p->itens[p->num_itens_diferentes]));
    strncpy(p->itens[p->num_itens_diferentes].codigo_produto, codigo_produto, MAX_CODIGO_PRODUTO - 1);
    p->itens[p->num_itens_diferentes].codigo_produto[MAX_CODIGO_PRODUTO - 1] = '\0';
    p->itens[p->num_itens_diferentes].quantidade_solicitada = quantidade;
    p->num_itens_diferentes++;
    return 1;
}

// Exibe os detalhes de um pedido
void imprimirPedido(const Pedido *p) { // Mudado para receber ponteiro
    if (p == NULL) {
        printf("Pedido inválido.\n");
        return;
    }
    printf("ID do Pedido: %d\n", p->id_pedido);
    printf("Solicitante: %s\n", p->nomeSolicitante);
    printf("Data da Solicitação: ");
    imprimirData(p->dataSolicitacao); // <<< CORRIGIDO: Passa Data por valor
    printf("\nItens do Pedido (%d tipos diferentes):\n", p->num_itens_diferentes);
    if (p->num_itens_diferentes == 0) {
        printf("  Nenhum item neste pedido.\n");
    } else {
        for (int i = 0; i < p->num_itens_diferentes; i++) {
            printf("  - ");
            imprimirItemPedido(&(p->itens[i])); // Se imprimirItemPedido espera ponteiro, mantenha assim
        }
    }
}