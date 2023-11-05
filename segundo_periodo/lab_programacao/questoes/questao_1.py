alunos = []

while True:
  print("1 - inserir um novo aluno na lista")
  print("2 - buscar um aluno na lista")
  print("3 - exibir a lista de alunos em ordem alfabética")
  print("4 - remover um aluno da lista")
  print("5 - sair do programa")
  resp = int(input("Digite a opcao desejada: "))
  if resp==1:
    nome = input("Digite o nome do aluno: ")
    alunos.append(nome)
    print(f"Aluno {nome} adicionado com sucesso!")

  elif resp==2:
    busca = input("Digite o nome do aluno a ser buscado: ")
    if busca in alunos:
      print(f"O aluno {busca} está presente na lista")
    else:
      print(f"O aluno {busca} não está presente na lista")

  elif resp==3:
    alunos.sort()
    print("Lista de alunos em ordem alfabética: ")
    for aluno in alunos:
      print(aluno)

  elif resp==4:
    remove = input("Digite o nome do aluno a ser removido: ")
    if remove in alunos:
      alunos.remove(remove)
      print(f"O aluno {remove} foi removido da lista!")
    else:
      print(f"O aluno {remove} não está presente na lista")

  elif resp==5:
    print("Encerrando o programa!")
    break;

  else:
    print("Opção inválida! Por favor, digite uma opção que está no menu!")