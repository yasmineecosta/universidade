#include <stdio.h>

int main(){

    int num[16], i, j, k;
    int matriz[4][4];
    k = 0;
    int soma = 0;
    int linhaZ = 0;

    for(i=0; i<16;i++){
        scanf("%d", &num[i]);
    }

    for(i=0; i<4;i++){
        for(j=0;j<4;j++){
            matriz[i][j] = num[k];
            k++;
        }
    }

    for(i=0; i<4;i++){
        for(j=0;j<4;j++){
            soma += matriz[i][j];
        }
        if(soma == 0)
            linhaZ++;
        soma = 0;
    }

    printf("A resposta seria: %d linhas", linhaZ);
    return 0;

}
