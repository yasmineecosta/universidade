#include <stdio.h>

int main(){

    int num, numaior;
    numaior = - 9999;

    do{
        scanf("%d", &num);
        if(num == 0)
            break;

        if(num>numaior){
            numaior = num;
        }else{
            printf("rejeitado: %d\n", num);
        }
    }while(num != 0);

    return 0;
}
