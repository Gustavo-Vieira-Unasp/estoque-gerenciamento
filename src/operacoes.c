#include "operacoes.h"
#include "estoque.h"
#include "filaPedidos.h"
#include "produto.h"
#include "engradado.h"
#include "pedido.h"
#include "itempedido.h"
#include "data.h"
#include "categoria.h"

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// Variável global simples para IDs de pedidos (pode ser salva/carregada em um DB real)
static int proximo_id_pedido_global = 1;

// --- Funções Auxiliares para Entrada de Dados ---
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

// Função de Teste: Cria um produto com dados predefinidos para facilitar testes
Produto criarProdutoTeste(const char* codigo, const char* nome, const char* lote, float precoC, float precoV, Categoria cat, Data fab, Data val) {
    Produto p;
    strcpy(p.codigo, codigo);
    strcpy(p.nome, nome);
    strcpy(p.lote, lote);
    p.precoCompra = precoC;
    p.precoVenda = precoV;
    p.categoria = cat;
    p.dataFabricacao = fab;
    p.dataValidade = val;
    return p;
}

// Função de Teste: Cria um engradado com um produto e quantidade
Engradado criarEngradadoTeste(Produto p, int qtd) {
    Engradado e;
    inicializarEngradado(&e);
    adicionarItensEngradado(&e, p, qtd); // Usa a função do Engradado para adicionar
    return e;
}


// 1. Inserir Produtos no Estoque
void realizarInsercaoProduto(Estoque *estoque) {
    printf("\n--- INSERIR ENGRADADO NO ESTOQUE ---\n");
    int linha, coluna;
    printf("Digite a linha (0 a %d): ", LINHAS_ESTOQUE - 1);
    scanf("%d", &linha);
    printf("Digite a coluna (0 a %d): ", COLUNAS_ESTOQUE - 1);
    scanf("%d", &coluna);
    while (getchar() != '\n'); // Limpa o buffer

    if (estaCheiaPilha(&(estoque->pilhas[linha][coluna]))) {
        printf("Erro: A pilha na posição [%d][%d] está cheia. Não é possível inserir mais engradados.\n", linha, coluna);
        return;
    }

    // Perguntar ao usuário os detalhes do produto para o novo engradado
    Produto novoProduto;
    printf("\n--- Dados do PRODUTO para o Engradado ---\n");
    printf("Código do Produto: "); lerStringComEspacos(novoProduto.codigo, MAX_CODIGO_PRODUTO);
    printf("Lote do Produto: "); lerStringComEspacos(novoProduto.lote, MAX_LOTE);
    printf("Nome do Produto: "); lerStringComEspacos(novoProduto.nome, MAX_NOME_PRODUTO);
    printf("Preço de Compra: "); scanf("%f", &novoProduto.precoCompra);
    printf("Preço de Venda: "); scanf("%f", &novoProduto.precoVenda);
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

    int quantidade_unidades;
    printf("Quantidade de UNIDADES deste produto no engradado (máx %d): ", MAX_UNIDADES_POR_ENGRADADO);
    scanf("%d", &quantidade_unidades);
    while (getchar() != '\n'); // Limpa o buffer

    // Criar o engradado e tentar adicionar o produto
    Engradado novoEngradado;
    inicializarEngradado(&novoEngradado);
    if (!adicionarItensEngradado(&novoEngradado, novoProduto, quantidade_unidades)) {
        printf("Falha ao criar o engradado. Verifique a quantidade ou se o produto já existe no engradado (mesmo que vazio, se o código for diferente).\n");
        return;
    }

    // Inserir o engradado na pilha do estoque
    inserirEngradadoNoEstoque(estoque, linha, coluna, novoEngradado);
}

