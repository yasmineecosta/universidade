#include <stdio.h>

int main(){
    int candidato_num = 1;
    int idade;
    int candidato_novo = 1000;
    int sem_xp = 0;
    char xp;

    while(candidato_num != 0){
        printf("Digite o numero do candidato:");
        scanf("%d", &candidato_num);

        if(candidato_num == 0)
            break;

        printf("Idade:");
        scanf("%d", &idade);

        do{
            printf("Possui experiencia?");
            scanf(" %c", &xp);
        }while(xp != 's' && xp != 'n');

        if((xp == 'n') && (idade>30))
            sem_xp++;
        if((xp == 's') && (idade<candidato_novo))
            candidato_novo = idade;
    };

        printf("Numero de candidatos >30anos sem experiencia: %d", sem_xp);
        if(candidato_novo != 1000)
        printf("Candidato mais novo possui %d anos", candidato_novo);

    return 0;
}
