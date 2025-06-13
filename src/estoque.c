#include "estoque.h"
#include "pilhaEngradados.h"
#include "engradado.h"
#include "produto.h"
#include <stdio.h>
#include <string.h>

void inicializarEstoque(Estoque *e) {
    for (int i = 0; i < LINHAS_ESTOQUE; i++) {
        for (int j = 0; j < COLUNAS_ESTOQUE; j++) {
            inicializarPilha(&(e->pilhas[i][j])); // Inicializa cada pilha individualmente
        }
    }
    printf("Estoque inicializado com sucesso (%dx%d).\n", LINHAS_ESTOQUE, COLUNAS_ESTOQUE);
}

// Verifica se a posição (linha, coluna) é válida dentro do estoque
static int posicaoValida(int linha, int coluna) {
    return (linha >= 0 && linha < LINHAS_ESTOQUE && coluna >= 0 && coluna < COLUNAS_ESTOQUE);
}

// Insere um engradado em uma posição específica do estoque
// Retorna 1 em sucesso, 0 em falha
int inserirEngradadoNoEstoque(Estoque *e, int linha, int coluna, Engradado engradado) {
    if (!posicaoValida(linha, coluna)) {
        printf("Erro: Posição (%d, %d) inválida no estoque.\n", linha, coluna);
        return 0;
    }

    // Tenta adicionar o engradado na pilha daquela posição
    if (!push(&(e->pilhas[linha][coluna]), engradado)) {
        printf("Erro: Não foi possível inserir engradado na pilha em (%d, %d). Pilha cheia?\n", linha, coluna);
        return 0; // Push falhou (pilha cheia)
    }

    printf("SUCESSO: Engradado inserido em [%d][%d].\n", linha, coluna);
    return 1; // Sucesso
}

// Remove um engradado de uma posição específica do estoque
// Retorna o Engradado removido. Se a pilha estiver vazia ou posição inválida, retorna um engradado "vazio".
Engradado removerEngradadoDoEstoque(Estoque *e, int linha, int coluna) {
    Engradado engradadoVazio;
    inicializarEngradado(&engradadoVazio); // Cria um engradado vazio para retorno de erro

    if (!posicaoValida(linha, coluna)) {
        printf("Erro: Posição (%d, %d) inválida no estoque para remoção.\n", linha, coluna);
        return engradadoVazio; // Retorna engradado vazio em caso de posição inválida
    }

    if (estaVaziaPilha(&(e->pilhas[linha][coluna]))) {
        printf("Erro: Pilha em (%d, %d) está vazia. Não há engradados para remover.\n", linha, coluna);
        return engradadoVazio; // Retorna engradado vazio se a pilha estiver vazia
    }

    Engradado removido = pop(&(e->pilhas[linha][coluna])); // Remove o engradado da pilha
    printf("SUCESSO: Engradado removido de [%d][%d].\n", linha, coluna);
    return removido;
}

// Visualiza o estado atual de todo o estoque
void visualizarEstoque(Estoque *e) {
    printf("\n--- VISUALIZAÇÃO DO ESTOQUE (%dx%d) ---\n", LINHAS_ESTOQUE, COLUNAS_ESTOQUE);
    for (int i = 0; i < LINHAS_ESTOQUE; i++) {
        for (int j = 0; j < COLUNAS_ESTOQUE; j++) {
            printf("--- Posição [%d][%d] ---\n", i, j);
            if (estaVaziaPilha(&(e->pilhas[i][j]))) {
                printf("  Pilha vazia.\n");
            } else {
                // Imprime apenas o engradado do topo da pilha e a quantidade de engradados na pilha
                Engradado topo = peek(&(e->pilhas[i][j]));
                printf("  Topo da Pilha: %s (Cód: %s) - Qtd: %d itens\n", topo.produto.nome, topo.produto.codigo, topo.quantidadeAtual);
                printf("  Total de Engradados na Pilha: %d\n", e->pilhas[i][j].topo + 1);
            }
        }
    }
    printf("------------------------------------------\n");
}

// Busca por um produto específico em todo o estoque pelo código
void buscarProdutoNoEstoque(Estoque *e, const char *codigo_produto) {
    printf("\n--- BUSCANDO PRODUTO COM CÓDIGO '%s' NO ESTOQUE ---\n", codigo_produto);
    int encontrado = 0;
    for (int i = 0; i < LINHAS_ESTOQUE; i++) {
        for (int j = 0; j < COLUNAS_ESTOQUE; j++) {
            // Itera sobre a pilha para verificar cada engradado (do topo para a base)
            Pilha *currentPilha = &(e->pilhas[i][j]);
            if (!estaVaziaPilha(currentPilha)) {
                for (int k = currentPilha->topo; k >= 0; k--) {
                    Engradado currentEngradado = currentPilha->itens[k];
                    if (strcmp(currentEngradado.produto.codigo, codigo_produto) == 0) {
                        printf("  Produto '%s' (Lote: %s) encontrado em [%d][%d], Engradado #%d da pilha.\n",
                               currentEngradado.produto.nome, currentEngradado.produto.lote, i, j, k + 1);
                        printf("    Contém %d unidades.\n", currentEngradado.quantidadeAtual);
                        encontrado = 1;
                    }
                }
            }
        }
    }
    if (!encontrado) {
        printf("  Produto com código '%s' não encontrado em nenhuma posição do estoque.\n", codigo_produto);
    }
}