#include <stdio.h>
int A;
void func1(){
    int B;
    B = 100 + A;
    A = 2*A;
    printf("B: %d e A: %d", B,A);
}

int main(){

    int B;
    A = 5;
    B = 10;
    func1();
}
