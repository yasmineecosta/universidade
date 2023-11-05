#include <stdio.h>
int main(){
    int alta, baixa, num, result;

    for(num>1000; num<9999; num++){
        alta = num/100;
        baixa = num%100;
        result = (alta + baixa)*(alta+baixa);
        if(result == num)
            printf("%d\n", num);
    }

    return 0;
}
