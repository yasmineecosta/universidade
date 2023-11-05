#include <stdio.h>

int main(){

    float num;
    // 0,25     25,50   50,75   75,100
    scanf("%f", &num);
    if((num>=0.0) && (num<=25.00)){
        printf("Intervalo [0,25]\n");
    }
    else if((num>25) && (num<=50.00)){
        printf("Intervalo (25,50]\n");
    }
    else if((num>50) && (num<=75.00)){
        printf("Intervalo (50,75]\n");
    }
    else if((num>75) && (num<=100.00)){
        printf("Intervalo (75,100]\n");
    }
    else{
        printf("Fora de intervalo\n");
    }

    return 0;

}
