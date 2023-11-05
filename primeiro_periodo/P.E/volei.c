#include <stdio.h>

int main(){
    int N,i;
    char nome[20];
    int s1, s2, b1, b2, a1, a2;
    float saquetotal, bloqueiototal, ataquetotal;
    float saqueconfirmado, bloqueioconfirmado, ataqueconfirmado;
    float media1, media2, media3;
    saquetotal = 0; bloqueiototal = 0; ataquetotal = 0;
    saqueconfirmado = 0; bloqueioconfirmado = 0; ataqueconfirmado = 0;

    scanf("%d", &N);

    for(i=0;i<N;i++){
        scanf("%s", &nome);
        scanf("%d %d %d", &s1, &b1, &a1);
        scanf("%d %d %d", &s2, &b2, &a2);
        saquetotal+=s1;
        bloqueiototal += b1;
        ataquetotal += a1;
        saqueconfirmado += s2;
        ataqueconfirmado += a2;
        bloqueioconfirmado += b2;

    }

    media1 = saqueconfirmado/saquetotal;
    media2 = bloqueioconfirmado/bloqueiototal;
    media3 = ataqueconfirmado/ataquetotal;

    //printf("saquetotal:%f , saqueconfirmado: %f", saquetotal,saqueconfirmado);
    printf("Pontos de Saque: %.2f %", media1 * 100);
    printf("Pontos de Bloqueio: %.2f %", media2 * 100);
    printf("Pontos de Ataque: %.2f %", media3 * 100);

    return 0;

}
