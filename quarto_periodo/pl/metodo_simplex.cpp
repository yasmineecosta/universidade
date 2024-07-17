#include <bits/stdc++.h>
using namespace std;

int qtdX, qtdFuncoesLimitantes;
int totalLinhas, totalColunas;
int colunaPivo;
double variavel_entrada = 1000;
double coluna_variavel_entrada;
double tabela[10][10];
double menorPivo = 1000, elementoPivo;
int linhaPivo;
double novaLinhaPivo[10];
int variaveisBasicas[10], contBasicas;
int variaveisNaoBasicas[10], contNaoBasicas;
double funcaoObjetivo[10];

void buscarVariavelEntrada() {
    variavel_entrada = 1000;
    colunaPivo = 0;

    cout << "\n\nProcurando Variavel Que Entra: \n";

    for (int j = 0; j < totalColunas - 1; j++) {
        if (tabela[totalLinhas - 1][j] < variavel_entrada) {
            variavel_entrada = tabela[totalLinhas - 1][j];
            colunaPivo = j;
        }
    }

    cout << "Assim temos que a Variavel que Entra eh " << variavel_entrada << "\n";
}

void buscarLinhaPivo() {
    menorPivo = 1000;
    linhaPivo = 0;
    elementoPivo = 0;

    cout << "\nObtendo Linha Pivo: \n";

    for (int i = 0; i < totalLinhas - 1; i++) {
        if (tabela[i][colunaPivo] > 0) {
            coluna_variavel_entrada = tabela[i][totalColunas - 1] / tabela[i][colunaPivo];
            if (coluna_variavel_entrada < menorPivo) {
                menorPivo = coluna_variavel_entrada;
                linhaPivo = i;
            }
        }
    }
    elementoPivo = tabela[linhaPivo][colunaPivo];
    cout << "Linha Pivo: " << linhaPivo + 1 << "\n";
    cout << "Elemento Pivo: " << elementoPivo << "\n";
}

void calcularNovasLinhas() {
    cout << "\nCalculando novas Linhas: \n";

    for (int aux = 0; aux < totalLinhas; aux++) {
        if (aux != linhaPivo) {
            if (aux == totalLinhas - 1) {
                cout << "\nNova Linha Z: \n";
            } else {
                cout << "\nNova " << aux + 1 << " º Linha: \n";
            }
            double representanteInverso = tabela[aux][colunaPivo] * -1;
            for (int i = 0; i < totalColunas; i++) {
                tabela[aux][i] += tabela[linhaPivo][i] * representanteInverso;
                cout << tabela[aux][i] << " ";
            }
            cout << "\n";
        }
    }
}

void calcularNovaLinhaPivo() {
    cout << "\nCalculando Nova Linha Pivo: \n\n";

    cout << "Nova Linha Pivo: \n";
    for (int i = 0; i < totalColunas; i++) {
        tabela[linhaPivo][i] = tabela[linhaPivo][i] / elementoPivo;
        cout << tabela[linhaPivo][i] << " ";
    }
    cout << "\n";

    calcularNovasLinhas();
}

void iniciarMetodoSimplex() {
    buscarVariavelEntrada();
    buscarLinhaPivo();
    calcularNovaLinhaPivo();

    cout << "\n\nFormato da tabela POS METODO: \n";
    for (int i = 0; i < totalLinhas; i++) {
        cout << "\n";
        for (int j = 0; j < totalColunas; j++) {
            cout << tabela[i][j] << " ";
        }
    }

    cout << "\n\n";
    cout << "\n--------------------------------------------------------------------------------\n";
}

bool verificarTabela() {
    cout << "Verificando se a solucao eh otimo ou nao: ";

    for (int i = 0; i < totalColunas - 1; i++) {
        if (tabela[totalLinhas - 1][i] < 0) {
            cout << "Solucao nao eh otima\n";
            return false;
        }
    }
    cout << "Solucao eh otima\n";

    return true;
}

