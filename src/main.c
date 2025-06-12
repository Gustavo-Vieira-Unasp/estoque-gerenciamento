#include "estoque.h"
#include "filaPedidos.h"
#include "operacoes.h"

#include <stdio.h>
#include <stdlib.h>

void exibirMenu() {
    printf("\n--- SISTEMA DE GERENCIAMENTO DE ESTOQUE ---\n");
    printf("1. Inserir Engradado no Estoque\n");
    printf("2. Remover Engradado do Estoque\n");
    printf("3. Criar e Adicionar Novo Pedido\n");
    printf("4. Processar Próximo Pedido\n");
    printf("5. Visualizar Estoque Completo\n");
    printf("6. Buscar Produto no Estoque\n");
    printf("7. Exibir Relatórios\n");
    printf("0. Sair\n");
    printf("-------------------------------------------\n");
    printf("Escolha uma opção: ");
}

int main() {
    Estoque meuEstoque;
    Fila filaDePedidos;

    inicializarEstoque(&meuEstoque);
    inicializarFila(&filaDePedidos);

    int opcao;
    do {
        exibirMenu();
        scanf("%d", &opcao);
        while (getchar() != '\n');

        switch (opcao) {
            case 1:
                realizarInsercaoProduto(&meuEstoque);
                break;
            case 2:
                realizarRemocaoEngradado(&meuEstoque);
                break;
            case 3:
                criarEAdicionarPedido(&filaDePedidos);
                break;
            case 4:
                processarProximoPedido(&filaDePedidos, &meuEstoque);
                break;
            case 5:
                visualizarEstoque(&meuEstoque);
                break;
            case 6: {
                char codigo_busca[MAX_CODIGO_PRODUTO];
                printf("Digite o código do produto para buscar: ");
                lerStringComEspacos(codigo_busca, MAX_CODIGO_PRODUTO);
                buscarProdutoNoEstoque(&meuEstoque, codigo_busca);
                break;
            }
            case 7:
                exibirRelatorios(&meuEstoque, &filaDePedidos);
                break;
            case 0:
                printf("Saindo do sistema. Até mais!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
        printf("\nPressione ENTER para continuar...");
        while (getchar() != '\n');
    } while (opcao != 0);

    return 0;
}