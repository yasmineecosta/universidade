conjunto1 = {'vermelho', 'preto', 'branco', 'amarelo'}
conjunto2 = {'azul', 'amarelo', 'laranja', 'preto'}
conjunto3 = {'cinza', 'preto', 'branco', 'dourado'}

while True:
  print("1 - Unir dois conjuntos de cores.")
  print("2 - Interseção entre dois conjuntos de cores.")
  print("3 - Diferença entre dois conjuntos de cores.")
  print("4 - Sair do programa.")
  resp = int(input("Digite a opcao:"))

  if resp == 1:
    c1 = int(input("Escolha o primeiro conjunto de cores: "))
    c2 = int(input("Escolha o primeiro conjunto de cores: "))

    if c1 == 1:
      c1 = conjunto1
    elif c1 == 2:
      c1 = conjunto2
    elif c1 == 3:
      c1 = conjunto3

    if c2 == 1:
      c2 = conjunto1
    elif c2 == 2:
      c2 = conjunto2
    elif c2 == 3:
      c2 = conjunto3

    unir = c1.union(c2)
    print("União dos conjuntos:", unir)

  elif resp == 2:
    c1 = int(input("Escolha o primeiro conjunto de cores: "))
    c2 = int(input("Escolha o primeiro conjunto de cores: "))

    if c1 == 1:
      c1 = conjunto1
    elif c1 == 2:
      c1 = conjunto2
    elif c1 == 3:
      c1 = conjunto3

    if c2 == 1:
      c2 = conjunto1
    elif c2 == 2:
      c2 = conjunto2
    elif c2 == 3:
      c2 = conjunto3

    intersc = c1.intersection(c2)
    print("Intersecção dos conjuntos:", intersc)

  elif resp == 3:
    c1 = int(input("Escolha o primeiro conjunto de cores: "))
    c2 = int(input("Escolha o primeiro conjunto de cores: "))

    if c1 == 1:
      c1 = conjunto1
    elif c1 == 2:
      c1 = conjunto2
    elif c1 == 3:
      c1 = conjunto3

    if c2 == 1:
      c2 = conjunto1
    elif c2 == 2:
      c2 = conjunto2
    elif c2 == 3:
      c2 = conjunto3

    dif = c1.difference(c2)
    print("Diferença dos conjuntos:", dif)

  elif resp == 4:
    print("Programa encerrado.")
    break

  else:
    print("Opção inválida! Por favor, digite uma opção que está no menu!")
