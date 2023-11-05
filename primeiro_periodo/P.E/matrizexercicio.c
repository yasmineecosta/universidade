#include <stdio.h>
#define A 3
#define B 4

void imprimePorProd(int e[A][B]){
    int i, j;
    printf("OPCAO 1 DO MENU:\n");
    printf("ESTOQUE POR PRODUTO:\n");
    for(i=0; i<B; i++){
        printf("PRODUTO %d:\n", i+1);
        for(j=0; j<A; j++){
            printf("Armazem %d: %d\n", j+1, e[j][i]);
        }
    }
}

void imprimePorArmazem(int e[A][B]){
    int i, j;
    printf("OPCAO 2 DO MENU:\n");
    printf("ESTOQUE POR ARMAZEM:\n");
    for(i=0;i<A;i++){
        printf("ARMAZEM %d:\n", i+1);
        for(j=0;j<B;j++){
            printf("Produto %d: %d\n", j+1, e[i][j]);
        }
    }
}

void imprimeTotalArmazem(int e[A][B]){
    int i, j, soma[B];
    printf("OPCAO 3 DO MENU:\n");
    printf("Total de produtos por armazem: \n");
    for(i=0;i<A;i++){
        soma[i] = 0;
        for(j=0; j<B; j++){
            soma[i] = soma[i] + e[i][j];
        }
        printf("ARMAZEM %d: %d\n", i+1, soma[i]);
    }
}

void imprimeTotalProduto(int e[A][B]){
    int i, j, soma[B];
    printf("OPCAO 4 DO MENU: \n");
    printf("Total de cada produto: \n");
    for(i=0; i<B; i++){
        soma[i] = 0;
        for(j=0; j<A; j++){
            soma[i] = soma[i] + e[j][i];
        }
        printf("PRODUTO %d: %d\n", i+1, soma[i]);
    }
}

void custoTotalArmazem(int e[A][B], float vet[B]){
    int i, j;
    int soma[B];
    float somavalor[B];
    printf("OPCAO 5 DO MENU:\n");
    printf("Custo total por armazem:\n");
    for(i=0; i<A;i++){
        soma[i] = 0;
        somavalor[i] = 0;
        for(j=0; j<B; j++){
            soma[i] = soma[i] + e[i][j];
        }
        somavalor[i] = soma[i] * vet[i];
        printf("ARMAZEM %d: R$ %.2f\n", i+1, somavalor[i]);
    }
}

void custoTotalProd(int e[A][B], float vet[B]){
    int i, j;
    int soma[B];
    float somavalor[B];
    printf("OPCAO 6 DO MENU:\n");
    printf("Custo total por produto:\n");
    for(i=0; i<B; i++){
        soma[i] = 0;
        somavalor[i] = 0;
        for(j=0; j<A; j++){
            soma[i] = soma[i] + e[j][i];
        }
        somavalor[i] = soma[i] * vet[i];
        printf("PRODUTO %d: R$ %.2f\n", i+1, somavalor[i]);
    }
}

int SoliciteNums(int e[A][B]){
    int i, j, numA, numB, numSubst;
    char resp;
    printf("OPCAO 7 DO MENU: \n");
    printf("Digite o numero do produto e do armazem:\n");
    do{
        scanf("%d %d", &numA, &numB);
    }while(((numA>4)||(numA<0)) && ((numB>5)||(numB<0)));

    for(i=0; i<A; i++){
        for(j=0; j<B; j++){
            if(((i+1) == numA) && ((j+1) == numB)){
                printf("%d e a quantidade atual do produto %d no armazem %d\n", e[i][j], j+1, i+1);
            }
        }
    }
    printf("Deseja alterar a quantidade? (s/n)\n");
    scanf(" %c", &resp);
    if(resp == 's'){
        printf("Digite o novo numero:\n");
        do{
            scanf("%d", &numSubst);
        }while(numSubst < 0);
        e[numA-1][numB-1] = numSubst;
    }
    return e[numA-1][numB-1];
}

int SoliciteProd(int e[A][B], float vet[B]){
    int i, j, numA;
    float numSubst;
    char resp;
    printf("OPCAO 8 DO MENU: \n");
    printf("Digite o numero do produto:\n");
    do{
        scanf("%d", &numA);
    }while((numA>5)||(numA<0));

    for(j=0; j<B; j++){
            if((j+1) == numA){
                printf("%.2f e o valor atual do produto %d\n", vet[j-1], j+1);
            }
        }
        printf("Deseja alterar a quantidade? (s/n)\n");
        scanf(" %c", &resp);
        if(resp == 's'){
        printf("Digite o novo valor:\n");
        do{
            scanf("%f", &numSubst);
        }while(numSubst <= 0.0);
        vet[numA-1] = numSubst;
    }
    return vet[numA-1];
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
    for(i=0; i<B; i++){
        printf("Produto %d:", i+1);
        scanf("%f", &valor[i]);
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
/*
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
*/

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
                    imprimePorProd(estoque);
                    break;
            case 2:
                    imprimePorArmazem(estoque);
                    break;
            case 3:
                    imprimeTotalArmazem(estoque);
                    break;
            case 4:
                    imprimeTotalProduto(estoque);
                    break;
            case 5:
                    custoTotalArmazem(estoque, custo);
                    break;
            case 6:
                    custoTotalProd(estoque, custo);
                    break;
            case 7:
                    SoliciteNums(estoque);
                    break;
            case 8:
                    SoliciteProd(estoque, custo);
                    break;
            case 0:
                    break;
            default:
                    printf("Opcao invalida!\n\n");
        }
    }while(resp != 0);

    return 0;
}
