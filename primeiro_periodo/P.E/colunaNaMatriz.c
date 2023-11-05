#include <stdio.h>
#define TAM 4

int main(){
        float M[TAM][TAM];
        char T;
        int i, j, C;
        float soma;
        soma = 0;
        scanf("%d", &C);
        scanf(" %c", &T);
            for(i=0; i<TAM; i++){
                for(j=0; j<TAM; j++){
                    scanf("%f", &M[i][j]);
                }
            }

            for(i=0;i<TAM;i++){
                for(j=0; j<TAM; j++){
                    if((j+1) == C){
                        soma = soma + M[i][j];
                    }
                }
            }
            if((soma != 0) && (T == 'S'))
                        printf("%.1f", soma);
                if((soma != 0) && (T == 'M'))
                        printf("%.1f", soma/TAM);
    return 0;
}
