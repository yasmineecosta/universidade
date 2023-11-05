#include <stdio.h>

int main(){

    int vendas[12][4];
    int i, j, total;
    int cont[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    int maior = 0;
    int anototal = 0;
    total = 0;
    printf("Digite a matriz: \n");

    for(i=0; i<12; i++){
        for(j=0; j<4; j++){
            scanf("%d", &vendas[i][j]);
        }
    }

    for(i=0; i<12; i++){
        for(j=0; j<4; j++){
            total += vendas[i][j];
            printf("Total mes %d: %d\n", j+1, total);
        }

        total = 0;
    }


    for(j=0; j<4; j++){
        for(i=0; i<12; i++){
            total += vendas[i][j];
        }
        printf("Total semana %d: %d\n", j+1, total);
        total = 0;
    }

    for(i=0; i<12;i++){
        for(j=0;j<4;j++){
            anototal += vendas[i][j];
        }
    }
    printf("Total no ano: %d\n", anototal);

    for(i=0; i<12; i++){
        for(j=0; j<4; j++){
            if(vendas[i][j] == 0)
                cont[i]++;
        }
    }

    for(i=0; i<12; i++){
        if(maior < cont[i])
            maior = cont[i];
    }
    printf("mes(es) com mais semanas sem vender redes: ");
    for(i=0; i<12; i++){
        if(maior == cont[i]){
            printf("%d ", i+1);
        }
    }

    return 0;
}
