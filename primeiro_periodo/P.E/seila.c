#include <stdio.h>
#define TAM 5

typedef struct{
    char nome[80];
    char email[80];
}Pessoa;

typedef struct{
    int quant;
    Pessoa pessoas[100];
}Conjunto;

int menu(){
    int resp;
    printf("1 - Cadastrar\n");
    printf("2 - Localizar\n");
    printf("0 - Sair\n");
    scanf("%d", &resp);

    return resp;
}

int cadastra(Pessoa *p){

}


int main(){
    Conjunto conj;
    conj.quant = 0;
    Pessoa p;
}
