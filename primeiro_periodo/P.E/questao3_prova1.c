#include <stdio.h>

int main(){

    int i, num_par, num_impar, num;
    num_par = 0;
    num_impar = 1;
    for(i=0; i<100; i++){
        scanf("%d", &num);
        if(num % 2 == 0){
            num_par += num;
        }else{
            num_impar = num * num_impar;
        }
    }

    printf("Produto dos numeros impares: %d \nSoma dos pares: %d", num_impar, num_par);

    return 0;
}