void buscarVariaveisBasicas_naoBasicas() {
    double aux = 0;

    contBasicas = 0;
    contNaoBasicas = 0;

    for (int i = 0; i < totalColunas - 1; i++) {
        for (int j = 0; j < totalLinhas; j++) {
            aux += tabela[j][i];
        }
        if (aux == 1 && tabela[totalLinhas - 1][i] == 0) {
            variaveisBasicas[contBasicas] = i;
            contBasicas++;
        } else {
            variaveisNaoBasicas[contNaoBasicas] = i;
            contNaoBasicas++;
        }
        aux = 0;
    }
}

void calcularVariaveisBasicas_NaoBasicas() {
    cout << "\nCalculando Resposta Final e Variaveis Basicas e Nao Basicas: \n";

    cout << "Variaveis Basicas: \n";

    for (int i = 0; i < contBasicas; i++) {
        if (variaveisBasicas[i] < qtdX) {
            double valorResp = 0;
            for (int j = 0; j < totalLinhas; j++) {
                if (tabela[j][variaveisBasicas[i]] == 1) {
                    valorResp = tabela[j][totalColunas - 1];
                    break;
                }
            }
            cout << "X" << variaveisBasicas[i] + 1 << " = " << valorResp << "\n";
        } else {
            double valorResp = 0;
            for (int j = 0; j < totalLinhas; j++) {
                if (tabela[j][variaveisBasicas[i]] == 1) {
                    valorResp = tabela[j][totalColunas - 1];
                    break;
                }
            }
            cout << "s" << variaveisBasicas[i] - qtdX + 1 << " = " << valorResp << "\n";
        }
    }

    cout << "\n\nVariaveis Nao Basicas: \n";
    double zero = 0;
    for (int i = 0; i < contNaoBasicas; i++) {
        if (variaveisNaoBasicas[i] < qtdX) {
            cout << "X" << variaveisNaoBasicas[i] + 1 << " = " << zero << "\n";
        } else {
            cout << "s" << variaveisNaoBasicas[i] - qtdX + 1 << " = " << zero << "\n";
        }
    }
}

double calcularZ() {
    double Z = 0;
    for (int i = 0; i < contBasicas; i++) {
        double valorResp = 0;
        for (int j = 0; j < totalLinhas; j++) {
            if (tabela[j][variaveisBasicas[i]] == 1) {
                valorResp = tabela[j][totalColunas - 1];
                break;
            }
        }
        Z += funcaoObjetivo[variaveisBasicas[i]] * valorResp;
    }
    return Z;
}

int main() {
    cout << "Quantas funcoes limitantes? ";
    cin >> qtdFuncoesLimitantes;
    cout << "Quantos X existem? ";
    cin >> qtdX;
    totalColunas = qtdX + qtdFuncoesLimitantes + 1;
    totalLinhas = qtdFuncoesLimitantes + 1;

    cout << "Informe os valores da tabela inicial formada linha a linha: \n";
    for (int i = 0; i < totalLinhas; i++) {
        for (int j = 0; j < totalColunas; j++) {
            cin >> tabela[i][j];
        }
    }

    // Copiando a última linha para a função objetivo
    for (int i = 0; i < totalColunas - 1; i++) {
        funcaoObjetivo[i] = tabela[totalLinhas - 1][i];
    }

    cout << "\n--------------------------------------------------------------------------------\n";
    cout << "\n\nFormato da primeira tabela: \n";
    for (int i = 0; i < totalLinhas; i++) {
        cout << "\n";
        for (int j = 0; j < totalColunas; j++) {
            cout << tabela[i][j] << " ";
        }
    }

    do {
        cout << "\n#####################################################################################\n";

        iniciarMetodoSimplex();

    } while (!verificarTabela());

    buscarVariaveisBasicas_naoBasicas();
    calcularVariaveisBasicas_NaoBasicas();

    cout << "\n\nCalculando Z: \n";

    double respostaFinal = calcularZ();

    cout << "Valor de Z (LUCRO MAXIMO OU GASTO MINIMO): " << respostaFinal << "\n";

    return 0;
}
