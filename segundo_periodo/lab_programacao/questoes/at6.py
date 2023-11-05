num = int(input("Digite um numero: "))

print(f"A seguir, todos os numeros impares do 1 até {num}: ")
if num >= 0:
  for i in range(1, num + 1):
    if i % 2 == 0:
      continue
    print(i)
else:
  for i in range(-1, num - 1, -2):
    if i % 2 == 0:
      continue
    print(i)

if num % 2 == 0:
  print(f"O número {num} não é ímpar")