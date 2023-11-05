#include <stdio.h>
#include <string.h>


int main(){
    char palavra1[30], palavra2[30];
    int i, j;
    scanf("%s", palavra1);
    scanf("%s", palavra2);
    if(strcmp(palavra1, palavra2) == 0){
        printf("sao anagramas\n");
    }else if(strlen(palavra1) == strlen(palavra2)){
        for(i = 0;palavra1[i] != '\0';i++){

        }
        char palavra3[i+1];
       for( i = 0 ; palavra1[i] != '\0' ; i++ ){
           for( j = 0 ; palavra2[j] != '\0' ; j++ ){
               if(palavra1[i] == palavra2[j]){
                   palavra3[j] = palavra1[i];
                   break;
               }
           }
       }
       palavra3[i] = '\0';
       if(strcmp(palavra2, palavra3) == 0){
           printf("sao anagramas\n");
       }else{
           printf("nao sao anagramas\n");
       }
    }else{
        printf("nao sao anagramas\n");
    }
    return 0;
}
