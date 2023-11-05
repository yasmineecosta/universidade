import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


# função
def f(x):
  return (x - 1)**3 - x + 1 - np.exp(-2 * x)


# derivada da função
def g(x):
  return 3 * ((x - 1)**2) - 1 + (2 * np.exp(-2 * x))


# Vetor/Input
# values_x = []
# values_diff = ['----------']
x0 = float(input('Digite o valor inicial de X: '))



# t = 4
# x_new = x0

# método quasi-newton com atualização de broyden
def broyden_method(x0, max_iter=10):
  values_x = [x0]
  values_diff = ['----------']
  marg_erro = 10**(-4)
    
  for i in range(max_iter):
    fx = f(x0)
    gx = g(x0)

    #Calculo do h(x0) usando f'(x0)
    hx = g(x0)
    x_prox = x0 - ((fx / gx) / (hx + g(x0)))

    diff = abs(x_prox - x0)
    values_x.append(x_prox)
    values_diff.append(diff)

    if diff <= marg_erro or abs(fx+gx) <= marg_erro:
      break;
    
    x0 = x_prox
  
  dict_values = {
  'Valores de x': values_x,
  '   Valores da Diferença': values_diff
  }
  tabela = pd.DataFrame(dict_values)
  return x_prox, tabela

# Tabela
solucao_aproximada, tabela = broyden_method(x0)
print('\n\nTabela de Valores e Diferenças: \n')
print(tabela)

# desenvolvendo o gráfico, usando numpy e matplotlib
x = np.linspace(-1, 3, 2048)
y = f(x)
plt.grid(True)
plt.plot(x, y, color='red')
plt.scatter(x0, f(x0), color='darkblue', s=25)
plt.scatter(solucao_aproximada, f(solucao_aproximada), color='darkgreen', s=25)
plt.title('Gráfico da função f(x)')
plt.axhline(0, color='black', linewidth=1)
plt.axvline(0, color='black', linewidth=1)
plt.ylim(-1, 1)
plt.show()
