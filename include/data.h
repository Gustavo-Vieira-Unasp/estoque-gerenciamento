#ifndef DATA_H
#define DATA_H

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

// Protótipos das funções de Data
void inicializarData(Data *d, int dia, int mes, int ano);
void imprimirData(Data d); // <<< CORRIGIDO: Recebe Data por valor
int compararDatas(Data d1, Data d2);

#endif