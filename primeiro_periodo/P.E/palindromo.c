#include <stdio.h>
#include <string.h>

int ehPalindromo(char v[]){
    int i,j,k,p;
    k = strlen(v);
    for(i=0,j=k-1;i<j;i++,j--){
        if(v[i] == v[j])
            p=1;
        else{
            p=0;
            break;
        }
    }

    return p;
}

int main(){

    char palavra[20];
    int resp;
    scanf("%s", palavra);

    resp = ehPalindromo(palavra);

    if(resp == 1)
        printf("eh palindromo\n");
    else
        printf("nao palindromo\n");
    return 0;
}
