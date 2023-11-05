#include <stdio.h>

int main(){
    int L,C, i,j,k, zerado, num, pos, dif, pos2, coisa;
    zerado = 0;
    dif = 0;

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
          //opcao de coluna = 0
        }if(j==C){
            coisa = 1;
            num = i+1;
            break;
        }
        zerado = 0;
    }

    if(coisa == 1){
        for(i=num;i<L;i++){
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

    for(i=0;i<L;i++){
        for(j=0;j<C;j++){
            if(mat[i][j]!=0){
                dif++;
                if((dif != 0) && (mat[i+1][j] != 0)){
                    printf("N\n");
                    return 0;
                }
            }
        }
        if(dif == 0){
            printf("S\n");
            return 0;
        }
    }



    return 0;
}
