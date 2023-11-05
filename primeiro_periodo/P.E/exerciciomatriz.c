#include <stdio.h>
#define A 3
#define B 4

void imprimeTotalProduto(int e[A][B]){
    int i, j, soma[B];
    printf("Total de cada produto: \n");
    for(i=0; i<B; i++){
        soma[i] = 0;
        for(j=0; j<A; j++){
            soma[i] = soma[i] + e[j][i];
        }
        printf("PRODUTO %d: %d\n", i+1, soma[i]);
    }
}


void custoTotalProd(int e[A][B], float vet[B]){
    int i, j;
    int soma = 0;

}

void LerEstoque(int e[A][B]){
    int i, j;
    printf("Escreva o estoque inicial:\n");
    for(i=0; i<A; i++){
            printf("Armazem %d\n", i+1);
        for(j=0;j<B; j++){
            printf("Produto %d: ", j+1);
            scanf("%d", &e[i][j]);
        }

    }
}

void LerCusto(float valor[B]){
    int i;
    printf("Escreva o custo de cada tipo de produto:\n");
    for(i=0; i<B    ; i++){
        printf("Produto %d:", i+1);
        scanf("%f", valor[i]);
    }
}

int menu(){
    int menu;
    printf("----MENU----\n");
    printf("1 - Estoque por produto\n");
    printf("2 - Estoque por armazem\n");
    printf("3 - Total em cada armazem\n");
    printf("4 - Total de cada produto\n");
    printf("5 - Custo total por armazem\n");
    printf("6 - Custo total por produto\n");
    printf("7 - Alterar quantidade de um produto\n");
    printf("8 - Alterar custo de um produto\n");
    printf("0 - Sair\n");
    scanf("%d", &menu);
    return menu;
}

void imprimeProd(int prod[]){
    int i;
    for(i=0; i<B; i++){
        printf("Produto %d: %d\n", i+1, prod[i]);
    }
}

void imprime(int e[A][B]){
    int i;
    for(i=0; i<A; i++){
        printf("ARMAZEM %d\n", i+1);
        imprimeProd(e[i]);
    }
}

int main(){
    int estoque[A][B];
    float custo[B];
    int resp;

    LerEstoque(estoque);
    LerCusto(custo);

    do{
        resp = menu();

        switch(resp){
            case 1:

                    break;
            case 2:
                    break;
            case 3:
                    break;
            case 4:

                    break;
            case 5:
                    break;
            case 6:
                    custoTotalProd(estoque, custo);
                    break;
            case 7:

                    break;
            case 8:
                    break;
            case 0:
                    break;
            default:
                    printf("Opcao invalida!\n\n");
        }
    }while(resp != 0);

    return 0;
}
