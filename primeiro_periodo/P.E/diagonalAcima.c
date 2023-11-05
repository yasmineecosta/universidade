#include <stdio.h>
#define TAM 12

int main(){
    char O;
    float M[TAM][TAM];
    float soma;
    soma = 0;
    int i, j, quant;
    quant = 0;
    scanf(" %c", &O);

        for(i=0; i<TAM; i++){
            for(j=0; j<TAM; j++){
                scanf("%f", &M[i][j]);
            }
        }

        for(i=0;i<TAM-1; i++){
            for(j=1;j<TAM;j++){
                if(j>i){
                    soma = soma + M[i][j];
                    quant++;
                }
            }
        }

        if(O == 'S')
            printf("%.1f\n", soma);
        if(O == 'M')
            printf("%.1f\n", soma/quant);
    return 0;
}
