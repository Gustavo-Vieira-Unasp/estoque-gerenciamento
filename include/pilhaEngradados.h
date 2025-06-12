#ifndef PILHAENGRADADOS_H
#define PILHAENGRADADOS_H

#include "engradado.h"

#define MAX_ENGRADADOS_POR_PILHA 5

typedef struct
{
    Engradado itens[MAX_ENGRADADOS_POR_PILHA]; 
    int topo;                                  
} Pilha;


void inicializarPilha(Pilha *p);

int estaVaziaPilha(Pilha *p);

int estaCheiaPilha(Pilha *p);

int push(Pilha *p, Engradado e);

Engradado pop(Pilha *p);

Engradado peek(Pilha *p);

void imprimirPilha(Pilha *p);

#endif