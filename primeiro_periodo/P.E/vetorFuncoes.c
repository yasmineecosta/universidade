#include<stdio.h>
#define MAX 6
void preenche(int vet[]){
	int i;
	for(i=0;i<MAX;i++){
		printf("Numero %d: ", i+1);
		scanf("%d", &vet[i]);
	}
}
void imprime(int vet[MAX]){ //pode declarar o parâmetro como int vet[MAX] ou int vet[]
	int i;
	for(i=0; i<MAX; i++){
		printf("%d\n", vet[i]);
	}
}
int main(){
    int num1[MAX];
    int num2[MAX];

    printf("Digite %d numeros do conjunto 1:\n", MAX);
    preenche(num1);
    printf("Digite %d numeros do conjunto 2:\n", MAX);
    preenche(num2);
    printf("Conjunto 1:\n");
    imprime(num1);
    printf("Conjunto 2:\n");
    imprime(num2);    
	return 0;
}