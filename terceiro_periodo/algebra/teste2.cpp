#include <bits/stdc++.h>
#define MAXN 101
 
using namespace std;
 
int N;
int matriz[MAXN][MAXN];
bool visitados[MAXN];
 
void coloca()
{
    for (int i = 0; i < MAXN; i++)
    {
        visitados[i] = false;
    }
}
 
int laplace(int n, int coluna) 
{
    int m[n + 1][n + 1], k = 1;
    visitados[coluna] = true;
 
    for (int i = N - n + 1; i <= N; i++) 
    {
        int cont = 1;
 
        for (int j = 1; j <= N; j++)
        {
            if (cont > n) break;
            if (!visitados[j]) 
            {
                m[k][cont] = matriz[i][j];
                cont++;
            }
        }
 
        k++;
    }
 
    if (n == 2)
    {
        visitados[coluna] = false;
        return ((m[1][1] * m[2][2]) - (m[1][2] * m[2][1]));
    }
 
    int soma = 0;
 
    for (int i = 1; i <= n; i++) soma += m[1][i] * (pow(-1, 1 + i) * laplace(n - 1, N - n + i));
    visitados[coluna] = false;
 
    return soma;
}
 
int main() 
{
    coloca();
    cout << "Digite o valor N para a matriz: ";
    cin >> N;
 
    cout << "Digite os valores da matriz: " << endl;
 
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
        cin >> matriz[i][j];
 
    int valor;
    if (N == 1) {
        valor = matriz[1][1];
    } else {
        valor = laplace(N, 0);
    }
    // int valor = laplace(N, 0);
 
    cout << "Determinante: " << valor << endl;
 
    return 0;
}