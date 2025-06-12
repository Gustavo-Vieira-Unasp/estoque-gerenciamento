#ifndef OPERACOES_H
#define OPERACOES_H

#include "estoque.h"
#include "filaPedidos.h"
#include "data.h"

void realizarInsercaoProduto(Estoque *estoque);

void realizarRemocaoEngradado(Estoque *estoque);

void criarEAdicionarPedido(Fila *filaPedidos);

void processarProximoPedido(Fila *filaPedidos, Estoque *estoque);

void exibirRelatorios(Estoque *estoque, Fila *filaPedidos);

Data lerDataDoUsuario();
void lerStringComEspacos(char *buffer, int max_len);
Produto criarProdutoTeste(const char* codigo, const char* nome, const char* lote, float precoC, float precoV, Categoria cat, Data fab, Data val);
Engradado criarEngradadoTeste(Produto p, int qtd);


#endif