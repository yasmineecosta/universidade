#include <stdio.h>
typedef struct{
	int dia;
	int mes;
	int ano;
}tData;

void testeData(tData dt){
	dt.dia = 25;
	printf("Em testeData, dt = %d/%d/%d\n",dt.dia,dt.mes, dt.ano);

}
void testeInt(int x){
	x = 100;
	printf("Em testeInt,  x = %d\n",x);

}
void testeVet(int v[3]){
	v[0]=100;
	printf("Em testeVet, primeiro elemento do vetor: %d\n",v[0]);

}
int main(){
	tData dt={2,12,1999};
	int x=10;
	int vet[3]={1,2,3};
	tData dt2;
	//int vet2[3];
	testeInt(x);
	printf("No main, x = %d\n", x);
	//Observe que o inteiro x do main NAO foi modificado pela fun��o testeInt!
	//S� seria se tiv�ssemos passado seu endere�o.
	testeData(dt);
	printf("No main, dt = %d/%d/%d\n",dt.dia,dt.mes, dt.ano);
	//Observe que o registro dt do main NAO foi modificado pela fun��o testeData!
	//S� seria se tiv�ssemos passado seu endere�o.
	testeVet(vet);
	printf("No main, primeiro elemento do vetor: %d\n",vet[0]);
	//Observe que o vetor do main foi modificado pela fun��o testeVet!
	//Isso porque sempre passamos o nome da matriz para a fun��o e o nome �
	//o endere�o inicial da matriz.




   //vet2 = vet; //Com vetor n�o compila!!!!
	dt2 = dt; //Com registro est� correto. dt2 recebe o mesmo valor de dt, ou seja,
	          //os valores dos campos de todo o registro.

	//if (vet2 = vet) //Compila, mas est� ERRADO, pois estamos comparando os endere�os e n�o os elementos!
	//	printf("IGUAIS");


	//if (dt2==dt) //ERRO! N�o compila!!! Temos que comparar campo a campo.
	//	printf("IGUAIS");

	if(dt2.dia==dt.dia && dt2.mes==dt.mes && dt2.ano==dt.ano) //CORRETO!
		printf("IGUAIS");



    return 0;
}
