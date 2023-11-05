def fat(num):
  if num < 0:
    fim1 = print(f"Numeros negativos, como o {num}, não possuem fatorial.")
    return fim1

  elif num == 0:
    fim2 = print(f"{num}! = 1")
    return fim2
  else:
    fat = 1
    print(f"A seguir, o fatorial de {num}: ")
    print(f"{num}! = ", end="")
    for i in range(num, 0, -1):
      fat *= i
      if i == 1:
        print("1", end="")
      else:
        print(f"{i} * ", end="")

    print(f" = {fat}")
    # break


num = int(input("Digite um número:"))
# result = fat(num)
print(fat(num))
