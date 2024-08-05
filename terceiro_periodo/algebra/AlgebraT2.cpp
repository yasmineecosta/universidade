#include <bits/stdc++.h>
#include <iostream>
#include <math.h>
#define MAXN 100
using namespace std;

// Função para determinar a determinante de uma matriz quadrada
int determinante(int matriz[MAXN][MAXN], int n) {
  int det = 0;
  int submatriz[MAXN][MAXN];

  // Matriz quadrada de ordem 1
  if (n == 1)
    return matriz[0][0];

  // Matriz quadrada de ordem 2, usando o algoritmo padrão
  if (n == 2)
    return ((matriz[0][0] * matriz[1][1]) - (matriz[1][0] * matriz[0][1]));

  // Matriz quadrada de ordem 3 ou maior, usando laplace
  else {
    for (int i = 0; i < n; i++) {
      int subI = 0; // Linha da submatriz
      for (int j = 1; j < n; j++) {
        int subJ = 0; // Coluna da submatriz
        for (int k = 0; k < n; k++) {
          if (k == i) // Ignora o elemento quando i = k
            continue;
          submatriz[subI][subJ] = matriz[j][k]; // Preenche a submatriz
          subJ++; // acresce a coluna da submatriz
        }
        subI++; // acresce a linha da submatriz
      }
      // Calculando o determinante tirando a primeira linha
      det = det + pow(-1, i) * matriz[0][i] * determinante(submatriz, n - 1); 
    }
  }

  return det;
}

int main() {
  int n, i, j, matriz[MAXN][MAXN];

  cout << "Digite o valor N para a matriz quadrada: ";
  cin >> n;

  cout << "Digite os valores da matriz: " << endl;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      cin >> matriz[i][j];
    }
  }

  cout << "A determinante é = " << determinante(matriz, n) << endl;
  return 0;
}