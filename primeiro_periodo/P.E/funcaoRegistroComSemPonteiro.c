#include <stdio.h>
typedef struct{
	int dia;
	int mes;
	int ano;
}tData;

void imprimeData(tData dt){
	printf("%d/%d/%d\n",dt.dia,dt.mes, dt.ano); 
	
}

tData leData(){
    tData dt;
    printf("Digite dia, mes e ano separados por espaco:");
	scanf("%d%d%d", &dt.dia, &dt.mes, &dt.ano); 
	return dt;	
}

void leData2(tData *p){
	tData dt;
    printf("Digite dia, mes e ano separados por espaco:");
	scanf("%d%d%d", &dt.dia, &dt.mes, &dt.ano); 
	*p = dt;	
}

void leData3(tData *p){
    printf("Digite dia, mes e ano separados por espaco:");
	scanf("%d%d%d", &(*p).dia, &p->mes, &p->ano);
		
}

int main(){
	tData dt={2,12,1999};
//	dt = leData();
    leData3(&dt);
	imprimeData(dt);

    return 0;	
}