#include <stdio.h>

int main(){
    float a,b,c,d,e,f;
    int cont = 0;
    scanf("%f %f %f %f %f %f",&a,&b,&c,&d,&e,&f);

    if(a>0)
        cont++;
    if(b>0)
        cont++;
    if(c>0)
        cont++;
    if(d>0)
        cont++;
    if(e>0)
        cont++;
    if(f>0)
        cont++;

    printf("%d valores positivos\n", cont);

    return 0;

}