// 2. Remover Produtos do Estoque
void realizarRemocaoEngradado(Estoque *estoque) {
    printf("\n--- REMOVER ENGRADADO DO ESTOQUE ---\n");
    int linha, coluna;
    printf("Digite a linha (0 a %d): ", LINHAS_ESTOQUE - 1);
    scanf("%d", &linha);
    printf("Digite a coluna (0 a %d): ", COLUNAS_ESTOQUE - 1);
    scanf("%d", &coluna);
    while (getchar() != '\n'); // Limpa o buffer

    // A função removerEngradadoDoEstoque já trata erros de posição/pilha vazia
    Engradado engradadoRemovido = removerEngradadoDoEstoque(estoque, linha, coluna);

    // Se o engradado removido não for "vazio" (ID 0 ou quantidade 0 e código vazio)
    if (!engradadoEstaVazio(&engradadoRemovido)) {
        printf("Engradado com produto '%s' (Qtd: %d) removido com sucesso.\n",
               engradadoRemovido.produto.nome, engradadoRemovido.quantidadeAtual);
    }
}

// 3. Criar e Adicionar Pedido à Fila
void criarEAdicionarPedido(Fila *filaPedidos) {
    printf("\n--- CRIAR NOVO PEDIDO ---\n");
    if (estaCheiaFila(filaPedidos)) {
        printf("Erro: Fila de pedidos cheia. Não é possível adicionar novos pedidos.\n");
        return;
    }

    Pedido novoPedido;
    inicializarPedido(&novoPedido, proximo_id_pedido_global++); // Atribui um ID único

    printf("Nome do Solicitante: ");
    lerStringComEspacos(novoPedido.nomeSolicitante, MAX_NOME_SOLICITANTE);

    // Pegar a data atual do sistema para a solicitação (simplificado)
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    novoPedido.dataSolicitacao.dia = tm_info->tm_mday;
    novoPedido.dataSolicitacao.mes = tm_info->tm_mon + 1;
    novoPedido.dataSolicitacao.ano = tm_info->tm_year + 1900;

    int mais_itens = 1;
    char codigo_temp[MAX_CODIGO_PRODUTO];
    int quantidade_temp;

    while (mais_itens) {
        printf("\nAdicionar item ao Pedido (ID: %d):\n", novoPedido.id_pedido);
        printf("Código do Produto: ");
        lerStringComEspacos(codigo_temp, MAX_CODIGO_PRODUTO);
        printf("Quantidade Solicitada: ");
        scanf("%d", &quantidade_temp);
        while (getchar() != '\n');

        if (!adicionarItemAoPedido(&novoPedido, codigo_temp, quantidade_temp)) {
            printf("Falha ao adicionar item ao pedido. Verifique os dados ou o limite de itens.\n");
        }

        printf("Adicionar outro item a este pedido? (1 para Sim, 0 para Não): ");
        scanf("%d", &mais_itens);
        while (getchar() != '\n');
    }

    enqueue(filaPedidos, novoPedido); // Adiciona o pedido à fila
}

