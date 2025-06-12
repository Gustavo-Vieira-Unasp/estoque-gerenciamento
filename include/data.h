#ifndef DATA_H
#define DATA_H

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

void imprimirData(Data d);
int compararDatas(Data d1, Data d2);

#endif