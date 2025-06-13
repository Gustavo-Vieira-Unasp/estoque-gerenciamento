#include "engradado.h"
#include "produto.h" // Para tipos de Produto, e a função inicializarProduto e imprimirProduto
#include <stdio.h>
#include <string.h>

// Inicializa um engradado, marcando-o como vazio
void inicializarEngradado(Engradado *e) {
    if (e != NULL) {
        inicializarProduto(&(e->produto)); // Inicializa o produto dentro do engradado
        e->quantidadeAtual = 0;
    }
}

// Adiciona itens a um engradado existente
// Retorna 1 em caso de sucesso, 0 em caso de falha
int adicionarItensEngradado(Engradado *e, Produto p, int quantidade) {
    if (e == NULL || quantidade <= 0) {
        return 0; // Ponteiro nulo ou quantidade inválida
    }

    if (e->quantidadeAtual == 0) {
        // Se o engradado está vazio, adiciona o novo produto
        e->produto = p;
        e->quantidadeAtual = quantidade;
        return 1;
    } else if (strcmp(e->produto.codigo, p.codigo) == 0 &&
               strcmp(e->produto.lote, p.lote) == 0 &&
               strcmp(e->produto.nome, p.nome) == 0) {
        // Se o engradado já contém o mesmo produto, apenas adiciona a quantidade
        e->quantidadeAtual += quantidade;
        return 1;
    }
    // Se o engradado já tem um produto diferente, não permite adicionar
    return 0;
}

// Remove itens de um engradado existente
// Retorna 1 em caso de sucesso, 0 em caso de falha
int removerItensEngradado(Engradado *e, int quantidade) {
    if (e == NULL || quantidade <= 0) {
        return 0; // Ponteiro nulo ou quantidade inválida
    }
    if (e->quantidadeAtual < quantidade) {
        return 0; // Tentando remover mais do que o disponível
    }
    e->quantidadeAtual -= quantidade;
    // Se a quantidade chegar a zero, o engradado fica "vazio"
    if (e->quantidadeAtual == 0) {
        inicializarProduto(&(e->produto)); // Limpa o produto
    }
    return 1;
}

// Verifica se o engradado está vazio
int engradadoEstaVazio(const Engradado *e) {
    return (e == NULL || e->quantidadeAtual == 0 || strlen(e->produto.codigo) == 0);
}

// Imprime informações do engradado
void imprimirEngradado(const Engradado *e) {
    if (e != NULL && e->quantidadeAtual > 0) {
        printf("Engradado: Produto: ");
        imprimirProduto(&(e->produto)); // Chama a função de impressão do produto
        printf(", Qtd no Engradado: %d\n", e->quantidadeAtual);
    } else {
        printf("Engradado: Vazio\n");
    }
}