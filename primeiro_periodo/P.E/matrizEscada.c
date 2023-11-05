#include <stdio.h>

int main(){
    int L,C, i,j,k,l, zerado, felipe, zarur; //fel - condicional zarur - quant
    zerado = 0;

    scanf("%d %d", &L, &C);
    int mat[L][C];

    for(i=0;i<L;i++){
        for(j=0;j<C;j++){
            scanf("%d", &mat[i][j]);
        }
    }

    for(i=0; i<L; i++){
        for(j=0; j<C; j++){
            if((mat[i][j] != 0)&&(i != L-1)){
                for(k=i+1; k<L; k++){
                    for(l=0; l<=j;l++){
                        if(mat[k][l] != 0){
                            printf("N\n");
                            return 0;
                        }
                    }
                }
                break;
            }
            if(mat[i][j] == 0)
                zerado++;
        }
        if(zerado == C){
            for(k=0; k<C; k++){
                if(mat[i+1][k] != 0){
                    printf("N\n");
                    return 0;
                }
            }
        }
        zerado = 0;
    }

/*
    if(felipe == 1){
        for(i=zarur;i<L;i++){
            for(j=0;j<C;j++){
                if(mat[i][j]!=0){
                    printf("N\n");
                    return 0;
                }
            printf("S\n");
            return 0;
            }
        }
    }

        for(i=0;i<L-1;i++){
            for(j=0;j<C;j++){
                if(mat[i][j]!=0)
                    break;
            }
            for(k=0;k<j;k++){
                if(mat[i+1][k] != 0){
                    printf("N\n");
                    return 0;
                }
            }
        }

        for(i=0; i<L-1; i++){
            for(j=0; j<C; j++){
                if(mat[i][j] == 0){
                    if(mat[i+1][j] != 0){
                        printf("N\n");
                    return 0;
                    }
                    if(mat[i][j+1])
                }


            }
        }
        */

    printf("S\n");
    return 0;
}
