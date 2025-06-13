#include "estoque.h"
#include "filaPedidos.h"
#include "operacoes.h"

#include <stdio.h>
#include <stdlib.h>


void menuPrincipal(Estoque *estoque, Fila *filaPedidos, Pilha *pilhaEngradados) {
    int opcao;
    Produto p_temp;

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Inserir Engradado no Estoque\n");
        printf("2. Remover Engradado do Estoque\n");
        printf("3. Criar e Adicionar Pedido\n");
        printf("4. Processar Próximo Pedido\n");
        printf("5. Exibir Relatórios\n");
        printf("6. Cadastrar Novo Produto\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        while (getchar() != '\n');

        switch (opcao) {
            case 1:
                realizarInsercaoProduto(estoque);
                break;
            case 2:
                realizarRemocaoEngradado(estoque);
                break;
            case 3:
                criarEAdicionarPedido(filaPedidos);
                break;
            case 4:
                processarProximoPedido(filaPedidos, estoque);
                break;
            case 5:
                exibirRelatorios(estoque, filaPedidos);
                break;
            case 6:
                p_temp = cadastrarProduto();
                printf("Produto '%s' cadastrado. Você pode usá-lo para criar engradados agora.\n", p_temp.nome);
                imprimirProduto(p_temp);
                break;
            case 0:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);
}