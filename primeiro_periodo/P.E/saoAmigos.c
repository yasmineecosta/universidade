#include <stdio.h>

//Obriga o usuário digitar um número não negativo e retorna esse número
int leNaoNegativo(){  
	int num;
	do{
		printf("Digite um numero nao negativo: ");
		scanf("%d", &num); 
	}while(num<0);
	return num;
}

//Retorna a soma dos divisores próprios de um numero passado por parâmetro
int somaDivisores(int num){ 
    int soma=0,i;
    for(i=1; i<num; i++){  //poderia ir até um valor menor, como por exemplo i<=num/2
		if (num % i == 0)
			soma = soma + i;
	}
	return soma;
}

//Verifica se dois números, passados por parâmetros, são amigos. 
//Retorna 1 se são amigos e 0, caso contrário.
int saoAmigos(int num1, int num2){
    if (somaDivisores(num1) == num2 && somaDivisores(num2)==num1)
    	return 1;
    return 0;
}
int main(){
	int num1, num2;
	while (1){
		printf("Digite dois numeros positivos para saber se sao amigos ou 0 para finalizar\n");
		num1 = leNaoNegativo();
		if (num1 == 0) 
			break;
		num2 = leNaoNegativo();
		if (num2 == 0) 
			break;		
		if (saoAmigos(num1, num2)==1){
			printf("SAO AMIGOS\n");
		}else
			printf("NAO SAO AMIGOS\n");
	}
	return 0;
}