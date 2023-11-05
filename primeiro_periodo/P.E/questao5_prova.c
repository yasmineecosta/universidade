#include <stdio.h>
#include <math.h>

int main(){

    int num, cont, baixos, altos;

    for(cont=1000; cont<=9999; cont++){
        baixos = cont % 100;
        altos = cont / 100;
        num = (baixos + altos) * (baixos + altos);
        if(num == cont)
            printf("%d\n", num);

    }

    return 0;
}
