#include <stdio.h>

int main() {

    float vet[5];
    int i;

    for(i = 0; i<5; i++){
        scanf("%f", &vet[i]);
    }

    for(i=0; i<5;i++){
        if(vet[i] <= 10){
            printf("A[%d] = %.2f\n", i, vet[i]);
        }
    }



    return 0;
}
