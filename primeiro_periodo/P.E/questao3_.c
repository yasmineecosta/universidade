#include <stdio.h>
int main(){
    int X[5], Y[5], U[10], I[10];
    int i, j, a, k, b;
    for( i = 0 ; i < 5 ; i++ ){
        scanf("%d", &X[i]);
    }
    for( i = 0 ; i < 5 ; i++ ){
        scanf("%d", &Y[i]);
    }
    for( i = 0 ; i < 5 ; i++ ){
        U[i] = X[i];
    }
    k = 5;
    a = 0;
    for( i = 0 ; i < 5 ; i++ ){
        for( j = 0 ; j < 5 ; j++ ){
            if(Y[i] != X[j]){
                a++;
            }
        }
        if(a == 5){
            U[k] = Y[i];
            k++;
        }
        a = 0;
    }

    for( i = 0 ; i < k ; i++ ){
        printf("Uniao: %d\n", U[i]);
    }
    b = 0;
    for( i = 0 ; i < 5 ; i++ ){
        for( j = 0 ; j < 5 ; j++ ){
            if(X[i] == Y[j]){
                I[b] = X[i];
                b++;
                break;
            }
        }
    }
    for( i = 0 ; i < b ; i++ ){
        printf("Intersecao: %d\n", I[i]);
    }

    return 0;
}
