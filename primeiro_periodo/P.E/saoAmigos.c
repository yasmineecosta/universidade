#include <stdio.h>

//Obriga o usu�rio digitar um n�mero n�o negativo e retorna esse n�mero
int leNaoNegativo(){  
	int num;
	do{
		printf("Digite um numero nao negativo: ");
		scanf("%d", &num); 
	}while(num<0);
	return num;
}

//Retorna a soma dos divisores pr�prios de um numero passado por par�metro
int somaDivisores(int num){ 
    int soma=0,i;
    for(i=1; i<num; i++){  //poderia ir at� um valor menor, como por exemplo i<=num/2
		if (num % i == 0)
			soma = soma + i;
	}
	return soma;
}

//Verifica se dois n�meros, passados por par�metros, s�o amigos. 
//Retorna 1 se s�o amigos e 0, caso contr�rio.
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