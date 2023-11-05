entrada = input()
numeros = [int(x) for x in entrada.split(",")]

# Ordena a lista em ordem crescente
numeros_ordenados = sorted(numeros)

# Imprime os números ordenados
print("Números em ordem crescente:", numeros_ordenados)
print("Média calculada:" , sum(numeros_ordenados)/len(numeros_ordenados))
print("Mediana calculada:", numeros_ordenados[len(numeros_ordenados)//2])