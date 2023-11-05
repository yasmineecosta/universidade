#include <stdio.h>
#define TAM 6

void preenche(int v[]){
    int i;
    for(i=0; i<TAM; i++){
        scanf("%d",&v[i]);
    }
}

void troca(int *x, int *y){
    int temp;
    temp = *x;
    *x = *y;
    *y=temp;
}

void inverte(int v[]){
    int i, j;
    for(i=0,j=TAM-1; i<TAM/2;i++,j--){
        troca(&v[i],&v[j]);
    }
}

void imprime(int v[]){
    int i;
    printf("Saida: ");
    for(i=0; i<TAM; i++){
        printf(" %d ", v[i]);
    }
}

int main(){
    int vet[TAM];
    preenche(vet);
    inverte(vet);
    imprime(vet);

    return 0;
}
