#include <stdio.h>

int coisa(float a, float b, float c, float *perimetro){

    if(((a+b)>c) && ((a+c)>b) && ((b+c)>a)){
        *perimetro = a+b+c;
        return 1;
    }else{
        *perimetro = 0;
        return 0;
    }

}

int main(){
    float a, b, c, perimetro;

    scanf("%f %f %f", &a,&b,&c);

    int triangulo;
    triangulo = coisa(a,b,c, &perimetro);

    if(triangulo == 1){
        printf("e triangulo perimetro = %f", perimetro);
    }else{
        printf("Nao e triangulo. perimetro = %f", perimetro);
    }

}
