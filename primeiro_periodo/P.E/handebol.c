#include <stdio.h>

int main(){
    int i,j,N,M;
    int x = 0;
    int y;

    scanf("%d %d", &N, &M);
    int vet[N][M];

    for(i=0; i<N; i++){
        for(j=0; j<M; j++){
            scanf("%d", &vet[i][j]);
        }
    }

    for(i=0; i<N; i++){
                y = 1;
        for(j=0;j<M;j++){
            printf("%d", vet[i][j]);
            if(vet[i][j] == 0){
                y = 0;
            }
        }
        printf("\n");
            if(y == 1)
                x++;
    }
    printf("%d", x);
    return 0;
}

