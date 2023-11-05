classe20 = []
classe25 = []
classe30 = []
classe35 = []
classe40 = []
classe45 = []

def p_medio(num1, num2):
    return (num1 + num2) / 2

def main():
    entrada = input()
    numeros = [int(x) for x in entrada.split(" ")]
    numeros_ordenados = sorted(numeros)

# Classes
    for x in numeros[:]:
        if (x>=20 and x<25):
            classe20.append(x)
        elif (x>=25 and x<30):
            classe25.append(x)
        elif (x>=30 and x<35):  
            classe30.append(x)
        elif (x>=35 and x<40):
            classe35.append(x)
        elif (x>=40 and x<45):  
            classe40.append(x)
        elif (x>=45 and x<50):
            classe45.append(x)    
    print("LETRA A:")
    print(f"Números separados por classes:")
    print(f"Classe 20-25: {classe20}")
    print(f"Classe 25-30: {classe25}")
    print(f"Classe 30-35: {classe30}")
    print(f"Classe 35-40: {classe35}")
    print(f"Classe 40-45: {classe40}")
    print(f"Classe 45-50: {classe45}")
    print("LETRA B:")
    print(f"Ponto médio de cada classe: {p_medio(20,25)}, {p_medio(25,30)}, {p_medio(30,35)},{p_medio(35,40)},{p_medio(40,45)}, {p_medio(45,50)}")


# Imprime os números ordenados
main()
