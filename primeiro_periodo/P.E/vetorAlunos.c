#include <stdio.h>
#define TAM 4
/*
struct aluno{
   double peso;
   double altura;
   int ano;	
};

typedef struct aluno tAluno;
*/
/*
typedef struct aluno{
   double peso;
   double altura;
   int ano;	
} tAluno;
*/

typedef struct{
   double peso;
   double altura;
   int ano;	
} tAluno;

int main(){
	tAluno alu[TAM];
	int i;
	
	for(i = 0; i<TAM; i++){
		printf("ALUNO %d\n", i+1);
	    printf("Digite a altura: ");
	    scanf("%lf", &alu[i].altura);
	    printf("Digite o peso: ");
	    scanf("%lf", &alu[i].peso);
	    printf("Digite o ano de nascimento: ");
	    scanf("%d", &alu[i].ano);	    
	}
	
	for(i = 0; i<TAM; i++){
	    printf("Aluno %d: peso %.1lf altura %.1lf ano %d\n",
	    i+1, alu[i].peso, alu[i].altura, alu[i].ano);
	}
	return 0;
}