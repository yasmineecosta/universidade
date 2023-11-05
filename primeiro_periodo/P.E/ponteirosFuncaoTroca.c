#include <stdio.h>
void troca2(int *p1, int *p2){
	int num1, num2;
	int aux;
	
	num1 = *p1;
	num2 = *p2;
	
	aux = num1;
	num1 = num2;
	num2 =aux;
	
	*p1 = num1;
	*p2 = num2;
	
}

void troca1(int *p1, int *p2){
	int aux;
	aux = *p1;
	*p1 = *p2;
	*p2 =aux;
}


int main(){
	int x,y;
	printf("Digite dois numeros: ");
	scanf("%d%d", &x, &y);
    //troca1(&x, &y); // Está correto também!
    troca2(&x, &y);
	printf("x = %d e y = %d\n", x, y);
	return 0;
}