// 4. Processar Próximo Pedido da Fila
void processarProximoPedido(Fila *filaPedidos, Estoque *estoque) {
    printf("\n--- PROCESSANDO PRÓXIMO PEDIDO ---\n");
    if (estaVaziaFila(filaPedidos)) {
        printf("Fila de pedidos vazia. Nada para processar.\n");
        return;
    }

    Pedido pedidoAProcessar = dequeue(filaPedidos); // Remove o pedido da fila

    printf("Processando Pedido ID: %d do solicitante: %s\n", pedidoAProcessar.id_pedido, pedidoAProcessar.nomeSolicitante);

    // Para cada item no pedido, tentar encontrar e remover do estoque
    for (int i = 0; i < pedidoAProcessar.num_itens_diferentes; i++) {
        ItemPedido item = pedidoAProcessar.itens[i];
        printf("\n  - Tentando atender item: Produto (Cód): %s, Quantidade: %d\n", item.codigo_produto, item.quantidade_solicitada);

        int quantidade_atendida = 0;
        int quantidade_restante_no_item = item.quantidade_solicitada;

        // Itera sobre todo o estoque para encontrar o produto
        for (int l = 0; l < LINHAS_ESTOQUE; l++) {
            for (int c = 0; c < COLUNAS_ESTOQUE; c++) {
                Pilha *currentPilha = &(estoque->pilhas[l][c]);
                for (int k = currentPilha->topo; k >= 0; k--) {
                    Engradado *engradadoNaPilha = &(currentPilha->itens[k]);

                    if (strcmp(engradadoNaPilha->produto.codigo, item.codigo_produto) == 0) {
                        printf("    Produto '%s' encontrado em [%d][%d], engradado na posição %d da pilha. Qtd: %d\n",
                               item.codigo_produto, l, c, k + 1, engradadoNaPilha->quantidadeAtual);

                        int pode_remover = (engradadoNaPilha->quantidadeAtual >= quantidade_restante_no_item) ?
                                          quantidade_restante_no_item : engradadoNaPilha->quantidadeAtual;

                        if (removerItensEngradado(engradadoNaPilha, pode_remover)) { // Tenta remover do engradado
                            quantidade_atendida += pode_remover;
                            quantidade_restante_no_item -= pode_remover;
                            printf("      Atendidos %d unidades. Restam %d para o item.\n", pode_remover, quantidade_restante_no_item);

                            if (engradadoNaPilha->quantidadeAtual == 0 && k == currentPilha->topo) {
                                printf("      Engradado na posição %d da pilha ficou vazio, removendo-o da pilha.\n", k + 1);
                                pop(currentPilha);
                            } else if (engradadoNaPilha->quantidadeAtual == 0) {
                                printf("      Engradado na posição %d da pilha ficou vazio, mas não é o topo, permanecerá na pilha por agora.\n", k + 1);
                            }
                        }

                        if (quantidade_restante_no_item == 0) {
                            printf("    Item de pedido para produto '%s' completamente atendido.\n", item.codigo_produto);
                            break; // Item atendido, passa para o próximo ItemPedido
                        }
                    }
                }
                if (quantidade_restante_no_item == 0) break; // Se o item foi atendido, pare de procurar em outras colunas.
            }
            if (quantidade_restante_no_item == 0) break; // Se o item foi atendido, pare de procurar em outras linhas.
        }

        if (quantidade_restante_no_item > 0) {
            printf("  AVISO: Não foi possível atender completamente o item '%s'. Faltaram %d unidades.\n",
                   item.codigo_produto, quantidade_restante_no_item);
        } else {
            printf("  Item de pedido para produto '%s' atendido com sucesso.\n", item.codigo_produto);
        }
    }
    printf("\n--- Pedido ID %d Processado. ---\n", pedidoAProcessar.id_pedido);
}

