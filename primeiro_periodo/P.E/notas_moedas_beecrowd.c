#include <stdio.h>

int main(){

    float valor;
    int nota100, nota50, nota20, nota10, nota5, nota2;
    int moeda1, moeda50, moeda25, moeda10, moeda05, moeda01;
    float resto100, resto50, resto20, resto10, resto5, resto2;
    int resto1, resto050, resto025, resto010, resto005, resto001;
    scanf("%f", &valor);

    nota100 = valor/100;
    resto100 = fmod(valor,100);

    nota50 = resto100/50;
    resto50 = fmod(resto100,50);

    nota20 = resto50/20;
    resto20 = fmod(resto50,20);

    nota10 = resto20/10;
    resto10 = fmod(resto20,10);

    nota5 = resto10/5;
    resto5 = fmod(resto10,5);

    nota2 = resto5/2;
    resto2 = fmod(resto5,2);

    moeda1 = resto2;
    resto1 = fmod(resto2,1.0);

    moeda50 = resto1/0.50;
    resto050 = fmod(resto1,0.50);

    moeda25 = resto050/0.25;
    resto025 = fmod(resto050,0.25);

    moeda10 = resto025/0.10;
    resto010 = fmod(resto025,0.10);

    moeda05 = resto010/0.05;
    resto005 = fmod(resto010,0.05);

    moeda01 = resto005/0.01;
    resto001 = fmod(resto005, 0.01);

    printf("NOTAS:\n");
    printf("%d nota(s) de R$ 100.00\n", nota100);
    printf("%d nota(s) de R$ 50.00\n", nota50);
    printf("%d nota(s) de R$ 20.00\n", nota20);
    printf("%d nota(s) de R$ 10.00\n", nota10);
    printf("%d nota(s) de R$ 5.00\n", nota5);
    printf("%d nota(s) de R$ 2.00\n", nota2);

    //moedas:
    printf("MOEDAS:\n");
    printf("%d moeda(s) de R$ 1.00\n", resto1);
    printf("%d moeda(s) de R$ 0.50\n", resto050);
    printf("%d moeda(s) de R$ 0.25\n", resto025);
    printf("%d moeda(s) de R$ 0.10\n", resto010);
    printf("%d moeda(s) de R$ 0.05\n", resto005);
    printf("%d moeda(s) de R$ 0.01\n", resto001);


    printf("%d %d %d %d", resto2, resto1, resto050, resto025);

    return 0;

}
