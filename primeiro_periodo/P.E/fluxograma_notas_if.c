#include <stdio.h>

int main(){
    int nota1,nota2,nota3;

    scanf("%d %d %d", &nota1, &nota2, &nota3);

    int media = (nota1+nota2+nota3) / 3;

    if(media>=7){
        printf("A");
    }
    if(media<4){
        printf("R");
    }
    if(media>=4 && media<7){
        printf("EF");
    }

    return 0;
}
