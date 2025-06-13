#include "data.h"
#include <stdio.h>

void inicializarData(Data *d, int dia, int mes, int ano) {
    if (d != NULL) {
        d->dia = dia;
        d->mes = mes;
        d->ano = ano;
    }
}

void imprimirData(Data d) { // <<< CORRIGIDO: Recebe Data por valor
    printf("%02d/%02d/%04d", d.dia, d.mes, d.ano);
}

// Retorna:
// < 0 se d1 < d2
//   0 se d1 = d2
// > 0 se d1 > d2
int compararDatas(Data d1, Data d2) {
    if (d1.ano != d2.ano) {
        return d1.ano - d2.ano;
    }
    if (d1.mes != d2.mes) {
        return d1.mes - d2.mes;
    }
    return d1.dia - d2.dia;
}