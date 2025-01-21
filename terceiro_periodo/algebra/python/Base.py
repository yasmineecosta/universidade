from matplotlib import pyplot as plt
import numpy as np

def printaMatriz(matriz):
  for linha in matriz:
    print(' '.join(map(str, linha)))

def calcular_inversa(matriz):
    inversa = np.linalg.inv(matriz)
    return inversa

def transform_vet_em_col(vetor):
    return np.array(vetor).astype(float).reshape(-1, 1)

def mat_transposta(mat):
    return np.transpose(mat)

def concatenar_base(*vetores):
    nova_matriz = np.concatenate(vetores, axis = 1)
    return nova_matriz

def transform_col_em_vet(coluna):
    return np.array(coluna).reshape(1,-1)

def vetores_para_matriz(*vetores):
    return np.column_stack(vetores)

def produto_interno(vetor1, vetor2): #Calcula o produto interno entre dois vetores
    if len(vetor1) != len(vetor2):
        print("Os vetores devem ter o mesmo comprimento.")
        return None
    prodint = 0
    for i in range(len(vetor1)):
        vetor1[i] = float(vetor1[i])
        vetor2[i] = float(vetor2[i])
        prodint += vetor1[i] * vetor2[i]
    return prodint

def norma(vetor):
    return np.linalg.norm(vetor)

def nova_base(*vetores):
    w = []
    for i in range(len(vetores)):
        if i == 0:
            w.append(vetores[i] / norma(vetores[i]))
        else:
            w.append(vetores[i])
            for j in range(i):
                w[i] = w[i] - produto_interno(w[j], vetores[i]) * w[j]
            w[i] = w[i] / norma(w[i])
   
    return w

def plotar_graficos(vetor, base, base_ortonormal):
    if len(vetor) == 2:
        fig, axs = plt.subplots(1, 2, figsize=(12, 6))

        axs[0].quiver(0, 0, vetor[0], vetor[1], angles='xy', scale_units='xy', scale=1, color='r', label='Vetor Original')
        for i, vetor_base in enumerate(base):
            axs[0].quiver(0, 0, vetor_base[0], vetor_base[1], angles='xy', scale_units='xy', scale=1, color='b', alpha=0.5)

        axs[0].set_xlim(-norma(vetor)-1, norma(vetor)+1)
        axs[0].set_ylim(-norma(vetor)-1, norma(vetor)+1)
        axs[0].axhline(0, color='black', linewidth=0.5)
        axs[0].axvline(0, color='black', linewidth=0.5)
        axs[0].grid(color='gray', linestyle='--', linewidth=0.5)
        axs[0].legend(loc='upper left')
        axs[0].set_title('Gráfico com Base do Usuário')
        axs[0].set_xlabel('X')
        axs[0].set_ylabel('Y')

        axs[1].quiver(0, 0, vetor[0], vetor[1], angles='xy', scale_units='xy', scale=1, color='r', label='Vetor Original')
        for i, vetor_base_ortonormal in enumerate(base_ortonormal):
            axs[1].quiver(0, 0, vetor_base_ortonormal[0], vetor_base_ortonormal[1], angles='xy', scale_units='xy', scale=1, color='g', alpha=0.5)

        axs[1].set_xlim(-norma(vetor)-1, norma(vetor)+1)
        axs[1].set_ylim(-norma(vetor)-1, norma(vetor)+1)
        axs[1].axhline(0, color='black', linewidth=0.5)
        axs[1].axvline(0, color='black', linewidth=0.5)
        axs[1].grid(color='gray', linestyle='--', linewidth=0.5)
        axs[1].legend(loc='upper left')
        axs[1].set_title('Gráfico com Base Ortonormal')
        axs[1].set_xlabel('X')
        axs[1].set_ylabel('Y')

        plt.tight_layout()
        plt.show()


base = []
matriz = []

print("Entre com um vetor")
vetor = (input(""))
vetor = vetor.split(',')
matrizcoluna = transform_vet_em_col(vetor) #transforma o vetor em uma matriz coluna para futura multiplicação

dimensão_vetor = len(vetor)

print("Digite a nova base")
for i in range(dimensão_vetor):
    print(f"{i+1}° vetor:")
    base.append(input(""))
    base[i] = base[i].split(',')
    base[i] = np.array(base[i]).astype(float)

matriz = vetores_para_matriz(*base)

matriz_inversa = calcular_inversa(matriz)

vetor_resultante = np.dot(matriz_inversa, matrizcoluna)
vetor_resultante = transform_col_em_vet(vetor_resultante)

print("Coordenadas do Vetor na nova base: ")
printaMatriz(vetor_resultante)

base_ortonormal = nova_base(*base)
base_ortonormal = mat_transposta(base_ortonormal)

print("Base ortonormalizada: ")
printaMatriz(base_ortonormal)
print("Vetor na Base ortornormalizada: ")

vetor_resultante = np.dot(base_ortonormal, matrizcoluna) #Calculo do vetor na base ortonormal
vetor_resultante = transform_col_em_vet(vetor_resultante)

printaMatriz(vetor_resultante)

plotar_graficos(transform_vet_em_col(vetor), base, base_ortonormal) #Plotar grafico caso vetor pertença a R²