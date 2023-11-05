#include <stdio.h>
int compacta(char cadeiaOriginal[], char cadeiaGerada[]){
	int i;//posição do caracter corrente(que estamos analisando)
	      //da cadeia original 
	int cont; //contar a quantidade de caracteres iguais em sequencia		  
	int j = 0; //1ª posição livre da cadeiaGerada	
	i=0;
	while (cadeiaOriginal[i] != '\0'){
		cont=1;
		while (cadeiaOriginal[i] == cadeiaOriginal[i+1]){
			cont++;
			i++;
		}
		cadeiaGerada[j] = cadeiaOriginal[i];
		j++;
		
		cadeiaGerada[j] = cont + 48;
		j++;
		i++;
	}
	cadeiaGerada[j] = '\0';  
	if (j<i) 
		return 1;
	return 0; 	
}
int main(){
	char palavra[100];
	char nova[100];
	printf("Digite a palavra: ");
	scanf("%s", palavra);
	if (compacta(palavra, nova)==1)
		printf("Palavra compactada com sucesso: %s\n", nova);
	else
        printf("Palavra nao compactada: %s\n", nova);
	return 0;
}