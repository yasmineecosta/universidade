#include <stdio.h>
#define TAM 4


struct endereco{
     char rua[100];
	 char cep[9];
	 int num;	
};

struct aluno{
   double peso;
   double altura;
   int ano;	
   struct endereco end;
};


int main(){
	struct aluno alu[TAM];
	int i;

	
	for(i = 0; i<TAM; i++){
		printf("ALUNO %d\n", i+1);
	    printf("Digite a altura: ");
	    scanf("%lf", &alu[i].altura);
	    printf("Digite o peso: ");
	    scanf("%lf", &alu[i].peso);
	    printf("Digite o ano de nascimento: ");
	    scanf("%d", &alu[i].ano);
	    printf("Digite seu cep: ");
	    scanf("%s", alu[i].end.cep);
		printf("Digite o numero: ");
		scanf("%d", &alu[i].end.num);	    
	}
	
	for(i = 0; i<TAM; i++){
	    printf("Aluno %d: peso %.1lf altura %.1lf ano %d\n",
	            i+1, alu[i].peso, alu[i].altura, alu[i].ano);
	    printf("CEP: %s num: %d\n", alu[i].end.cep, alu[i].end.num);
	    
	}
	return 0;
}