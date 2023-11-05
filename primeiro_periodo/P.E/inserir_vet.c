#include <stdio.h>

int main(){

    int vet[10];
    int i, a, num;
    a = 0;

    for(i=0;i<10;i++){
        scanf("%d", &vet[i]);
    }
    scanf("%d", &num);

    for(i=0; i<10; i++){
        if(num == vet[i])
        a = 1;
    }

    if(a != 0){
        printf("O numero %d esta entre os numeros", num);
    }else{
        printf("O numero %d nao esta entre os 10 numeros", num);
    }

    return 0;
}
