import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# função
def f(x):
    return (x-1)**3 - x + 1 - np.exp(-2*x)

# derivada da função
def g(x):
    return 3*((x-1)**2) - 1 + (2*np.exp(-2*x))


# Implementing Newton Raphson Method
def newtonRaphson(x0, marg_erro, max_tent):
    print('\n\n NEWTON RAPHSON METHOD IMPLEMENTATION ')
    step = 1
    flag = 1
    condicao = True

    while condicao:
        if g(x0) == 0.0:
            print('Divide by zero error!')
            break

        x1 = x0 - f(x0)/g(x0)
        print('Iteration-%d, x1 = %0.6f and f(x1) = %0.6f' % (step, x1, f(x1)))
        x0 = x1
        step = step + 1
        if step > max_tent:
            flag = 0
            break
        condicao = abs(f(x1)) > marg_erro

    if flag==1:
        print('\nRequired root is: %0.8f' % x1)
    else:
        print('\nNot Convergent.')

    chave = True
    cont = 1
    while(chave):
        x_ant = x1
    values_x.append(x1)
    x1 = x_ant-(f(x_ant)/g(x_ant))
    cont = cont + 1
    values_diff.append(numpy.absolute(x_ant-x1))
    if(numpy.absolute(x_ant-x1)<=10**(-4)):
        values_x.append(x1)
        chave = False



#Input Section
x0 = input('Digite o valor de x0: ')
e = input('Digite a margem de erro: ')

#vec
values_x = []
values_diff = ['********']
x0 = float(x0)
x_new = x0
marg_erro = float(e)
max_tent = 4


#Note: You can combine above three section like this

# Starting Newton Raphson Method
newtonRaphson(x0, marg_erro, max_tent)


# tabela
dict_values = {'Valores de x':values_x, '   Valores da Diferença':values_diff}
tabela = pd.DataFrame(dict_values)
print('\n')
print(tabela)

# gráfico
x = numpy.linspace(-1, 3, 2048)
y = f(x)
mat.grid(True)
mat.plot(x, y, color='red')
mat.scatter(x0, f(x0), color='darkblue', s=25)
mat.scatter(x_new, f(x_new), color='darkgreen', s=25)
mat.title('Gráfico da Função')
mat.axhline(0, color='black', linewidth=1)  
mat.axvline(0, color='black', linewidth=1)
mat.ylim(-1, 1)
mat.show()
