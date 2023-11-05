#include <stdio.h>
#include <string.h>
int main(){
	int num[5]; //armazena 5 numeros inteiros
	char placa[8]; //armazena 8 caracteres: 7 da placa + 1 para o '/0' (delimitador da cadeia)
    int num2[5]={10,20,30,40,50};
    char placa2[8]="LVL2020";
    
	int i;

	//Ler 5 numeros e, em seguida, imprimir esses numeros
	printf("01)Digite 5 numeros:\n");
	for(i = 0; i < 5; i++){
		scanf("%d", &num[i]);
	}
	printf("02)Numeros digitados:\n");
	for(i = 0; i < 5; i++){
		printf("%d ", num[i]);
	}
	printf("\n");
//--------------------------------------------------------------	
    //Ler a placa(7 caracteres) e, em seguida, imprimi-la
	printf("03)Digite a placa: ");
	for (i = 0; i < 7; i++){
		scanf(" %c", &placa[i]);
	}
	placa[7] = '\0';

    printf("04)Placa informada: ");
	for (i = 0; placa[i] != '\0'; i++){
		printf("%c", placa[i]);
	}
	printf("\n");

//--------------------------------------------------------------	
	//Ler a placa(7 caracteres) e, em seguida, imprimi-la
	printf("05)Digite a placa: ");
	scanf("%s", placa);
	printf("06)Placa informada: %s\n", placa);
	
//--------------------------------------------------------------
   
    //Atribuir valores constantes aos elementos de um vetor
    
	//num2 = {15,21,3,40,5}; //NAO COMPILA
	//placa2 = "PIZ3131"; //NAO COMPILA
	
	printf("07)Valores iniciais de num2: ");
	for(i = 0; i < 5; i++){
		printf("%d ", num2[i]);
	}
	printf("\n");		
	num2[0] = 15;
	num2[1] = 21;
	num2[3] = 40;
	num2[4] = 5;
	printf("08)Valores atribuidos aos elementos de num2: ");
	for(i = 0; i < 5; i++){
		printf("%d ", num2[i]);
	}
	printf("\n");
	
	printf("09)Valor inicial de placa2: %s\n", placa2);	
	placa2[0] = 'P';
	placa2[1] = 'I';
	placa2[2] = 'Z';
	placa2[3] = '3';
	placa2[4] = '1';
	placa2[5] = '3'; 
	placa2[6] = '1';
	placa2[7] = '\0';
	printf("10)Placa2: %s\n", placa2);	
	
   //outra forma para cadeia de caracteres: função strcpy	
	strcpy(placa2, "LXY5151");
    printf("11)Placa2: %s\n", placa2);
	   
//--------------------------------------------------------------    
    
	//Copiar os elementos de um vetor no outro:
    
    //num1 = num2 //NAO COMPILA
    //placa1 = placa2; //NAO COMPILA
    
    //copia dos numeros
   	for(i=0; i<5; i++){
        num[i] = num2[i];
	}
	 
	printf("12)Elementos copiados em num: "); 
	for(i = 0; i < 5; i++){
		printf("%d ", num[i]);
	}
	printf("\n");
	
	//copia da placa	 
	for(i=0; i<8; i++){
        placa[i] = placa2[i];
	}
    printf("13)Elementos copiados em placa: %s\n", placa);
    
    //outra forma para vetor de caracteres: novamente a função strcpy
    strcpy(placa, placa2);
    printf("14)Elementos copiados em placa: %s\n", placa);

//--------------------------------------------------------------  		 

    //Verificar se duas cadeias de caracteres são iguais:
    
	printf("15)%s e %s sao ", placa, placa2);    
	if (strcmp(placa, placa2) == 0){
		printf("IGUAIS\n");
	}else
		printf("DIFERENTES\n");
	
	printf("16)%s e LVZ4135 sao ", placa);		
	if (strcmp(placa, "LVZ4135") == 0){
		printf("IGUAIS\n");
	}else
		printf("DIFERENTES\n");
						
   //Obter o tamanho de uma cadeia de caracteres em um vetor.		
   i = strlen(placa);
   printf("17)Quantidade de caracteres da placa %d\n", i);
		
	return 0;
}
