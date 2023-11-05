import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# função f(x)
def function(x):
  return (x - 1)**3 - x + 1 - np.exp(-2 * x)
def f(x):
  return -(x-1)**3+x-1
# função g(x)
def g(x):
  return np.exp(-2 * x)
def Dg(x):
  return -2 * np.exp(-2 * x)
# função h(x)
def h(x):
  return -3 * (x - 1)**2 + 1

# Vetor
values_x = []
values_diff = ['----------']

# Input
x0 = float(input('Digite o valor inicial de X: '))

# valores iniciais
h0 = True
x_new = x0
cont = 1
cond = True

# valor de margem de erro, representando a condição do 2.
marg_erro = 10**(-4)

# método quasi-newton com atualização de broyden (loop)
while cond:
    x_ant = x_new
    values_x.append(x_new)
    
    x_new = x_ant - (f(x_ant) + g(x_ant)) / (h(x_new) + Dg(x_ant))
    
    # calculo do h(novo) usando f(x)
    h_new = h(x_ant) + ((f(x_new) - f(x_ant) - (h(x_ant) * (x_new - x_ant))) / (np.absolute(x_new - x_ant)**2)) * (x_new - x_ant)
    cont+= 1
    values_diff.append(np.absolute(x_ant - x_new))

    if (np.absolute(f(x_new) + g(x_new)) <= marg_erro or np.absolute(x_ant - x_new) <= marg_erro):
      values_x.append(x_new)
      cond = False
    

# Tabela a partir dos valores de x e das diferenças, usando pandas
ind_x = []
dict_values = {'Valores de x': values_x,'   Valores da Diferença': values_diff}
tabela = pd.DataFrame(dict_values)
print('\n\n')
print(tabela)
print('\nA raiz encontrada é: %0.6f' % values_x[-1])

# desenvolvendo o gráfico, usando numpy e matplotlib
x = np.linspace(-1, 3, 2048)
y = function(x)
plt.grid(True)
plt.plot(x, y, color='red')
plt.scatter(x0, function(x0), color='darkblue', s=25)
plt.scatter(x_new, function(x_new), color='darkgreen', s=25)
plt.title('Gráfico da função f(x)')
plt.axhline(0, color='black', linewidth=1)
plt.axvline(0, color='black', linewidth=1)
plt.ylim(-1, 1)
plt.show()