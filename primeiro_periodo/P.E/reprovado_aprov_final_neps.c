#include <stdio.h>

int main(){
    float N1, N2, mediaPond;
    0.0 <= N1 <= 10.0;
    0.0 <= N2 <= 10.0;

    scanf("%f %f", &N1, &N2);//inserindo as notas

    mediaPond = ((N1*2) + (N2*3)) /5;   //equacao da media

    if(mediaPond < 3.0){
        printf("Reprovado");
    }else if(mediaPond>= 3.0 && mediaPond < 7.0){
        printf("Final");
    }else{
        printf("Aprovado");
    }

    return 0;
}
