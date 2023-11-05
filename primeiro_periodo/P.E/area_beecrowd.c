#include <stdio.h>
#include <math.h>
int main(){

    float A,B,C;
    scanf("%f %f %f", &A,&B,&C);
    float triangulo_ret, circulo, trapezio, quadrado, retangulo;
    //1 area do triangulo retangulo
    triangulo_ret = (A*C)/2.0;
    //2  area circulo raio C
    circulo = 3.14159*pow(C,2);
    //3 area do trapezio
    trapezio = ((A+B)/2) * C;
    //4 area do quadrado
    quadrado = pow(B,2);
    //5 area do retangulo
    retangulo = A*B;

    printf("TRIANGULO: %.3f\n", triangulo_ret);
    printf("CIRCULO: %.3f\n", circulo);
    printf("TRAPEZIO: %.3f\n", trapezio);
    printf("QUADRADO: %.3f\n", quadrado);
    printf("RETANGULO: %.3f\n", retangulo);


    return 0;
}
