#include <stdio.h>

int main(){

    int tempo_gasto, velocidade_media;
    float litros_neces, km;
    //12km/litro

    scanf("%d %d", &tempo_gasto, &velocidade_media);

    km = velocidade_media*tempo_gasto;
    litros_neces = km/12;

    printf("%.3f\n", litros_neces);


    return 0;

}
