#include <stdio.h>
#include <stdlib.h>

#define MAX_PILHA 5 

//Define a estrutura da Pilha
typedef struct
{
    int itens[MAX_PILHA]; //Array para armazenar os itens
    int topo;             //Índice do topo da pilha
} Pilha;

//Inicializa a pilha, definindo o topo como -1 (pilha vazia)
void inicializarPilha(Pilha *p)
{
    p->topo = -1;
}

//Verifica se a pilha está vazia
int estaVaziaPilha(Pilha *p) 
{
    return (p->topo == -1);
}

//Verifica se a pilha está cheia
int estaCheiaPilha(Pilha *p)
{
    return (p->topo == MAX_PILHA - 1);
}

//Adiciona um item ao topo da pilha (push)
void push(Pilha *p, int valor)
{
    if (estaCheiaPilha(p))
    {
        printf("Erro: Pilha cheia. Não é possível adicionar o item %d.\n", valor);
        return; //Sai da função sem adicionar
    }

    p->topo++;                 //Incrementa o topo
    p->itens[p->topo] = valor; //Adiciona o valor no topo
}

//Remove e retorna o item do topo da pilha (pop)
int pop(Pilha *p)
{
    if (estaVaziaPilha(p))
    {
        printf("Erro: Pilha vazia. Não é possível remover item.\n");
        exit(EXIT_FAILURE); //Termina o programa se tentar remover de uma pilha vazia
    }

    int valor = p->itens[p->topo]; //Pega o valor do topo
    p->topo--;                     //Decrementa o topo
    return valor;                  //Retorna o valor removido
}

//Retorna o item do topo da pilha sem removê-lo (peek/top)
int peek(Pilha *p)
{
    if (estaVaziaPilha(p))
    {
        printf("Erro: Pilha vazia. Não há item para consultar.\n");
        exit(EXIT_FAILURE); //Termina o programa se tentar consultar uma pilha vazia
    }

    return p->itens[p->topo]; //Retorna o valor do topo
}