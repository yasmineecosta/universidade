//Escrever um código que o usuário entre com uma matriz quadrada nxn e 
// o código retorne o determinante da matriz usando o desenvolvimento de Laplace.
#include <bits/stdc++.h>
#define optimize ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'
#define MAXN 10100
#define INTMAX 10000000000
#define pii pair<int, int> 
#define delta 0.0000001
#define ALL(x) x.begin(), x.end()
#define ll long long
 
using namespace std;
int n;
vector<vector<double>> matriz;
vector<vector<double>> a;
vector<vector<double>> aux;


double matriz_Laplace(vector<vector<double>>& matriz, int l, int c){
    int n = matriz.size();
    vector<int> sum_line(n, 0), sum_column(n, 0);
    // vector<vector<double>> aux(n-1, vector<double>(n-1));
    l = 0, c=0;
    int temp_col = -1, temp_line = -1;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(matriz[i][j] == 0){
                sum_line[i]++;
                sum_column[j]++;
            }
        }
    }
    
    for(int i=0; i<n; i++){
        if(sum_line[i] > l && sum_line[i] > temp_line){
            l = i;
            temp_line = sum_line[i];

        }
        if(sum_column[i] > c){
            c = i;
        }
    }
    int linha_aux = 0, coluna_aux = 0;

    for(int i=0; i<n; i++){
        if(i == l) continue;
        for(int j=0; j<n; j++){
            if(j == c) continue;
        aux[linha_aux][coluna_aux] = matriz[i][j];
        coluna_aux++;
        }
        linha_aux++;
    }
    return aux[n-1][n-1];
}

double detLaplace(int n, vector<vector<double>>& matriz){
    vector<vector<double>> a(n-1,vector<double>(n-1));
    int l, c;
    a = aux;
    if(n == 1){
        //Caso base: matriz 1x1
        return a[0][0];
    }else{
        double det = 0;
        // a = aux;
        int i, j, col, j_aux, i_aux;
        
        //Escolhe a primeira linha para calcular os cofatores
        for(i = 0; i < n; i++){
            //ignora os zeros (zero vezes qualquer número é igual zero)
            if (a[0][i] != 0) {
                vector<vector<double>> aux(n-1, vector<double>(n-1));
                i_aux = 0;
                j_aux = 0;
                //Gera as matrizes para calcular os cofatores
                for(j = 1; j < n; j++){
                    for(col = 0; col < n; col++){
                        if(col != i){
                            aux[i_aux][j_aux] = a[j][col];
                            j_aux++;
                        }
                    }
                    i_aux++;
                    j_aux = 0;
                }
                double f = (i % 2 == 0)? a[0][i] : -a[0][i];
                det = det + f * detLaplace(n - 1, aux);
            }
        }
        return det;
    }
}

// double determinante(vector<vector<double>>& matriz){
//     int n = matriz.size();
//     int det = 0;
//     int linha, coluna;
//     if(n == 1) return matriz[0][0];
//     vector<vector<double>> aux(n-1, vector<double>(n-1));
//     aux = matriz_Laplace(matriz, linha, coluna);
    
//     //tirar a linha e a coluna
//     int aux[n-1][n-1];
    
//     //lendo a nova matriz auxiliar
//     for(int i = 0; i < n-1; i++){
//         for(int j=1; j<n-1; j++){

//         }
//         // for(int j = 1; j < n; j++){
//         //     for(int k = 0; k < n; k++){
//         //         if(k < i) aux[j-1][k] = matriz[j][k];
//         //         else if(k > i) aux[j-1][k-1] = matriz[j][k];
//         //     }
//         // }
//         // if(i % 2 == 0) det += matriz[0][i] * determinante(aux, n-1);
//         // else det -= matriz[0][i] * determinante(aux, n-1);
//     }
//     return det;
// }
 
int main(){
    // Tamanho da matriz
    int n;
    cout << "Digite qual o valor de n: " << endl;
    cin >> n;
    // int zero_line, zero_column;
    vector<vector<double>> A(n, vector<double>(n));

    // seta_valores(A[n][n]);
    cout << "Digite os valores da matriz:\n";
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
             cin >> A[i][j];
        }
    }
    // vector<vector<double>> matriz_aux = criar_aux(A, zero_line, zero_column);
    // tira_zero(A, zero_line, zero_column);

    double det = detLaplace(n, A);

    cout << "O determinante da matriz é: " << det << endl;
 
    cout << "Fim :)\n";
    
    return 0;
}



// int n; 
// void seta_valores(int matriz[n][n]){
//     cout << "Digite os valores da matriz:\n";
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < n; j++)
//         {
//             cin >> matriz[i][j];
//         }
//     }
// }

// double criar_aux(vector<vector<double>>& matriz, int l, int c){
//     int n = matriz.size();
//     vector<vector<double>> matriz_aux(n-1, vector<double>(n));

//     return matriz[n][n];
// }
