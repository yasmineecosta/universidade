#include <stdio.h>

int coisa(char a[], char b[]){
    int i, j, cont, quant;
    quant = 1;
    cont = strlen(a);
    b[30];
    b[0] = a[0];
    for(i=1;i!='/0';i++){
        for(j=1; j!='/0';j++){
            if(a[i-1] == a[i]){
                quant++;
            }else{
                b[j] = quant;
                b[j+1] = a[i];
                quant = 1;
            }
        }
    }
    for(i=0;i!='/0'; i++){
        printf("%d %d\n", a[cont+1],b[30]);
    }
    int cont2 = strlen(b);

    if(cont2 < cont){
        return 1;
    }else{
        return 0;
    }

}


int main(){

    char br[30], br1[50];
    scanf("%s", br);
    coisa(br, br1);


}
