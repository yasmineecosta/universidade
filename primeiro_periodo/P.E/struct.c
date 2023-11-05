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
	//Observe que o inteiro x do main NAO foi modificado pela função testeInt!
	//Só seria se tivéssemos passado seu endereço.
	testeData(dt);
	printf("No main, dt = %d/%d/%d\n",dt.dia,dt.mes, dt.ano);
	//Observe que o registro dt do main NAO foi modificado pela função testeData!
	//Só seria se tivéssemos passado seu endereço.
	testeVet(vet);
	printf("No main, primeiro elemento do vetor: %d\n",vet[0]);
	//Observe que o vetor do main foi modificado pela função testeVet!
	//Isso porque sempre passamos o nome da matriz para a função e o nome é
	//o endereço inicial da matriz.




   //vet2 = vet; //Com vetor não compila!!!!
	dt2 = dt; //Com registro está correto. dt2 recebe o mesmo valor de dt, ou seja,
	          //os valores dos campos de todo o registro.

	//if (vet2 = vet) //Compila, mas está ERRADO, pois estamos comparando os endereços e não os elementos!
	//	printf("IGUAIS");


	//if (dt2==dt) //ERRO! Não compila!!! Temos que comparar campo a campo.
	//	printf("IGUAIS");

	if(dt2.dia==dt.dia && dt2.mes==dt.mes && dt2.ano==dt.ano) //CORRETO!
		printf("IGUAIS");



    return 0;
}
