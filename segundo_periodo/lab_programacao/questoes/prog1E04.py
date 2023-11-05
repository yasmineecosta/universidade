def menu():
  print("---------MENU---------")
  print("1 - Inserir pessoa")
  print("2 - Listar pessoas cadastradas")
  print("3 - Buscar pessoa por CPF")
  print("4 - Buscar pessoa por telefone")
  print("5 - Remover pessoa por CPF")
  print("6 - SAIR")


def temcpf(cpf):
  file_temp = open('pessoas.txt', 'r')
  for linha in file_temp:
    dados = linha.split(";")
    if dados[0] == cpf:
      file_temp.close()
      return True
  file_temp.close()
  return False


def inserir_telefones():
  telefones = []
  tel = str(input("Digite o(s) telefone(s) da pessoa(separados por vírgula):"))
  telefones.append(tel)
  return telefones


def ler_dados():
  cpf = input("Qual o CPF? ")
  while temcpf(cpf):
    if temcpf(cpf):
      print("CPF já cadastrado! Tente novamente.")
    cpf = input("Qual o CPF? ")
  nome = input("Qual o nome? ")
  endereco = input("Qual o endereco? ")
  telefone = inserir_telefones()
  pessoa = cpf + ";" + nome + ";" + endereco + ";" + ",".join(telefone) + "\n"
  # print("Pessoa inserida com sucesso!\n")
  return pessoa


def inserir_pessoa(nome_arquivo, conteudo):
  file_temp = open(nome_arquivo, 'a')
  conteudo = conteudo + "\n"
  file_temp.write(conteudo)
  file_temp.close()
  print("Pessoa inserida com sucesso!\n")


def listar_pessoas_cadastradas(nome_arquivo):

  file_temp = open(nome_arquivo, 'r')
  linhas = file_temp.read()
  if not linhas:
    print("\n---A lista está vazia!---\n")
  else:
    file_temp.close
    file_temp = open(nome_arquivo, 'r')
    for linha in file_temp:
      print(linha, end='')
    print('\n')
    file_temp.close()


def buscar_por_CPF(nome_arquivo, cpf):
  file_temp = open(nome_arquivo, 'r')
  for linha in file_temp:
    dados = linha.split(';')
    if dados[0] == cpf:
      file_temp.close()
      return linha

  file_temp.close()
  print("CPF não registrado!")
  return


def buscar_por_Tel(nome_arquivo):
  file_temp = open(nome_arquivo, 'r')
  telefone = input("Telefone que procura: ").strip().lower()
  for linha in file_temp:
    dados = linha.split(';')
    if len(dados) >= 4:
      tel = dados[3].split(',')
      for i in range(len(tel)):
        if tel[i].strip().lower() == telefone:
          file_temp.close()
          return linha
  file_temp.close()
  return None


def remover_por_CPF(nome_arquivo, cpf):
  file_temp = open(nome_arquivo, 'r')
  linhas = file_temp.readlines()
  file_temp.close()

  pessoa_encontrada = False
  for linha in linhas:
    dados = linha.split(';')
    if dados[0] == cpf:
      linhas.remove(linha)
      pessoa_encontrada = True
      break
    #else:
    #  pessoa.append(dados)
  if pessoa_encontrada:
    file_temp = open(nome_arquivo, 'w')
    file_temp.writelines(linhas)
    file_temp.close()
    print("Pessoa removida da lista com sucesso!\n")
  else:
    print("Pessoa não encontrada!\n")


def executa_agenda():
  while True:
    menu()
    opcao = input("Escolha uma opção do menu: ")
    if opcao == '1':
      pessoa_temp = ler_dados()
      inserir_pessoa('pessoas.txt', pessoa_temp)

    elif opcao == '2':
      listar_pessoas_cadastradas("pessoas.txt")

    elif opcao == '3':
      cpf = input("Digite o CPF da pessoa que busca: ")
      print(buscar_por_CPF('pessoas.txt', cpf))

    elif opcao == '4':
      achou = buscar_por_Tel('pessoas.txt')
      if achou is not None:
        print(achou)
      else:
        print("Número de telefone não encontrado!")

    elif opcao == '5':
      cpf = input("Digite o CPF da pessoa que deseja remover: ")
      remover_por_CPF('pessoas.txt', cpf)

    elif opcao == '6':
      print("Programa encerrado!")
      break

    else:
      print("Opção inválida. Tente novamente. \n")


executa_agenda()
