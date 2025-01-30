import sympy as sp
import numpy as np

def nova_matriz(colunas):
    matriz = []
    auxj = 0
    while auxj<colunas:
        matriz.append([])
        auxj+=1
    return matriz

def preenche_matriz(matriz, linhas, colunas):
    for i in range (linhas):
        for j in range (colunas):
            while True:
                try:
                    elemento = float(input(f'a{i+1}{j+1} = '))
                    matriz[i].append(elemento)
                    break
                except ValueError:
                    print("Erro! Insira um número válido!")
    return matriz

def adiciona_variavel_matriz(matriz, variavel):
    # Criando uma matriz simbólica a partir da matriz de entrada
    A = sp.Matrix(matriz)
    
    # Subtraindo x apenas dos elementos da diagonal principal
    for i in range(A.shape[0]):
        A[i, i] -= variavel

    return A

def autovetores_autovalor_um(matriz):
    # Converte a matriz para um array NumPy
    matriz_np = np.array(matriz)

    # Calcula os autovetores e autovalores da matriz
    autovalores, autovetores = np.linalg.eig(matriz_np)

    # Encontra os índices dos autovalores iguais a 1
    indices_autovalor_um = np.where(np.isclose(autovalores, 1.0))[0]

    # Seleciona os autovetores correspondentes
    autovetores_autovalor_um = autovetores[:, indices_autovalor_um]

    return autovetores_autovalor_um

def printa_page_rank(matriz, autovetor):
    # Calcula o PageRank
    page_rank = autovetor / np.sum(autovetor)

    # Imprime o PageRank
    for i, valor in enumerate(page_rank):
        print(f'PageRank do nó {i+1}: {valor[0]:.2f}')

print("Voce deseja dar entrada em uma matriz ou utilizar uma matriz predefinida?")
print("1 - Digitar uma matriz")
print("2 - Utilizar uma matriz ja existente")
opcao = int(input("Digite a opcao desejada: "))
print("")

if opcao == 1:
    linhas = int(input("Digite a quantidade de linhas da matriz: "))
    colunas = int(input("Digite a quantidade de colunas da matriz: "))

    if linhas != colunas:
        print("Erro, so e possivel calcular o determinante em matrizes quadradas!")
        exit()
    else:
        matriz = nova_matriz(colunas)
        print("Digite os elementos da matriz")
        matriz = preenche_matriz(matriz, linhas, colunas)
        x = sp.Symbol('x')
        A = adiciona_variavel_matriz(matriz, x)
        print("")
        for i in range(A.shape[0]):
            print(A[i, :])

        print("")
        print("Polinomio caracteristico:")
        print(A.det())
        print("")
        autovalores = sp.solve(A.det(), x)
        print("Autovalores:")
        print(autovalores)
        print("")

        if 1 in autovalores:
            autovetor_1 = autovetores_autovalor_um(matriz)
            print("Autovetor associado ao autovalor 1:")
            print(autovetor_1)
            print("")

            printa_page_rank(matriz, autovetor_1)

elif opcao == 2:
    matriz = [[0.3, 0.7, 0.5],
              [0.4, 0.2, 0.5],
              [0.3, 0.1, 0.0]]
    x = sp.Symbol('x')
    A = adiciona_variavel_matriz(matriz, x)
    for i in range(A.shape[0]):
        print(A[i, :])

    print("")
    print("Polinomio caracteristico:")
    print(A.det())
    print("")
    autovalores = sp.solve(A.det(), x)
    print("Autovalores:")
    print(autovalores)
    print("")

    autovetor_1 = autovetores_autovalor_um(matriz)
    print("Autovetor associado ao autovalor 1:")
    print(autovetor_1)
    print("")

    printa_page_rank(matriz, autovetor_1)