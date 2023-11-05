#include <stdio.h>
#define P 5
#define TAM 4
/*
typedef struct{
	char mat[22];
	float nota1;
	float nota2;
	float nota3;
	float nota4;
	float nota5;
}tAluno;
*/
typedef struct{
	char mat[22];
	float nota[P];
}tAluno;

int main(){
	tAluno alu[TAM];
	int i, j;
	
	for(i=0; i<TAM; i++){
		printf("ALUNO %d\n", i+1);
		printf("Digite a matricula: ");
		scanf("%s", alu[i].mat);
		printf("Digite as notas:\n");
		for(j=0; j<P; j++){
			printf("NOTA %d\n", j+1);
			scanf("%f", &alu[i].nota[j]);
		}
		
	}
	
	for(i=0; i<TAM; i++){
		printf("ALUNO %d\n", i+1);
		printf("Matricula: %s\n", alu[i].mat);
		for(j=0; j<P; j++){
			printf("NOTA %d: %.1f\n", j+1, alu[i].nota[j]);
		}		
	}	
	
	return 0;
}
