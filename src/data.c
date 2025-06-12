#include "data.h"
#include <stdio.h>

void imprimirData(Data d) {
    printf("%02d/%02d/%04d", d.dia, d.mes, d.ano);
}

int compararDatas(Data d1, Data d2) {
    if (d1.ano < d2.ano) return -1;         //Verfica se já passou do ano
    if (d1.ano > d2.ano) return 1;
    if (d1.mes < d2.mes) return -1;         //Verifica se já passou do mês
    if (d1.mes < d2.mes) return 1;
    if (d1.dia < d2.dia) return -1;         //Verifica se passou do dia
    if (d1.dia > d2.dia) return 1;
    return 0;
}