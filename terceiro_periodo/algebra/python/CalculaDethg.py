def nova_matriz(colunas):
    matriz = []
    auxj = 0
    while auxj<colunas:
        matriz.append([])
        auxj+=1
    return matriz

def preenche_matriz(matriz, linhas, colunas):
    for i in range (linhas):
        for j in range (colunas):
            while True:
                try:
                    elemento = int(input(f'a{i+1}{j+1} = '))
                    matriz[i].append(elemento)
                    break
                except ValueError:
                    print("Erro! Insira um número válido!")
    return matriz

def linha_ou_coluna_mais_elementos_nulos(matriz):
    elinha = False
    nlinha = 0
    ecoluna = False
    ncoluna = 0
    mais_nulos = 0

    for i in range (len(matriz[0])):
        quant_nulos=0
        for elemento in matriz[i]:
            if elemento == 0:
                quant_nulos+=1
        if(quant_nulos>mais_nulos):
            mais_nulos = quant_nulos
            elinha = True
            nlinha = i
    
    for i in range (len(matriz)):
        quant_nulos=0
        for j in range(len(matriz[0])):
            if matriz[j][i] == 0:
                quant_nulos+=1
        if(quant_nulos>mais_nulos):
            mais_nulos = quant_nulos
            ecoluna = True
            elinha = False
            ncoluna = i
    
    if elinha == True:
        return 0, nlinha
    elif ecoluna == True:
        return 1, ncoluna
    else:
        return -1, 0

def calcula_det_n3(matriz):
    det = 0
    det += matriz[0][0]*matriz[1][1]*matriz[2][2]
    det += matriz[0][1]*matriz[1][2]*matriz[2][0]
    det += matriz[0][2]*matriz[1][0]*matriz[2][1]
    det -= matriz[0][2]*matriz[1][1]*matriz[2][0]
    det -= matriz[0][1]*matriz[1][0]*matriz[2][2]
    det -= matriz[0][0]*matriz[1][2]*matriz[2][1]
    return det

def calcula_det_n2(matriz):
    det = 0
    det += matriz[0][0]*matriz[1][1]
    det -= matriz[0][1]*matriz[1][0]
    return det

def calcula_det_n1(matriz):
    det = matriz[0][0]
    return det

def laplaceaux(matriz):
    n = len(matriz)
    
    if n == 1:
        return matriz[0][0]
    
    if n == 2:
        return calcula_det_n2(matriz)
    
    if n == 3: 
        return calcula_det_n3(matriz)
    
    det = 0
   
    k = 0
    for m in range (0, len(matriz)):
        submatriz = nova_matriz(n-1)
        l = 0
        cof = ((-1)**(2+m))*matriz[0][m]
        for i in range (0, len(matriz)):
            for j in range (0, len(matriz)):
                if (j != k) and (i != 0):
                    submatriz[l].append(matriz[i][j])
                    if len(submatriz[l]) == n-1:
                        l+=1
                        
        if len(submatriz) == 1:
            det += calcula_det_n1(submatriz)*cof
        elif len(submatriz) == 2:
            det += calcula_det_n2(submatriz)*cof
        elif len(submatriz) == 3:
            det += calcula_det_n3(submatriz)*cof
        else:
            det += laplaceaux(submatriz)*cof
        k+=1
    
    return det

def determinante_de_laplace(matriz):
    return laplaceaux(matriz)


linhas = int(input("Digite a quantidade de linhas da matriz: "))
colunas = int(input("Digite a quantidade de colunas da matriz: "))

if linhas != colunas:
    print("Erro, so e possivel calcular o determinante em matrizes quadradas!")
    exit()
else:
    matriz = nova_matriz(colunas)
    print("Digite os elementos da matriz")
    matriz = preenche_matriz(matriz, linhas, colunas)
    
det = determinante_de_laplace(matriz)

print("determinate =",det)