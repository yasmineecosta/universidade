import re

def escaneiaVetor():
    n = int(input("Digite o tamanho do vetor: "))

    print(f"Digite os {n} elementos do vetor separados por vírgulas ou espaços:")

    entrada = input()
    elementos = [int(elemento) for elemento in re.split(r'[,\s]+', entrada)]

    if len(elementos) != n:
        print("Número incorreto de elementos. Por favor, insira novamente.")
        return escaneiaVetor(n)

    return elementos

def escaneiaBase(n):
    print(f"Digite os elementos da base, inserindo {n} inteiros por linha:")

    base = []

    for i in range(n):
        print(f"Digite os {n} elementos do vetor {i + 1} separados por vírgulas ou espaços:")
        entrada = input()
        elementos = [int(elemento) for elemento in re.split(r'[,\s]+', entrada)]

        if len(elementos) != n:
            print("Número incorreto de elementos. Por favor, insira novamente.")
            return escaneiaBase(n)

        base.append(elementos)

    return base

def resolve_sistema(matriz):
    # Número de equações (linhas)
    n = len(matriz)

    # Eliminação para transformar a matriz em uma forma triangular superior
    for i in range(n):
        # Pivoteamento parcial (troca de linhas para garantir um pivô não nulo)
        max_index = i
        for k in range(i + 1, n):
            if abs(matriz[k][i]) > abs(matriz[max_index][i]):
                max_index = k
        matriz[i], matriz[max_index] = matriz[max_index], matriz[i]

        # Normalização
        pivot = matriz[i][i]
        for j in range(i, n + 1):
            matriz[i][j] /= pivot

        # Eliminação
        for k in range(i + 1, n):
            factor = matriz[k][i]
            for j in range(i, n + 1):
                matriz[k][j] -= factor * matriz[i][j]

    # Substituição retroativa para encontrar as soluções
    solucoes = [0] * n
    for i in range(n - 1, -1, -1):
        solucao = matriz[i][n]
        for j in range(i + 1, n):
            solucao -= matriz[i][j] * solucoes[j]
        solucoes[i] = solucao

    return solucoes

def criaMatriz(vet, base):
    matriz = []

    for i in range(len(vet)):
        linha = []
        for j in range(len(vet)):
            linha.append(base[j][i])
        linha.append(vet[i])
        matriz.append(linha)

    return matriz

def produtoEscalar(v1, v2):
    return sum(x * y for x, y in zip(v1, v2))

def GranSchmidt(base):
    u = []
    for i in range(len(base)):
        u.append(base[i])

    for i in range(1, len(base)):
        for j in range(i):
            projection = produtoEscalar(u[i], u[j]) / produtoEscalar(u[j], u[j])
            u[i] = [u[i][k] - projection * u[j][k] for k in range(len(u[i]))]

    for i in range(len(u)):
        magnitude = sum(x**2 for x in u[i])**0.5
        u[i] = [x / magnitude for x in u[i]]

    return u

vet = escaneiaVetor()
base = escaneiaBase(len(vet))
matriz = criaMatriz(vet, base)
resolve_sistema(matriz)
print("Coordenadas do vetor na nova base:", resolve_sistema(matriz))
print("Base ortonormalizada:", GranSchmidt(base))