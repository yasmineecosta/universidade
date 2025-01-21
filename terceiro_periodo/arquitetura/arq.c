#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000 // Defina o valor de N conforme necessário

int main() {
    int dados[N];
    int indice = 1;

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Acessa os dados de forma dispersa e irregular na memória
    dados[indice * rand()] = rand();

    dados[indice * rand()] = rand();

    dados[indice * rand()] = rand();

    dados[indice * rand()] = rand();

    dados[indice * rand()] = rand();


    return 0;
}