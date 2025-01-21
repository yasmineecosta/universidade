import numpy as np

def iniVetor():
  print("Digite o vetor que deseja transformar:")
  vetor = input("").split(',')
  return vetor


def Mprint(matriz):
  for linha in matriz:
    print(' '.join(map(str, linha)))


def vet_to_col(vetor):
  return np.array(vetor, dtype=float).reshape(-1, 1)


def mat_transposta(mat):
  return mat.transpose()


def concatenar_base(*vetores):
  return np.concatenate(vetores, axis=1)


def col_to_vet(coluna):
  return coluna.reshape(1, -1)


def vet_to_mat(*vetores):
  return np.column_stack(vetores)


def produto_interno(vetor1, vetor2):
  return np.dot(vetor1, vetor2)


def norma(vetor):
  return np.linalg.norm(vetor)


def new_base(*vetores):
  new_base = []
  for i, vetor in enumerate(vetores):
    vetor = np.array(vetor, dtype=float)
    if i == 0:
      new_base.append(vetor / norma(vetor))
    else:
      new_base.append(vetor)
      for j in range(i):
        new_base[i] = new_base[i] - produto_interno(new_base[j], vetor) * new_base[j]
      new_base[i] = new_base[i] / norma(new_base[i])
  return new_base


def main():
  base = []
  matriz = []

  vetor = iniVetor()    # inicializando o vetor
  m_col = vet_to_col(vetor)     # transformando o vetor em coluna

  print("Digite a nova base:")
  for i in range(len(vetor)):
    print(f"{i+1}° vetor:")
    novo_vetor = input("").split(',')
    novo_vetor = [float(x) for x in novo_vetor]     # convertendo para float
    base.append(novo_vetor)     # adicionando o vetor na base
    
  
  matriz = vet_to_mat(*base)    
  m_inversa = np.linalg.inv(matriz)    # calculando a inversa da matriz

  vet_result = np.dot(m_inversa, m_col)     # calculando o produto da inversa da matriz pelo vetor
  vet_result = col_to_vet(vet_result)   # transformando o vetor em coluna
  print("\n")
  print("Coordenadas do Vetor na nova base: ")
  Mprint(vet_result)

  base_ortonormal = new_base(*base)
  base_ortonormal = np.transpose(base_ortonormal) # transposta
  print("\n")
  print("Base ortonormalizada: ")
  Mprint(base_ortonormal)
  print("\n")

  print("Vetor na base ortonormalizada: ")
  vet_result = np.dot(base_ortonormal, m_col)
  vet_result = col_to_vet(vet_result)
  Mprint(vet_result)


main()
