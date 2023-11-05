#include <stdio.h>

int main(){

    int num_cand, idade, sem_xp, mais_novo;
    char xp;
    sem_xp = 0;
    mais_novo = 1000;
    num_cand=1;
    while(num_cand!=0){

        printf("Digite o num do candidato:\n");
        scanf("%d", &num_cand);
        if(num_cand == 0)
            break;
        printf("Digite a idade:\n");
        scanf("%d", &idade);

        do{
            printf("Tem experiencia?\n");
            scanf(" %c", &xp);
        }while((xp != 's') && (xp != 'n'));

        if((xp == 'n') && (idade>30))
            sem_xp++;
        if(idade<mais_novo && xp =='s')
            mais_novo = idade;

    }

    printf("numero de cand sem xp e >30anos: %d", sem_xp);
    if(mais_novo == 1000){
        printf("Nao ha candidato com experiencia!");
    }else{
        printf("candidato mais novo com experiencia: %d", mais_novo);
    }
    return 0;
}
