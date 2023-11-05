#include <stdio.h>

int main(){
    int flavio[6], lot[6];
    int i, j;
    int acertou = 0;

    for(i=0; i<6; i++){
        scanf("%d", &flavio[i]);
    }
    for(j=0; j<6; j++){
        scanf("%d", &lot[j]);
    }
    for(i=0; i<6; i++){
        for(j=0; j<6; j++){
            if(flavio[i] == lot[j]){
                acertou++;
            }
        }
    }

    if(acertou == 3){
        printf("terno\n");
    }if(acertou == 4){
        printf("quadra\n");
    }if(acertou == 5){
        printf("quina\n");
    }if(acertou == 6){
        printf("sena\n");
    }if(acertou < 3){
        printf("azar\n");
    }
    return 0;
}
