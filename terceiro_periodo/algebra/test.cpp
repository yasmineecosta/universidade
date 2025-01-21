#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <tuple>
#include <algorithm>
#include <functional>
#define MAXN 100
using namespace std;

typedef map<string, complex<double>> Symbol;
typedef vector<vector<complex<double>>> Matrix;
typedef vector<complex<double>> Vector;

void Mprint(int matriz[MAXN][MAXN], int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << matriz[i][j] << " ";
    }
    cout << endl;
  }
}

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

int insereMatriz(int matriz[MAXN][MAXN], int n) {
  cout << "Digite os valores da matriz: " << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> matriz[i][j];
    }
  }
  return matriz[MAXN][MAXN];
}

// int calculaAutovalor(int matriz[MAXN][MAXN], int n) {
//   long long lambda;
//   for (int i = 0; i < n; i++) {
//     matriz[i][i] = matriz[i][i] - lambda;
//   }
//   Mprint();
//   autovalor = determinante(matriz, n);
//   return autovalor;
// }
Vector<complex<double>> calculaAutovalor(Matrix matriz, int n) {
  Vector<complex<double>> autovalores;
  complex<double> lambda;

  for (int i = 0; i < n; i++) {
    matriz[i][i] -= lambda;
  }

  // Calcula o polinômio característico
  complex<double> charPoly = determinante(matriz, n);

  // Resolve o polinômio característico
  auto roots = roots(charPoly);

  for (auto root : roots) {
    autovalores.push_back(root.imag() != 0 ? polar(root.real(), arg(root)) : root);
  }

  return autovalores;
}

// int calculaAutovetor(int matriz[MAXN][MAXN], int n) {
//   return autovetor;
// }

Matrix calculaAutovetor(Matrix matriz, Vector<complex<double>> autovalores) {
  Matrix autovetores;

  for (auto autovalor : autovalores) {
    Matrix submatriz(matriz);
    Vector<complex<double>> sublista_variaveis_lambida(nVariaveis);
    Vector<complex<double>> subequacoes(nVariaveis);
    Symbol sublista_variaveis;

    // Substitute the eigenvalue into the diagonal
    for (int i = 0; i < nVariaveis; i++) {
      submatriz[i][i] -= autovalor;
    }

    // Create the system of linear equations
    for (int i = 0; i < nVariaveis; i++) {
      auto it = sublista_variaveis.insert({"x" + to_string(i), 1});
      sublista_variaveis_lambida[i] = autovalor * it->second;
      subequacoes[i] = 0;
      for (int j = 0; j < nVariaveis; j++) {
        subequacoes[i] += submatriz[i][j] * it->second;
      }
      subequacoes[i] -= sublista_variaveis_lambida[i];
    }
  // Solve the system of linear equations using Gaussian elimination
    for (int i = 0; i < nVariaveis - 1; i++) {
      for (int j = i + 1; j < nVariaveis; j++) {
        double ratio = submatriz[j][i] / submatriz[i][i];
        for (int k = i; k < nVariaveis; k++) {
          submatriz[j][k] -= ratio * submatriz[i][k];
        }
        for (int k = i; k < nVariaveis; k++) {
          subequacoes[j][k] -= ratio * subequacoes[i][k];
        }
      }
    }

    // Back-substitution to find the eigenvectors
    Vector<complex<double>> eigenvector(nVariaveis);
    for (int i = nVariaveis - 1; i >= 0; i--) {
      eigenvector[i] = subequacoes[i][nVariaveis];
      for (int j = i + 1; j < nVariaveis; j++) {
        eigenvector[i] -= submatriz[i][j] * eigenvector[j];
      }
      eigenvector[i] /= submatriz[i][i];
    }

    autovetores.push_back(eigenvector);
  }

  return autovetores;
}


int main() {
  int n, i, j, matriz[MAXN][MAXN];

  cout << "Digite o valor N para a matriz quadrada: ";
  cin >> n;

  matriz[MAXN][MAXN] = insereMatriz(matriz, n);
  Mprint(matriz, n);
  m_copy[MAXN][MAXN] = matriz[MAXN][MAXN];
  autovetores = calculaAutovetor(matriz, calculaAutovalor(m_copy));
  // int det = determinante(matriz, n);
  return 0;
}


void Mprint(int matriz[MAXN][MAXN], int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << matriz[i][j] << " ";
    }
    cout << endl;
  }
}

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

int insereMatriz(int matriz[MAXN][MAXN], int n) {
  cout << "Digite os valores da matriz: " << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> matriz[i][j];
    }
  }
  return matriz[MAXN][MAXN];
}
