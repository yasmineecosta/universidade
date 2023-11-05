#include <stdio.h>

int main(){

    int dist_perc;
    float gasosa_L;
    float consumo;

    scanf("%d %f", &dist_perc, &gasosa_L);

    consumo = dist_perc /gasosa_L;

    printf("%.3f km/l\n", consumo);
    return 0;

}
