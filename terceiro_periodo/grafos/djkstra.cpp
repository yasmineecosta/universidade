// Grupo 1
// Djkstra
#include <bits/stdc++.h>
#define optimize ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'
#define MAXN 1000
#define INTMAX 10000000000
#define pii pair<int, int> 
#define delta 0.0000001
#define ALL(x) x.begin(), x.end()
#define ll long long

using namespace std;

//declara o vetor que possui pares associados(um grafo)
vector<pii> grafos[MAXN];

vector<int> Djkstra(int origem)
{
    vector<bool> visitados(MAXN, false); // vetor de visitados inicializado com false
    vector<int> distancia(MAXN, INTMAX); // vetor de distância inicializado com infinito

    priority_queue<pii, vector<pii>, greater<pii>> fila;
    
    // primeiro valor é o custo pra chegar no vértice
    // segundo valor é o vértice destino
    fila.push({0, origem});
    distancia[origem] = 0;

    while(!fila.empty())    //enquanto ainda tiver vértices na fila
    {
        pii topo = fila.top();  //pega o topo da fila
        fila.pop(); // remove o topo da fila
        int custo = topo.first, vertice = topo.second;  //custo e vértice são o primeiro e segundo valor do topo

        // Não é necessário mas acelera o processo de verificação
        if (visitados[vertice]) continue;

        visitados[vertice] = true;

        for (auto vizinho : grafos[vertice]) //auto -- tipo de dado que irá se referir a variáveis presentes em um vetor(grafos)
        {
            int cust = vizinho.second, vertc = vizinho.first; //??

            if (!visitados[vertc]) //se o vértice não foi visitado ainda
            {
                // Verifica se o custo do caminho todo + custo pra eu ir pro vizinho é menor que o custo atual no vector
                if (custo + cust < distancia[vertc])
                {
                    fila.push({custo + cust, vertc});
                    distancia[vertc] = custo + cust;
                }
            }
        }
    }

    return distancia;
}

int main()
{
    grafos[0].push_back({1, 2});
    grafos[0].push_back({2, 6});
    grafos[1].push_back({0, 2});
    grafos[1].push_back({3, 5});
    grafos[2].push_back({0, 6});
    grafos[2].push_back({3, 8});
    grafos[3].push_back({1, 5});
    grafos[3].push_back({2, 8});
    grafos[3].push_back({5, 15});
    grafos[3].push_back({4, 10});
    grafos[4].push_back({3, 10});
    grafos[4].push_back({5, 6});
    grafos[4].push_back({6, 2});
    grafos[5].push_back({3, 15});
    grafos[5].push_back({4, 6});
    grafos[5].push_back({6, 6});
    grafos[6].push_back({5, 6});
    grafos[6].push_back({4, 2});

    int valor;
    cout << "Valor: ";
    cin >> valor;

    vector<int> distancias = Djkstra(valor);

    for (int i = 0; i <= 6; i++) cout << "Valor para " << i << ": " << distancias[i] << endl;

    return 0;
}