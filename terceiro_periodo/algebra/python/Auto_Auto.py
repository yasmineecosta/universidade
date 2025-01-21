import numpy as np
from sympy import symbols, Eq, solve, simplify
from sympy.logic.boolalg import BooleanTrue
from copy import deepcopy

def printaMatriz(matriz):
  for linha in matriz:
    print(' '.join(map(str, linha)))

#1    
def definirMatriz():
  dimensão = -1
  while(dimensão <= 0):
    print("Digite a Ordem da matriz quadrada (Se não for quadrada, não possui determinante)")
    try:
      dimensão = int(input(""))
    except:
      print("algo deu errado. tente novamente")
      continue
    if(dimensão <= 0):
      print("A dimensão da matriz deve ser maior que 0")
  matriz = []
  for i in range(dimensão):
    while True:
        entrada = input(f"Digite os {dimensão} elementos da {i + 1}ª linha, separados por espaço:\n")
        elementos = entrada.split()
        if(len(elementos) == dimensão):
          linha = [int(x) for x in elementos]
          matriz.append(linha)
          break
        else:
          print("Número de elementos inválido\n A matriz deve ser quadrada")
  print("")
  print(f"matriz:{matriz}")
  for linha in matriz:
    print(' '.join(map(str, linha)))
  print("\n")
  return matriz

def calcularDeterminante(matriz):
  ordem = int(len(matriz))
  determinante = 0
  if(ordem == 1):
    determinante = matriz[0][0]
  elif(ordem == 2):
    determinante = ((matriz[0][0] * matriz[1][1]) - (matriz[0][1] * matriz[1][0]))
  elif(ordem == 3):
    determinante = (matriz[0][0] * matriz[1][1] * matriz[2][2]) + (matriz[0][1] * matriz[1][2] * matriz[2][0]) + (matriz[0][2] * matriz[1][0] * matriz[2][1]) - (matriz[0][2] * matriz[1][1] * matriz[2][0]) - (matriz[0][0] * matriz[1][2] * matriz[2][1]) - (matriz[0][1] * matriz[1][0] * matriz[2][2])

  return determinante

def formulaDeterminante(matriz): 
  resultados = []
  nova_matriz = [linha[:] for linha in matriz] # copiando a matriz original e colando nessa outra lista
  calculoFinal = 0
  linha_excluida=[]
  ordem = int(len(matriz))
  posicao = 0

  if ordem > 3:
    print("\n")
    linha_excluida = matriz[0] #(a11,a12,a13,a14)
    nova_matriz.pop(0) # linha excluida (a11,a12,a13,a14)
    printaMatriz(nova_matriz)
    print("\n")
    ordem1 = int(len(matriz))
    iterador = 1
    for j in range(ordem1):
      nova_matriz = [linha[:] for linha in matriz] # voltando pro estado anterior
      linha_excluida = matriz[0] #(a11,a12,a13,a14)
      nova_matriz.pop(0) # linha excluida (a11,a12,a13,a14)
      ordem1 = int(len(nova_matriz))
      for i in range(ordem1): #excluindo os elementos abaixo do elemento em "j"
        #agora devemos excluir a coluna abaixo de cada elemento (a11,a12,a13,a14)
        nova_matriz[i].pop(j) # iterando em todas as linhas(listas) e excluindo a coluna J ( ex: se for [1,2,3,4], [1,2,3,4] . será excluido todos os '1' uns)
      printaMatriz(nova_matriz)

      #neste ponto, teremos a matriz sem a linha escolhida e sem a coluna na iteracao que "j" estiver

      ordem = int(len(nova_matriz))
      calculo = 0
      posicao = 1 + iterador
      if ordem < 4: # se o ordem for menor que 4, ja temos as formulas para ordem 3,2,1

            calculo = np.power(-1,posicao) * calcularDeterminante(nova_matriz) # aplicando a formula de determinante
            print(f"-1^({posicao}) * {calcularDeterminante(nova_matriz)}")
            resultados.append(calculo) # adicionando o resultado do cofator A1J a lista  
            iterador = iterador+1
            posicao = 0
      elif ordem >= 4: # se o ordem for maior que 4, teremos que aplicar novamente a formula de determinante
            resultadoDeterminanteAux = formulaDeterminante(nova_matriz)
            calculo = np.power(-1,posicao) * resultadoDeterminanteAux#aqui eh o resultado do det da matriz reduzidaa
            resultados.append(calculo) # adicionando o resultado do cofator
            iterador = iterador+1
            posicao =0
      print(f"cofator = {calculo}\n")
    # no fim da iteracao do primeiro laço, ja teremos todos os cofatores de a11,a12,a13,a14

    print(f"cofatores = {resultados}")
    print(f"linhas removidas= {linha_excluida}\n")
    #tenho que pegar a ordem da matriz primeira inciada
    ordem2 = int(len(matriz)) 
    for i in range(ordem2): #calculo final pra saber o determinante usando os cofatores e cada elemento excluido
      calculoFinal = calculoFinal + (linha_excluida[i] * resultados[i])
    return calculoFinal
  else:
      return calcularDeterminante(matriz)



def calculaAutovalor(matriz):
  y = symbols('y')

  for i in range(len(matriz)):
    matriz[i][i] = matriz[i][i] - y #fazendo a diagonal principal - lambida
  printaMatriz(matriz)

  autovalores = solve(Eq(formulaDeterminante(matriz),0)) # pega a equação do determinante e resolve achando raizes

  print (f"autovalores = {autovalores}\n")
  return autovalores


def calculaAutovetor(matriz,autovalores):
  #precisamos montar a equação da matriz
  
  nVariaveis = len(matriz)
  lista_variaveis = symbols('x0:%d' % nVariaveis) #vai criar uma lista de simbolos de x0 até XnVariaveis
  lista_variaveis_resultados = []
  lista_variaveis_lambida = []
  equacoesFormadas = []
  equacoes = []
  expressao = 0

  
  for i in range(len(matriz)):
    expressao = 0 
    for j in range(len(matriz)):
      expressao = expressao+(lista_variaveis[j]*matriz[i][j]) # apartir da matriz faz a eq = x*a11 + y*a12 + z*a13
    equacoes.append(expressao) #respectivas equacoes apartir da matriz.
  
  for p in range(len(autovalores)):# cada autovalor gera um autovalor
    print(f"autovetor n°{p} para o autovalor = {autovalores[p]}")
    
    for i in range(len(lista_variaveis)):
      lista_variaveis_lambida.append(autovalores[p]*lista_variaveis[i]) #autovalores * variaveis
    print(f"equacoes: {equacoes}")#################
    print(f"equacoesAutovalores: {lista_variaveis_lambida}")##########################
  
    for i in range(len(equacoes)):  #formando as equacoes
      equacao = Eq(equacoes[i],lista_variaveis_lambida[i])# x*a11 + y*a12 + z*a13 = autovalor * variavel
      equacoesFormadas.append(equacao) 
      
    print(f"equacoesFormadas: {equacoesFormadas}")
    tupla_lista_variaveis= tuple(lista_variaveis)
    result = solve(equacoesFormadas,tupla_lista_variaveis,dict=True) #resolver o sistema de equações

    print("Autovetor:")
    for sol in result:
      valores = [sol[var] if var in sol else var for var in lista_variaveis]
      print(tuple(valores))
    print("\n")
  
    lista_variaveis_lambida.clear()
    equacoesFormadas.clear()
    
###main###
matriz = definirMatriz()
matriz_copia = deepcopy(matriz) # pra nao mudar a matriz original
autovetores = calculaAutovetor(matriz,calculaAutovalor(matriz_copia))