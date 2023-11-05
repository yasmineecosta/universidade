#include <stdio.h>
/*prova - digitar as notas(obrigar o usuario a escrever de 0 a 10)
se ele nao quiser desejar nota(perguntar se quer imprimir ou n)


*/
int main(){
    float nota, nota_maior, nota_menor, soma, media, soma_maiores, media_maiores, qtd_7;
    int notas, nota_menor_quant;
    notas = 0;
    soma = 0;
    soma_maiores = 0;
    qtd_7 = 0;
    media = 0;
    char resp;

    nota_maior = 0;
    nota_menor = 10;
    nota_menor_quant = 0;

    do{
        do{
                //digitar as notas
            printf("Digite uma nota de 0 a 10: \n");
            scanf("%f", &nota);
        }while(nota<0 || nota>10);

            notas++;
            soma += nota;

        //qual a maior nota
            if(nota > nota_maior && (nota >=0 && nota <= 10)){
                nota_maior = nota;
            }
            //qual a menor nota
            if(nota < nota_menor && (nota >= 0 && nota <= 10)){
                nota_menor = nota;
            }
            // quantidade de notas <4
            if(nota < 4){
                nota_menor_quant+= 1;
            }

            if(nota >= 7){
                qtd_7++;
                soma_maiores += nota;
            }


        if(nota >= 9){
            printf("Nota Excelente!\n");
        }else if(nota < 7){
            printf("Estude mais!\n");
        }


        do{
            printf("Deseja informar outra nota?(S/N)\n");
            scanf(" %c", &resp);
        }while((resp != 'S') && (resp != 'N'));

        if(resp == 'N'){
            printf("Fim do programa!\n");
        }
    }while(resp == 'S');

        media = soma/notas;
        media_maiores = soma_maiores/qtd_7;

        printf("A maior nota foi: %.2f\nA menor nota foi: %.2f\n", nota_maior, nota_menor);
        printf("Ha %d notas menores que 4\n", nota_menor_quant);
        printf("Media de todas as notas: %.2f\n", media);
        printf("Media das notas maiores ou iguais a 7: %.2f\n",media_maiores);
    return 0;
}
