#include <stdio.h>

int main(){

    float n1,n2,n3,n4, n_exame;
    float media, media_final;
    scanf("%f %f %f %f", &n1,&n2,&n3,&n4);
    media = ((n1*2)+(n2*3)+(n3*4)+(n4*1))/10;
    printf("Media: %.1f\n",media);

    if(media>=7){
        printf("Aluno aprovado.\n");
    }else if(media<5){
        printf("Aluno reprovado.\n");
    }else{
        printf("Aluno em exame.\n");
        scanf("%f", &n_exame);
        printf("Nota do exame: %.1f\n", n_exame);
        media_final = (media + n_exame)/2;

        if(media_final>=5.0){
            printf("Aluno aprovado.\n");
        }else{
            printf("Aluno reprovado.\n");
        }

        printf("Media final: %.1f\n", media_final);
    }

    return 0;

}
