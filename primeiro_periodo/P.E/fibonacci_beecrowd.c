#include <stdio.h>
int fib(int x){
    if(x == 0){
        return 0;
    }
    if(x == 1){
        return 1;
    }
    else{
        return fib(x-1) + fib(x-2);
    }
}
int main(){

    int T, i;
    scanf("%d", &T);
    int vet[T];
    for(i=0; i<T; i++){
        scanf("%d", &vet[i]);
    }

    for(i=0; i<T; i++){
        printf("Fib(%d) = %d\n", vet[i], fib(vet[i]));
    }

    return 0;
}
