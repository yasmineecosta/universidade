#include <stdio.h>

int main(){

    int a,b,c;
    scanf("%d %d %d", &a,&b,&c);

    if(a>b){
        if(a>c){
                if(b>c){
                    printf("%d\n%d\n%d\n",c,b,a);
                }else{
                    printf("%d\n%d\n%d\n",b,c,a);
                }
        }else{
            printf("%d\n%d\n%d\n",b,a,c);
        }
    }else if(b>a){
        if(b>c){
                if(a>c){
                    printf("%d\n%d\n%d\n",c,a,b);
                }else{
                    printf("%d\n%d\n%d\n",a,c,b);
                }
        }else{
            printf("%d\n%d\n%d\n", a,b,c);
        }
    }else if(c>b){
            if(c>a){
                if(a>b){
                    printf("%d\n%d\n%d\n",b,a,c);
                }else{
                    printf("%d\n%d\n%d\n",a,b,c);
                }

            }else{
                printf("%d\n%d\n%d\n",b,c,a);
            }
    }
    return 0;

}
