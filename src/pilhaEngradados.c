#include "pilhaEngradados.h"
#include "engradado.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int estaVaziaPilha(Pilha *p) {
    return (p->topo == -1);
}

int estaCheiaPilha(Pilha *p) {
    return (p->topo == MAX_ENGRADADOS_POR_PILHA - 1);
}

int push(Pilha *p, Engradado e) {
    if (estaCheiaPilha(p)) {
        printf("Erro: Pilha cheia. Não é possível adicionar o engradado.\n");
        return 0;
    }

    p->topo++;                     
    p->itens[p->topo] = e;         
    printf("SUCESSO: Engradado adicionado à pilha. Topo: %d.\n", p->topo);
    return 1;
}

Engradado pop(Pilha *p) {
    if (estaVaziaPilha(p)) {
        printf("Erro: Pilha vazia. Não é possível remover engradado.\n");
        exit(EXIT_FAILURE);
    }

    Engradado engradadoRemovido = p->itens[p->topo];
    p->topo--;                                       
    printf("SUCESSO: Engradado removido da pilha. Novo topo: %d.\n", p->topo);
    return engradadoRemovido;    
}

Engradado peek(Pilha *p) {
    if (estaVaziaPilha(p)) {
        printf("Erro: Pilha vazia. Não há engradado para consultar.\n");
        exit(EXIT_FAILURE);
    }

    return p->itens[p->topo];
}

void imprimirPilha(Pilha *p) {
    printf("\n--- Conteúdo da Pilha (LIFO) ---\n");
    if (estaVaziaPilha(p)) {
        printf("Pilha vazia.\n");
    } else {
        for (int i = p->topo; i >= 0; i--) {
            printf("Posição %d: \n", i);
            imprimirEngradado(p ->itens[i]); 
            printf("---\n");
        }
    }
}