#include <stdio.h>
#define TAM 5
int main(){

    int X[TAM], Y[TAM], U[10], I[TAM], i, j, k, p,q;

    printf("Digite os elementos de X:\n");
    for(i=0;i<TAM;i++){
        scanf("%d", &X[i]);
    }

    printf("Digite os elementos de Y:\n");
    for(i=0;i<TAM;i++){
        scanf("%d", &Y[i]);
    }

    for(i=0;i<TAM;i++){
        for(j=0; j<TAM; j++){
            if(X[i] == Y[j]){
                I[k] = Y[j];
                k++;
            }
        }
    }

    for(i=0;i<TAM;i++){
        U[i] = X[i];
    }
    p = 5;
    q = 0;

    for(i=0;i<TAM;i++){
        for(j=0;j<TAM;j++){
            if(Y[i] != X[j]){
                q++;
            }
        }

        if(q == 5){
            U[p] = Y[i];
            p++;
        }

        q = 0;
    }

    printf("Uniao: ");
    for(i=0; i<p; i++){
        printf("%d ", U[i]);
    }

    printf("Interseccao: ");
    for(i=0; i<k; i++){
        printf("%d ", I[i]);
    }

    return 0;
}
