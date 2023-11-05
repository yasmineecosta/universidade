frase = input("Digite uma frase que tenha no máximo 100 caracteres: ")
quant = len(frase)

while quant > 100:
  frase = input("Frase com mais de 100 caracteres, digite outra fase: ")
  quant = len(frase)

for i in range(quant - 1, -1, -1):
  print(f"{frase[i]}", end="")