num = int(input("Digite um numero inteiro: "))
print(f"A seguir, todos os numeros pares do 0 até {num}: ")
if num>=0:
  for i in range(0,num+1):
    if i%2 != 0:
      continue
    print(i)
else:
  for i in range(0,num-1,-2):
    if i%2 != 0:
      continue
    print(i)

if num%2!=0:
  print(f"O número {num} não é par")
    