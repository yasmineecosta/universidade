rota = []

while True:
  print("1 - adicionar um novo ponto GPS à rota.")
  print("2 - remover um ponto GPS da rota.")
  print("3 - exibir a rota atual.")
  print("4 - sair do programa.")
  resp = int(input("Digite a opcao desejada: "))
  if resp==1:
    latitude = float(input("Digite o ponto latitudinal a ser incluído à rota: "))
    longitude = float(input("Digite o ponto longitudinal a ser incluído à rota: "))
    ponto_GPS = (latitude,longitude)
    rota.append(ponto_GPS)
    print(f"Ponto {ponto_GPS} adicionado com sucesso à rota!")
    print("Rota atualizada", rota)
  
  elif resp==2:
    if len(rota) > 0:
      latitude = float(input("Digite o ponto latitudinal a ser removido da rota: "))
      longitude = float(input("Digite o ponto longitudinal a ser removido da rota: "))
      ponto_GPS = (latitude,longitude)
      if ponto_GPS in rota:
        rota.remove(ponto_GPS)
        print(f"Ponto {ponto_GPS} removido com sucesso à rota!")
        print("Rota atualizada", rota)
      
      else:
        print(f"O ponto {ponto_GPS} não está presente na rota!")
        print("Rota: ", rota)

  elif resp==3:
    print("Rota atual:")
    for ponto in rota:
      print(ponto[0],ponto[1])
  
  elif resp==4:
    print("Encerrando o programa!")
    break;
  else:
    print("Opção inválida! Por favor, digite uma opção que está no menu!")
    print(rota)
    
    

