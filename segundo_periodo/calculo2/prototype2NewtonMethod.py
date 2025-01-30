import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# função
def f(x):
    return (x-1)**3 - x + 1 - np.exp(-2*x)

# derivada da função
def g(x):
    return 3*((x-1)**2) - 1 + (2*np.exp(-2*x))

# Vetor/Input
values_x = []
values_diff = ['********']
x0 = float(input('Digite o valor inicial de X: '))

marg_error = 10**(-4)
x_new = x0
cont = 1

# Método de Newton
while True:
    x_ant = x_new
    
    values_x.append(x_new)
    x_new = x_ant - (f(x_ant) / g(x_ant))
    cont = cont + 1
    values_diff.append(np.absolute(x_ant - x_new))
    
    if (np.absolute(x_ant - x_new) <= marg_error):
        values_x.append(x_new)
        break

# Tabela
ind_x = []
dict_values = {'Valores de x': values_x, 'Valores da Diferença': values_diff}
tabela = pd.DataFrame(dict_values)
print(tabela)

print('\nA raiz encontrada é: %0.6f' % values_x[-1])

# Gráfico
eixo_x = np.linspace(-1, 3, 2048)
y = f(eixo_x)
plt.grid(True)
plt.plot(eixo_x, y, color='red')
plt.scatter(x0, f(x0), color='darkblue', s=25)
plt.scatter(x_new, f(x_new), color='darkgreen', s=25)
plt.title('Gráfico da função f(x)')
plt.axhline(0, color='black', linewidth=1)
plt.axvline(0, color='black', linewidth=1)
plt.ylim(-1, 1)
plt.show()
