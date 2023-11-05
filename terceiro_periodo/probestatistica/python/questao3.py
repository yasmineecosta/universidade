import math

def soma_desvio(x, y):
    soma = 0
    for i in range(len(x)):
        soma += (x[i] - y)**2
    return soma



def main():
    entrada = input()
    numeros = [int(x) for x in entrada.split(" ")]
    # numerosMenores = [int(x-400) for x in entrada.split(" ")]
    numerosMenores = [x-400 for x in numeros]
    numeros_ordenados = sorted(numeros)
    numerosMenores_ordenador = sorted(numerosMenores)

    media = sum(numeros_ordenados)/len(numeros_ordenados)
    mediaMenor = sum(numerosMenores_ordenador)/len(numerosMenores_ordenador)

    print("Números ordenados:", numeros_ordenados)
    print("Números menos quatrocentos ordenados:", numerosMenores_ordenador)
    print("Média calculada:" , media)
    print("Média menos quatrocentos calculada:", mediaMenor)

    raiz = math.sqrt(soma_desvio(numeros_ordenados, media))
    raizMenor = math.sqrt(soma_desvio(numerosMenores_ordenador, mediaMenor))
    # Letra A
    print("Letra A:")
    print("Desvio amostral: ", raiz/math.sqrt(len(numeros_ordenados)-1))

    # Letra B
    print("Letra B:")
    print("Desvio amostral menos quatrocentos: ", raizMenor/math.sqrt(len(numerosMenores_ordenador)-1))




main()

    