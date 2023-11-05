#include <stdio.h>

int main(){

    char nome[30];
    double salario, vendas;
    scanf("%s", nome);
    scanf("%lf", &salario);
    scanf("%lf", &vendas);

    printf("TOTAL = R$ %.2f\n", salario + ((vendas*15) / 100));

    return 0;
}
