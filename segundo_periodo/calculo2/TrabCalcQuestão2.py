import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

def f(x):
  return -(x-1)**3+x-1
def g(x):
  return np.exp(-2*x)
def Dg(x):
  return -2*(np.exp(-2*x))
def h(x):
  return -3*(x-1)**2 + 1
def funçãogeral(x):
  return (x-1)**3-x+1-np.exp(-2*x)

primeiro_h = True
valores_de_x = []
valores_diferença = ['--------']
print('Entre com o valor inicial de X')
x_inicial = float(input(""))
novo_x = x_inicial
cont = 1

chave = True
while(chave):
  x_anterior = novo_x
  valores_de_x.append(novo_x)
  novo_x = x_anterior-(f(x_anterior)+g(x_anterior))/(h(novo_x)+Dg(x_anterior))
  novo_h = h(x_anterior) + ((f(novo_x)-f(x_anterior)-(h(x_anterior)*(novo_x*x_anterior)))/(np.absolute(novo_x-x_anterior)**2))*(novo_x-x_anterior)
  cont = cont + 1
  valores_diferença.append(np.absolute(x_anterior-novo_x))
  if(np.absolute(x_anterior-novo_x)<=10**(-4) or np.absolute(f(novo_x)+g(novo_x))<=10**(-4)):
    valores_de_x.append(novo_x)
    chave = False

#Gerando a Tabela
indices_de_x = []
dict_valores = {'Valores de x':valores_de_x, '   Valores da Diferença':valores_diferença}
tabela = pd.DataFrame(dict_valores)
print('\n\n')
print(tabela)

#Gerando o Gráfico
eixo_x = np.linspace(-1,3,2048)
eixo_y = funçãogeral(eixo_x)
plt.grid(True)
plt.plot(eixo_x, eixo_y, color = 'red')
plt.scatter(x_inicial,funçãogeral(x_inicial), color = 'darkblue', s = 25)
plt.scatter(novo_x,funçãogeral(novo_x), color = 'darkgreen', s = 25)
plt.title('Gráfico da Função')
plt.axhline(0, color='black', linewidth=1)  
plt.axvline(0, color='black', linewidth=1)
plt.ylim(-1,1)
plt.show()