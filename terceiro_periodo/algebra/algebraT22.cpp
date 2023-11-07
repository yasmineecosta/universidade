#include <bits/stdc++.h>
#include <iostream>
#include <math.h>
#define MAXN 100
using namespace std;

int determinante(int matriz[MAXN][MAXN], int n) {
  int det = 0;
  int submatriz[MAXN][MAXN];
  if (n == 1)
    return matriz[0][0];
  if (n == 2)
    return ((matriz[0][0] * matriz[1][1]) - (matriz[1][0] * matriz[0][1]));
  else {
    for (int i = 0; i < n; i++) {
      int subI = 0;
      for (int j = 1; j < n; j++) {
        int subJ = 0;
        for (int k = 0; k < n; k++) {
          if (k == i)
            continue;
          submatriz[subI][subJ] = matriz[j][k];
          subJ++;
        }
        subI++;
      }
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

  // if(N == 1){
  //     det = matriz[0][0];
  // }else{
  //     det = laplace(matriz, N);
  //     cout << "Determinante = " << det << endl;
  // }

  cout << "Determinante desta porra é = " << determinante(matriz, n) << endl;
  return 0;
}