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
values_x = []
values_diff = ['----------']
x0 = float(input('Digite o valor inicial de X: '))

marg_erro = 10**(-4)

# t = 4
# x_new = x0

# método quasi-newton com atualização de broyden
# Método de Newton
def newton(x0):
  x_new = x0
  step = 1
  flag = 1
  cont = 1

  condicao = True

  while condicao:
    x_ant = x_new
    values_x.append(x_new)
    x_new = x_ant - (f(x_ant) / g(x_ant))
    cont = cont + 1
    values_diff.append(np.absolute(x_ant - x_new))

    if (np.absolute(x_ant - x_new) <= marg_erro):
      values_x.append(x_new)
      condicao = False
    '''
    if g(x0) == 0.0:
      print('Erro de divisão por zero!')
      break

    x1 = x0 - f(x0) / g(x0)
    print('Iteração-%d, x1 = %0.6f e f(x1) = %0.6f' % (step, x1, f(x1)))
    x0 = x1
    step = step + 1
    if step >= 4:
      flag = 0
      break
    condicao = abs(f(x1)) > marg_erro

    if flag == 1:
      print('\nA raiz encontrada é: %0.8f' % x1)
    else:
      print('\nNão convergente.')

    '''


# Iniciando o método de Newton
result = print(newton(x0))

# Tabela
ind_x = []
dict_values = {
  'Valores de x': values_x,
  '   Valores da Diferença': values_diff
}
tabela = pd.DataFrame(dict_values)
print('\n\n')
print(tabela)

# Gráfico
x = np.linspace(-1, 3, 2048)
y = f(x)
plt.grid(True)
plt.plot(x, y, color='red')
plt.scatter(x0, f(x0), color='darkblue', s=25)
plt.scatter(values_x[-1], f(values_x[-1]), color='myrtle', s=25)
plt.title('Gráfico da função f(x)')
plt.axhline(0, color='black', linewidth=1)
plt.axvline(0, color='black', linewidth=1)
plt.ylim(-1, 1)
plt.show()
