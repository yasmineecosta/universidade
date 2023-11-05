#include <stdio.h>

int main() {

    float nota, notas, soma, media;
    int resp;

    do{
        notas = 0;
        soma = 0;
        media = 0;
            do{
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
            }while(notas != 2);

            do{
                printf("novo calculo (1-sim 2-nao)");
                scanf("%d", &resp);
            }while((resp < 1) || (resp > 2));
        }while(resp == 1);

    return 0;
}
