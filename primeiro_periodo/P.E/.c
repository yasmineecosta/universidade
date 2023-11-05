#include <stdio.h>
#define P 4 //colunas - quantidade de produtos
#define A 3  //linhas - quantidade de armazens

void imprimeTotalCadaProduto(int est[][P]){
	int i,j, soma[P];
	printf("Total de cada produto: \n");
	for(i=0; i<P; i++){//para cada produto(coluna)
		soma[i]=0;
	    for(j=0; j<A; j++){
			soma[i] = soma[i] + est[j][i];
		}
		printf("PRODUTO %d: %d\n", i+1, soma[i]);
	}


}

void custoTotalPorProduto(int est[A][P], float custo[P]){
	int i,j;
	int soma;
	printf("Custo total por produto:\n");
	for(i=0; i<P; i++){//coluna
		soma = 0;
		for(j=0; j<A; j++){//linha
			soma = soma + est[j][i];
		}
		printf("PRODUTO %d: R$ %.2f\n", i+1, soma*custo[i]);

	}
}


void lerEstoque(int est[A][P]){
	int i, j;
	printf("Digite o estoque:\n");
	for(i=0; i<A; i++){//linha
		printf("ARMAZEM %d:\n", i+1);
		for(j=0; j<P; j++){//coluna
			printf("Produto %d: ", j+1);
			scanf("%d", &est[i][j]);
		}
	}
}

void lerCusto(float custo[P]){
	int i;
	printf("Digite o custo de cada produto:\n");
	for(i=0; i<P; i++){
		printf("Produto %d: R$ ", i+1);
		scanf("%f", &custo[i]);
	}
}

int menu(){
	int opcao;
	printf("MENU\n1- Estoque por produto\n"
     	  "2- Estoque por armazem\n"
	      "3- Estoque por produto\n"
		  "4- Total de cada produto\n"
		  "5- Custo total por armazem\n"
		  "6- Custo total por produto\n"
		  "7- Alterar quantidade de um produto\n"
		  "8- Alterar custo de um produto\n"
		  "0- Sair\n");
	printf("Digite uma opcao do menu: ");
	scanf("%d", &opcao);
	return opcao;
}
void imprimeProdutos(int prod[]){
	int i;
	for(i=0; i<P; i++){
		printf("Produto %d: %d\n", i+1, prod[i]);
	}
}
void imprime(int estoque[A][P]){
	int i;
	for(i=0; i<A; i++){
		printf("ARMAZEM %d\n", i+1);
		imprimeProdutos(estoque[i]);

	}

}

int main(){

	int estoque[A][P];
	float custo[P];
	int resp; //armazena a escolha do usuário em relação ao menu

	lerEstoque(estoque);

	lerCusto(custo);

	imprime(estoque);

	do{
	    resp = menu();//1 - mostrar o menu
	                  //2 - escolher uma opcao do menu

	    //3 - de acordo com a opção escolhida a ação apropriada ocorre
	   switch(resp){
		  case 1: printf("FALTA IMPLEMENTAR\n\n");
		  	      break;
		  case 2: printf("FALTA IMPLEMENTAR\n\n");
		  	      break;
		  case 3: printf("FALTA IMPLEMENTAR\n\n");
		  	      break;
		  case 4: imprimeTotalCadaProduto(estoque);
		          printf("\n");
		  	      break;
		  case 5: printf("FALTA IMPLEMENTAR\n\n");
		  	      break;
		  case 6: custoTotalPorProduto(estoque, custo);
		  	      break;
		  case 7: printf("FALTA IMPLEMENTAR\n\n");
		  	      break;
		  case 8: printf("FALTA IMPLEMENTAR\n\n");
		  	      break;
		  case 0:
		  	      break;
		  default: printf("Opcao invalida!\n\n");
	   }
	}while (resp!=0);

	return 0;
}

