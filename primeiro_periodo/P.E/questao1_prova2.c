#include <stdio.h>

int main(){

    int codigo[5], i, quant, cod_prod;
    int cont=0;
    float preco[5], valor;

    for(i=0; i<5; i++){

        printf("Digite o codigo e o preco do produto %d: ",i+1);
        scanf("%d %f", &codigo[i], &preco[i]);
        printf("\n");
    }

    printf("Digite o codigo e a quantidade desejada: ");
    scanf("%d %d", &cod_prod, &quant);

    for(i=0; i<5; i++){
        if(codigo[i] == cod_prod){
            valor = preco[i] * quant;
        }else{
            cont++;
        }
    }
    if(cont==5){
        printf("Produto nao encontrado\n");
    }else{
        printf("Valor a pagar: %.2f\n", valor);
    }

    return 0;
}
