#include <stdio.h>

int main(){
    int num, con;
    int soma = 0;
    int prod = 1;

    for(con=1; con <= 100; con++){
        printf("Digite o numero:");
        scanf("%d", &num);
            if(num%2 != 0){
                prod = num * prod;
            }else if(num%2 == 0){
                soma = soma + num;
            }
    }

    printf("Produto dos numeros impares: %d\n", prod);
    printf("Soma dos numeros pares: %d\n", soma);
    return 0;

}
