#include <stdio.h>
#define TAM 5
int main(){

    int v[TAM];
    int troca, i;

    for(i=0; i<TAM; i++){
        scanf("%d", &v[i]);
    }

    for(i=0; i<TAM/2; i++){
        troca = v[i];
        v[i] = v[TAM-1-i];
        v[TAM-1-i] = troca;
    }

    for(i=0;i<TAM; i++){
        printf("%d", v[i]);
    }
    return 0;
}
