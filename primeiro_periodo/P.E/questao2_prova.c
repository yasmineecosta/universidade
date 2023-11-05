#include <stdio.h>

int main(){

    int quant;
    float preco;

    scanf("%d", &quant);

    if(quant < 12){
        preco = 2.3*quant;
    }else{
        preco = 2.0*quant;
    }

    printf("%.2f", preco);

    return 0;
}
