#include <stdio.h>
int main(){

double valormonetario;
scanf("%lf", &valormonetario);

int valor = valormonetario*100;

int notas[12] = {10000, 5000, 2000, 1000, 500, 200, 100, 50, 25, 10, 5, 1};
int i;
int contador = 0;
double cedula = 0;

printf("NOTAS:\n");
for(i = 0;i < 12; i++){
    if(i == 6){
        printf("MOEDAS:\n");

        contador = valor/notas[i];
        valor = valor%notas[i];
        cedula = notas[i];
        cedula = cedula/100;

        printf("%d moeda(s) de R$ %.2lf\n", contador, cedula);
    }
    if(i > 6){

        contador = valor/notas[i];
        valor = valor%notas[i];
        cedula = notas[i];
        cedula = cedula/100;

        printf("%d moeda(s) de R$ %.2lf\n", contador, cedula);
    }
    else if (i < 6) {
        contador = valor/notas[i];
        valor = valor%notas[i];

        printf("%d nota(s) de R$ %d.00\n", contador, notas[i]/100);
    }

}
return 0;
}
