#include <stdio.h>

int main() {

    int S, T, F, H;
    scanf("%d %d %d", &S,&T,&F);

    H = S + T - F;

    if(F >= 0){
        if(H>24 || H==24){
            printf("%d)\n", H - 24);
        }
        else if(H<24){
            printf("%d\n", H);
        }else if(H<0){
            printf("%d\n", 24 + H);
        }
    }else if(F<0){
        if(H<0){
            printf("%d\n", 24+H);
        }else if(H>0){
            printf("%d\n", H);
        }
    }

    return 0;
}
