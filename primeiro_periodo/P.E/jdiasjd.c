#include <stdio.h>

typedef struct{
    int matricula;
    float nota1;
    float nota2;
}tAluno;

tAluno insereDados(tAluno alu){
    scanf("%d", &alu.matricula);
    scanf("%f", &alu.nota1);
    scanf("%f", &alu.nota2);

    return alu;
}
/*
void insereDados(tAluno *alu){
    scanf("%d", &(*alu).matricula);
    scanf("%f", &(*alu).nota1);
    scanf("%f", &(*alu).nota2);

}
*/
int main(){
    tAluno aluno;
    //aluno = insereDados(aluno);
   aluno = insereDados(aluno);
    printf("%d %f %f", aluno.matricula, aluno.nota1,  aluno.nota2);
}

