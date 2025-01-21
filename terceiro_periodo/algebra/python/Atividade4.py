#operações usadas
def produto_interno(vetor1, vetor2):
    return sum(x * y for x, y in zip(vetor1, vetor2))

def subtrair_vetores(vetor1, vetor2):
    return [x - y for x, y in zip(vetor1, vetor2)]

def multiplicar_vetor_por_escalar(vetor, escalar):
    return [x * escalar for x in vetor]




def gram_schmidt(bases):
    num_vetores = len(bases)
    dimensao = len(bases[0])

    base_ortogonalizada = [[0] * dimensao for _ in range(num_vetores)]
    for i in range(num_vetores):
        vetor_atual = bases[i]

        for j in range(i):
            projecao = multiplicar_vetor_por_escalar(base_ortogonalizada[j], produto_interno(vetor_atual, base_ortogonalizada[j]) / produto_interno(base_ortogonalizada[j], base_ortogonalizada[j]))
            vetor_atual = subtrair_vetores(vetor_atual, projecao)

        base_ortogonalizada[i] = vetor_atual

    return base_ortogonalizada





def obter_ortonormal(base_ortogonalizada):
    base_ortonormal = []

    for vetor in base_ortogonalizada:
        base_ortonormal.append(vetor.copy())

    for i in range(len(base_ortonormal)):
        norma = (sum(x**2 for x in base_ortonormal[i]))**0.5
        base_ortonormal[i] = [x / norma for x in base_ortonormal[i]]

    return base_ortonormal

def coordenadas_na_nova_base(vetor, base):
    coordenadas = []
    
    for vetor_base in base:
        coordenada = produto_interno(vetor, vetor_base)
        coordenadas.append(coordenada)
    
    return coordenadas

# Solicitar a entrada do usuário
num_dimensoes = int(input("Digite a dimensão dos vetores na base: "))
num_vetores_base = int(input("Digite o número de vetores na base: "))


print("Digite os vetores da base:")
base_original = []
for j in range(num_vetores_base):
    vetor = [float(input(f"Digite a coordenada {i + 1} do vetor {j + 1} da base: ")) for i in range(num_dimensoes)]

    base_original.append(vetor)


print("\nDigite as coordenadas do vetor:")
vetor_original = [float(input(f"Digite a coordenada {i + 1} do vetor trabalhado: ")) for i in range(num_dimensoes)]



base_ortogonalizada = gram_schmidt(base_original)#         aplica o gram-schimidt
base_ortonormal = obter_ortonormal(base_ortogonalizada)




coordenadas_na_base_ortogonalizada = coordenadas_na_nova_base(vetor_original, base_ortogonalizada)    #coordenadas

coordenadas_na_base_ortonormal = coordenadas_na_nova_base(vetor_original, base_ortonormal)





print("\nBase Original:")
for vetor in base_original:
    print(vetor)

print("\nBase Ortogonalizada:")
for vetor in base_ortogonalizada:
    print(vetor)

print("\nBase Ortonormal:")
for vetor in base_ortonormal:
    print(vetor)

print("\nCoordenadas do Vetor na Nova Base (Ortogonalizada):")
#print(coordenadas_na_base_ortogonalizada)

print("\nCoordenadas do Vetor na Nova Base (Ortonormal):")
print(coordenadas_na_base_ortonormal)
