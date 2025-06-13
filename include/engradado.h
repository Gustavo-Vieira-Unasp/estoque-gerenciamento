#ifndef ENGRADADO_H
#define ENGRADADO_H

#include "produto.h" // Garante que Produto é conhecido

// Defina as constantes para o engradado (ajuste conforme seu design)
#define MAX_UNIDADES_POR_ENGRADADO 100 // Exemplo

typedef struct {
    Produto produto;         // O produto contido neste engradado
    int quantidadeAtual;     // Quantidade de unidades deste produto no engradado
} Engradado;

// Protótipos das funções do Engradado
void inicializarEngradado(Engradado *e);
int adicionarItensEngradado(Engradado *e, Produto p, int quantidade); // Assinatura que operacoes.c espera
int removerItensEngradado(Engradado *e, int quantidade);             // Assinatura que operacoes.c espera
int engradadoEstaVazio(const Engradado *e);
void imprimirEngradado(const Engradado *e); // Melhor passar por ponteiro para evitar cópia grande
// Adicione outras funções do engradado aqui se tiver
#endif