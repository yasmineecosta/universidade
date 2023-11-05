#include <stdio.h>

int main() {

    float nota, notas, soma, media;
    int resp;
    soma = notas = resp = 0;

    while(1){

        scanf("%f", &nota);

            if((nota < 0.0) || (nota > 10.0)){
                printf("nota invalida\n");
            }else{
                soma += nota;
                notas++;
                    if(notas == 2){
                        media = soma/2;
                        printf("media = %.2f\n", media);
                    }
                }
        do{
            printf("novo calculo (1-sim 2-nao)");
            scanf("%d", &resp);
        }while((resp < 1) && (resp > 2));


    }
    return 0;
}