// 5. Exibir Relatórios
void exibirRelatorios(Estoque *estoque, Fila *filaPedidos) {
    printf("\n--- RELATÓRIOS ---\n");
    int opcao;
    printf("1. Visualizar Estoque Completo\n");
    printf("2. Produtos Próximos do Vencimento / Vencidos\n");
    printf("3. Posições Ocupadas e Vazias no Estoque\n");
    printf("4. Número de Pedidos na Fila\n");
    printf("Opção: ");
    scanf("%d", &opcao);
    while (getchar() != '\n');

    switch (opcao) {
        case 1:
            visualizarEstoque(estoque);
            break;
        case 2: {
            Data dataAtual; // Obter data atual para comparação
            time_t t = time(NULL);
            struct tm *tm_info = localtime(&t);
            dataAtual.dia = tm_info->tm_mday;
            dataAtual.mes = tm_info->tm_mon + 1;
            dataAtual.ano = tm_info->tm_year + 1900;

            printf("\n--- RELATÓRIO DE VALIDADE ---\n");
            int vencidos_encontrados = 0;
            int proximos_vencimento_encontrados = 0;

            printf("\nProdutos Vencidos (Data Atual: %02d/%02d/%04d):\n", dataAtual.dia, dataAtual.mes, dataAtual.ano);
            for (int i = 0; i < LINHAS_ESTOQUE; i++) {
                for (int j = 0; j < COLUNAS_ESTOQUE; j++) {
                    Pilha *currentPilha = &(estoque->pilhas[i][j]);
                    if (!estaVaziaPilha(currentPilha)) {
                        for (int k = currentPilha->topo; k >= 0; k--) {
                            Engradado engr = currentPilha->itens[k];
                            if (compararDatas(engr.produto.dataValidade, dataAtual) < 0) { // Se dataValidade < dataAtual
                                printf("  VENCIDO: [%d][%d] - %s (Lote: %s), Validade: ", i, j, engr.produto.nome, engr.produto.lote);
                                imprimirData(engr.produto.dataValidade);
                                printf("\n");
                                vencidos_encontrados = 1;
                            }
                        }
                    }
                }
            }
            if (!vencidos_encontrados) printf("  Nenhum produto vencido encontrado.\n");


            printf("\nProdutos Próximos do Vencimento (Próximos 60 dias da Data Atual: %02d/%02d/%04d):\n", dataAtual.dia, dataAtual.mes, dataAtual.ano);

            Data dataFutura;
            dataFutura.dia = dataAtual.dia;
            dataFutura.mes = dataAtual.mes + 2;
            dataFutura.ano = dataAtual.ano;
            if (dataFutura.mes > 12) {
                dataFutura.mes -= 12;
                dataFutura.ano++;
            }

            for (int i = 0; i < LINHAS_ESTOQUE; i++) {
                for (int j = 0; j < COLUNAS_ESTOQUE; j++) {
                    Pilha *currentPilha = &(estoque->pilhas[i][j]);
                    if (!estaVaziaPilha(currentPilha)) {
                        for (int k = currentPilha->topo; k >= 0; k--) {
                            Engradado engr = currentPilha->itens[k];
                            // Se não está vencido E a validade é antes da data futura (ou igual)
                            if (compararDatas(engr.produto.dataValidade, dataAtual) >= 0 &&
                                compararDatas(engr.produto.dataValidade, dataFutura) <= 0) {
                                printf("  PRÓXIMO: [%d][%d] - %s (Lote: %s), Validade: ", i, j, engr.produto.nome, engr.produto.lote);
                                imprimirData(engr.produto.dataValidade);
                                printf("\n");
                                proximos_vencimento_encontrados = 1;
                            }
                        }
                    }
                }
            }
            if (!proximos_vencimento_encontrados) printf("  Nenhum produto próximo do vencimento encontrado (nos próximos 60 dias aproximadamente).\n");

            printf("------------------------------\n");
            break;
        }
        case 3:
            printf("\n--- POSIÇÕES NO ESTOQUE ---\n");
            int ocupadas = 0;
            int vazias = 0;
            for (int i = 0; i < LINHAS_ESTOQUE; i++) {
                for (int j = 0; j < COLUNAS_ESTOQUE; j++) {
                    if (estaVaziaPilha(&(estoque->pilhas[i][j]))) {
                        printf("  [%d][%d]: Vazia\n", i, j);
                        vazias++;
                    } else {
                        printf("  [%d][%d]: Ocupada (Engradados: %d/%d)\n", i, j,
                               estoque->pilhas[i][j].topo + 1, MAX_ENGRADADOS_POR_PILHA);
                        ocupadas++;
                    }
                }
            }
            printf("Resumo: %d posições ocupadas, %d posições vazias (Total: %d).\n", ocupadas, vazias, LINHAS_ESTOQUE * COLUNAS_ESTOQUE);
            printf("---------------------------\n");
            break;
        case 4:
            printf("\n--- NÚMERO DE PEDIDOS NA FILA ---\n");
            printf("Total de pedidos aguardando: %d\n", filaPedidos->tamanho);
            imprimirFilaPedidos(filaPedidos);
            printf("----------------------------------\n");
            break;
        default:
            printf("Opção de relatório inválida.\n");
            break;
    }
}