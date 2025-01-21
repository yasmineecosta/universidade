import numpy as np
import sympy as sp
from sympy import symbols, Eq, solve, simplify
from sympy.logic.boolalg import BooleanTrue
from copy import deepcopy


def Mprint(matriz):
  for linha in matriz:
    print(' '.join(map(str, linha)))


# Função para determinar a determinante de uma matriz quadrada
def determinante(matriz, n):
  # n = len(matriz)
  det = 0

  # Matriz quadrada de ordem 1
  if n == 1:
    return matriz[0][0]

  # Matriz quadrada de ordem 2, usando o algoritmo padrão
  if n == 2:
    return matriz[0][0] * matriz[1][1] - matriz[1][0] * matriz[0][1]

  # Matriz quadrada de ordem 3 ou maior, usando laplace
  else:
    for i in range(n):
      submatriz = [[0 for _ in range(n - 1)] for _ in range(n - 1)]
      subI = 0
      for j in range(1, n):
        subJ = 0
        for k in range(n):
          if (k == i):
            continue
          submatriz[subI][subJ] = matriz[j][k]
          subJ += 1
        subI += 1

      det = det + (-1)**i * matriz[0][i] * determinante(submatriz, n - 1)

  return det


def obtem_m_adj(matriz):
  matriz_adjacencia = np.where(matriz != 0, 1, 0)
  return matriz_adjacencia


def calculaAutovalor(matriz, n):
  y = symbols('y')
  for i in range(len(matriz)):
    matriz[i][i] = matriz[i][i] - y
  Mprint(matriz)
  autovalores = solve(Eq(determinante(matriz, n), 0))
  print(f"autovalores = {autovalores}\n")
  return autovalores


def calculaAutovetor(matriz, autovalores, n):
  nVar = len(matriz)
  list_Var = symbols('x0:%d' % nVar)
  list_Var_lambida = []
  eq_Formadas = []
  eq = []
  exp = 0  #expressão
  print()
  for i in range(nVar):
    exp = 0
    for j in range(nVar):
      exp = exp + (matriz[i][j] * list_Var[j])
    eq.append(exp)

  for k in range(len(autovalores)):
    print(f"autovetor nº{k} para o autovalor = {autovalores[k]}")

    for i in range(len(list_Var)):
      list_Var_lambida.append(list_Var[i] * autovalores[k])
    print(f"Equacoes: {eq}")
    print(f"Equacoes de Autovalores: {list_Var_lambida}")

    for i in range(len(eq)):
      equacao = Eq(eq[i], list_Var_lambida[i])
      eq_Formadas.append(equacao)

    print(f"Equacoes formadas: {eq_Formadas}")
    tuple_list_Var = tuple(list_Var)
    result = solve(eq_Formadas, tuple_list_Var, dict=True)

    print("Autovetor:")
    for l in result:
      valores = [l[var] if var in l else var for var in list_Var]
      print(tuple(valores))
    print("")
    # polinomioCaract(matriz)
    if 1 in autovalores:
      for linha in matriz:
        print(' '.join(map(str, linha)))
      print("")
      
    matriz_adjac = obtem_m_adj(matriz)
    # pageRank = calculaPageRank(matriz, n)
    # print(pageRank)
    list_Var_lambida.clear()
    eq_Formadas.clear()


def calculaPageRank(matriz, n, d=0.85, epsilon=1e-5):
  matriz_adjac = obtem_m_adj(matriz)

  #Inicializa o vetor de probabilidade de páginas visitadas
  prob_page = np.ones(n) / n

  #Itera até a convergência
  while True:
    # Calcula o vetor de probabilidade de página atualizado
    prob_page_att = np.dot(matriz_adjac, prob_page)

    # Aplica o fator de atenuação
    prob_page_att *= d

    # Adiciona o componente residual
    prob_page_att += (1 - d) / n

    # Calcula a norma do vetor de probabilidade de página atualizado
    norma = np.linalg.norm(prob_page_att - prob_page)

    # Se a convergência foi alcançada, retorna o vetor de probabilidade de página atualizado
    if norma < epsilon:
      return prob_page_att

    # Atualiza o vetor de probabilidade de página
    prob_page = prob_page_att


def add_var_m(matriz, var):
  A = sp.Matrix(matriz)
  for i in range(A.shape[0]):
    A[i, i] -= var
  return A


def polinomioCaract(matriz):
  x = sp.Symbol('x')
  A = add_var_m(matriz, x)
  print("")
  for i in range(A.shape[0]):
    print(A[i, :])
  print("Polinomio caracteristico:")
  print(A.det())


def autovet_autoval_Um(matriz):
  matriz_np = np.array(matriz)
  autovalores, autovetores = np.linalg.eig(matriz_np)
  indice_autoval_um = np.where(np.isclose(autovalores, 1.0))[0]

  # Seleciona os autovetores correspondentes
  autovet_autoval_um = autovetores[:, indice_autoval_um]

  return autovet_autoval_um


def insereMatriz_e_Det(n):
  print("Digite os valores da matriz: ")
  matriz = []
  for _ in range(n):
    # linha = list(map(float, input().split()))
    linha = list(map(int, input().split()))
    matriz.append(linha)

  print("A determinante é =", determinante(matriz, n))
  return matriz


def main():
  n = int(input("Digite o valor N para a matriz quadrada: "))
  matriz = insereMatriz_e_Det(n)
  print(matriz)
  for linha in matriz:
    print(' '.join(map(str, linha)))
  print("")

  matriz_op = deepcopy(matriz)
  matriz_A = matriz
  polinomioCaract(matriz_A)
  print("")
  pageRank = calculaPageRank(matriz, n)
  # print("PageRank:")
  # for l in pageRank:
  #   print(l)
    
  autovalores = calculaAutovetor(matriz, calculaAutovalor(matriz_op, n), n)
main()
