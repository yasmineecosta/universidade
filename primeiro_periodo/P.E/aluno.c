#include <stdio.h>

struct aluno{
   double peso;
   double altura;
   int ano;	
};



int main(){
	struct aluno alu, alu2;
		
	alu.peso = 55.5;
	printf("Digite a altura: ");
	scanf("%lf", &alu.altura);
	alu.ano = 2000;	
	
	printf("Aluno: peso %.1lf altura %.1lf ano %d\n",
	        alu.peso, alu.altura, alu.ano);
	return 0;
}