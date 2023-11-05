#include <stdio.h>

int main(){
    int nota1, nota2, nota3;

    scanf("%d %d %d", &nota1, &nota2, &nota3);

    int media = (nota1+nota2+nota3)/3;

    if(media>=7){
        printf("A");
    }else if(media<4){
        printf("R");
    }else{
        printf("EF");
    }

    return 0;
}
