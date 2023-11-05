#include <stdio.h>

int main(){
    int L,C, i,j,k, zerado, pos, pos2;
    zerado = 0;

    scanf("%d %d", &L, &C);
    int mat[L][C];

    for(i=0;i<L;i++){
        for(j=0;j<C;j++){
            scanf("%d", &mat[i][j]);
        }
    }

    for(j=0;j<C;j++){
        if(mat[0][j]!=0){
            pos = j;
            break;
        }else{
            pos = 0;
        }
    }

    for(i=1, j=0; j<C; i++, j++){
        if(mat[i][j] != 0){
            pos2 = j;
            if(pos >= pos2){
                printf("N\n");
                return 0;
            }
        }else{
            pos2 = 0;
        }
        pos = pos2;

    }
    if(pos < pos2){
        printf("S\n");
        return 0;
    }

    for(i=0;i<L;i++){
        for(j=0;j<C;j++){
            if(mat[i][j]==0)
                zerado++;
        }
        if(zerado == C){
            for(k=0;k<C;k++){
                if(mat[i+1][k] != 0){
                    printf("N\n");
                    return 0;
                }
            }
        }
        zerado = 0;
    }


    return 0;
}

