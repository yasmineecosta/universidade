#include <stdio.h>

int main(){

    int idade_dias;
    int ano, mes, dia;
    int resto1, resto2;

    scanf("%d", &idade_dias);

    ano = idade_dias/365;
    resto1 = idade_dias%365;

    mes = resto1/30;
    resto2 = resto1%30;

    dia = resto2;

    printf("%d ano(s)\n", ano);
    printf("%d mes(es)\n", mes);
    printf("%d dia(s)\n", dia);


    return 0;
}
