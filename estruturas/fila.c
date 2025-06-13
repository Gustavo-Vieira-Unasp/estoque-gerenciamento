#include <stdio.h>
#include <stdlib.h> //Para EXIT_FAILURE

#define MAX_FILA 100 //Renomeei para evitar conflito com MAX_NOME, etc.

//Define a estrutura da Fila
typedef struct
{
    int itens[MAX_FILA]; //Array para armazenar os itens
    int frente;          //Índice do elemento da frente da fila
    int tras;            //Índice do elemento de trás da fila
    int tamanho;         //Número atual de elementos na fila
} Fila;

//Inicializa a fila, definindo seus índices e tamanho
void inicializarFila(Fila *f)
{
    f->frente = 0;   //Frente começa no índice 0
    f->tras = -1;    //Trás começa em -1 (indicando fila vazia, nenhum elemento válido ainda)
    f->tamanho = 0;  //Tamanho inicial é 0
}

//Verifica se a fila está vazia
int estaVazia(Fila *f)
{
    return (f->tamanho == 0);
}

//Verifica se a fila está cheia
int estaCheia(Fila *f)
{
    return (f->tamanho == MAX_FILA);
}

//Adiciona um item ao final da fila (enqueue)
void enqueue(Fila *f, int valor)
{
    if (estaCheia(f))
    {
        printf("Erro: fila está cheia. Não é possível adicionar o item %d.\n", valor);
        return; //Sai da função sem adicionar
    }

    //Calcula o próximo índice para 'tras' de forma circular
    f->tras = (f->tras + 1) % MAX_FILA;
    f->itens[f->tras] = valor; //Adiciona o valor
    f->tamanho++;              //Incrementa o tamanho
}

//Remove e retorna o item da frente da fila (dequeue)
int dequeue(Fila *f)
{
    if (estaVazia(f))
    {
        printf("Erro: fila está vazia. Não é possível remover item.\n");
        exit(EXIT_FAILURE);
    }

    int valor = f->itens[f->frente]; //Pega o valor da frente
    //Calcula o próximo índice para 'frente' de forma circular
    f->frente = (f->frente + 1) % MAX_FILA;
    f->tamanho--; //Decrementa o tamanho
    return valor; //Retorna o valor removido
}

//Retorna o item da frente da fila sem removê-lo (front/peek)
int front(Fila *f)
{
    if (estaVazia(f))
    {
        printf("Erro: fila está vazia. Não há item para consultar.\n");
        exit(EXIT_FAILURE);
    }

    return f->itens[f->frente]; //Retorna o valor da frente
}
