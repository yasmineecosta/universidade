#include <iostream>
#include <vector>
#include <cmath>
#include <Eigen/Dense>
#include <bits/stdc++.h>
using namespace std;

// Funções auxiliares
void printaMatriz(const vector<vector<double>>& matriz) {
    for (const auto& linha : matriz) {
        for (double elem : linha) {
            cout << elem << " ";
        }
        cout << endl;
    }
}

vector<vector<double>> calcular_inversa(const vector<vector<double>>& matriz) {
    Eigen::MatrixXd matriz_eigen(matriz.size(), matriz[0].size());
    for(int i = 0; i < matriz.size(); i++) {
        for(int j = 0; j < matriz[0].size(); j++) {
            matriz_eigen(i, j) = matriz[i][j];
        }
    }
    Eigen::MatrixXd inversa_eigen = matriz_eigen.inverse();

    vector<vector<double>> inversa(matriz.size(), vector<double>(matriz[0].size()));
    for(int i=0; i<matriz.size(); i++) {
        for(int j=0; j<matriz[0].size(); j++) {
            inversa[i][j] = inversa_eigen(i, j);
        }
    }
    return inversa;
}

vector<vector<double>> transform_vet_em_col(const vector<double>& vetor) {
    vector<vector<double>> matriz_coluna;
    // Implemente a transformação do vetor em matriz coluna aqui
    return matriz_coluna;
}

vector<vector<double>> mat_transposta(const vector<vector<double>>& mat) {
    vector<vector<double>> transposta;
    // Implemente a transposição da matriz aqui
    return transposta;
}

vector<vector<double>> concatenar_base(const vector<vector<double>>& vetores) {
    vector<vector<double>> nova_matriz;
    // Implemente a concatenação da base aqui
    return nova_matriz;
}

vector<vector<double>> transform_col_em_vet(const vector<vector<double>>& coluna) {
    vector<vector<double>> vetor;
    // Implemente a transformação da coluna em vetor aqui
    return vetor;
}

vector<vector<double>> vetores_para_matriz(const vector<vector<double>>& vetores) {
    vector<vector<double>> matriz;
    // Implemente a criação da matriz a partir dos vetores aqui
    return matriz;
}

double produto_interno(const vector<double>& vetor1, const vector<double>& vetor2) {
    if (vetor1.size() != vetor2.size()) {
        cerr << "Os vetores devem ter o mesmo comprimento." << endl;
        return 0.0;
    }
    double prodint = 0.0;
    // Implemente o cálculo do produto interno aqui
    return prodint;
}

double norma(const vector<double>& vetor) {
    double norma = 0.0;
    // Implemente o cálculo da norma aqui
    return norma;
}

vector<vector<double>> nova_base(const vector<vector<double>>& vetores) {
    vector<vector<double>> w;
    // Implemente o cálculo da nova base aqui
    return w;
}

int main() {
    vector<vector<double>> base;
    vector<vector<double>> matriz;
    vector<double> vetor;

    cout << "Entre com um vetor: ";
    // Implemente a leitura do vetor aqui

    cout << "Digite a nova base:" << endl;
    // Implemente a leitura da nova base aqui

    vector<vector<double>> matrizcoluna = transform_vet_em_col(vetor);

    int dimensao_vetor = vetor.size();

    matriz = vetores_para_matriz(base);

    vector<vector<double>> matriz_inversa = calcular_inversa(matriz);

    vector<vector<double>> vetor_resultante = transform_col_em_vet(matriz_inversa * matrizcoluna);

    cout << "Coordenadas do Vetor na nova base: " << endl;
    printaMatriz(vetor_resultante);

    vector<vector<double>> base_ortonormal = nova_base(base);

    cout << "Base ortonormalizada: " << endl;
    printaMatriz(base_ortonormal);

    cout << "Vetor na Base ortornormalizada: " << endl;
    vetor_resultante = transform_col_em_vet(base_ortonormal * matrizcoluna);
    
    printaMatriz(vetor_resultante);

    return 0;
}