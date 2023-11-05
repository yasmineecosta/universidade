#include <stdio.h>

int main(){

    float a,b,c;
    scanf("%f %f %f",&a,&b,&c);
    int num = -1;
    float area, p;
    if((a<(b+c)) && (b<(a+c)) && (c<(a+b))){
        num = 1;
    }else{
        num = 0;
    }

    area = ((a+b) * c)/2;
    p = a + b + c;
    if(num == 1){
        printf("Perimetro = %.1f\n", p);
    }
    if(num == 0){
        printf("Area = %.1f\n", area);
    }

    return 0;

}
