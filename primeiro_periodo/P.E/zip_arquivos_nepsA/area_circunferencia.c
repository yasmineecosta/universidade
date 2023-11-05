#include <stdio.h>

int main(){
    float R;
    0 <= R <= 1000;

    scanf("%f", &R);
    printf("%.2f", R * R * 3.14);

    return 0;
}
