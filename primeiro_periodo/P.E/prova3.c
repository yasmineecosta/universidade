#include <stdio.h>
int A;
void func1(){
    int B;
    B = 100+A;
    A = 2*A;
    printf("6 - B: %d e A: %d\n", B,A);
}
void func2(int B){
    int A = 2;
    B = 200+A;
    printf("7 - B: %d e A: %d\n", B,A);
}
int func3(int B){
    B = B*A;
    printf("8 - B: %d e A: %d\n", B,A);
    return B;
}
void func4(int *B){
    *B = *B + A;
    printf("9 - B: %d e A: %d\n", B,A);
}

int main(){
    int B;
    A = 5;
    B = 10;
    printf("1 - B: %d e A: %d\n", B,A);
    B = 20;
    func1();
    printf("2 - B: %d e A: %d\n", B,A);
    B = 30;
    func2(B);
    printf("3 - B: %d e A: %d\n", B,A);
    B = 40;
    B = func3(B);
    printf("4 - B: %d e A: %d\n", B,A);
    B = 50;
    func4(&B);
    printf("5 - B: %d e A: %d\n", B,A);

    return 0;
}
