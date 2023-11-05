import os
import time
from Filtro import Filtro
from urllib.parse import urlparse
from Imagem import Imagem
from Download import Download

def menu():
  print('Menu')
  print('1 - Inserir o caminho da imagem')
  print('2 - Escolher o filtro a ser aplicado')
  print('3 - Listar arquivos de imagens do diretório corrente')
  print('4 - Sair')
  opcao = int(input('Digite a opção desejada: '))
  return opcao

def sub_menu_filtro():
  print('1 - Grayscale')
  print('2 - Black and White')
  print('3 - Edges')
  print('4 - Smooth')
  print('5 - Blur')
  print('6 - Detail')
  print('7 - Contour')
  opcao = int(input('Digite a opção de filtro desejada: '))
  return opcao

def aplica_filtro(minha_imagem, nome, filtro):
      filter = Filtro()
      vet = ['Grayscale', 'Black and White', 'Edges', 'Smooth', 'Blur', 'Detail', 'Contour']
      print(f'Aplicando filtro {vet[filtro - 1]}...')
      nome += f'_{vet[filtro - 1]}.jpg'
      imagem = filter.create(filtro, minha_imagem)
      imagem.save(nome)

def selecao_filtro(chave_temp, minha_imagem, nome):
    if chave_temp >= 1 and chave_temp <= 7:
      vet = ['Grayscale', 'Black and White', 'Edges', 'Smooth', 'Blur', 'Detail', 'Contour']
      aplica_filtro(minha_imagem, nome, chave_temp)
      print(f'Filtro {vet[chave_temp - 1]} aplicado com sucesso! Arquivo salvo em {nome}')
    else:
      print('Opção inválida!')

def cria_arquivo():
  arquivo = open('lista.txt', mode='w')
  arquivo.write('Lista de imagens\n')
  arquivo.close()

def insere_arquivo(nome_arquivo):
  arquivo = open('lista.txt', mode='a')
  arquivo.write(nome_arquivo + '\n')
  arquivo.close()

def ler_arquivo(nome_arquivo):
  arquivo = open(nome_arquivo, mode='r')
  # for linha in arquivo.readlines():
  #   print(linha)
  print(arquivo.read())
  arquivo.close()

def extrair_nome_extensao_url(url):
  # Faz o parse da URL
  parsed_url = urlparse(url)
  # Obtém o caminho do arquivo
  caminho_arquivo = parsed_url.path
  # Extrai o nome do arquivo e a extensão
  nome_arquivo, extensao = os.path.splitext(os.path.basename(caminho_arquivo))
  return nome_arquivo, extensao

def wait_for_file(file_path, interval=1):
    print('Aguarde...')
    while not os.path.exists(file_path):
      time.sleep(interval)
      interval = interval + 1
      print(".", end=" ")

def cria_imagem(minha_url_ou_caminho_local): # Método que cria a imagem
    print(f'URL ou caminho local: {minha_url_ou_caminho_local}') # Exibe a URL ou o caminho local

    if minha_url_ou_caminho_local.startswith('http://') or minha_url_ou_caminho_local.startswith('https://'):
        # Se a entrada for uma URL, realiza o download da imagem
        nome_arquivo, extensao_arquivo = extrair_nome_extensao_url(minha_url_ou_caminho_local) # Extrai o nome do arquivo e a extensão
        insere_arquivo(nome_arquivo) # Insere o nome do arquivo na lista  
        arquivo = nome_arquivo + extensao_arquivo # Concatena o nome do arquivo com a extensão
        meu_download = Download(minha_url_ou_caminho_local, arquivo) # Instancia a classe Download
        print(f'Inicia download...') # Exibe mensagem de início do download
        meu_download.download_file() # Chama o método que realiza o download
        print(f'Download concluído!') # Exibe mensagem de fim do download
        wait_for_file(arquivo) # Aguarda o arquivo ser criado
    else: 
        # Se a entrada for um caminho local, não é necessário fazer download
        nome_arquivo = os.path.basename(minha_url_ou_caminho_local) # Extrai o nome do arquivo
        insere_arquivo(nome_arquivo) # Insere o nome do arquivo na lista
        arquivo = minha_url_ou_caminho_local # Atribui o caminho local à variável arquivo

    imagem_teste = Imagem(id=1, nome_arquivo=os.path.basename(arquivo), path_arquivo=arquivo) # Instancia a classe Imagem
    print(imagem_teste) # Exibe as informações da imagem
    return imagem_teste.conteudo() # Retorna o conteúdo da imagem

'''class ImageFilter:
    def __init__(self, filter_name):
        self.filter_name = filter_name

    def apply_filter(self, minha_imagem, nome):
        print(f'Aplicando filtro {self.filter_name}...')
        filter_instance = None

        if self.filter_name == 'grayscale':
            filter_instance = GrayscaleFilter()
        elif self.filter_name == 'black_and_white':
            filter_instance = BlackAndWhiteFilter()
        elif self.filter_name == 'edges':
            filter_instance = EdgesFilter()
        elif self.filter_name == 'smooth':
            filter_instance = SmoothFilter()
        elif self.filter_name == 'blur':
            filter_instance = BlurFilter()
        elif self.filter_name == 'detail':
            filter_instance = DetailFilter()
        elif self.filter_name == 'contour':
            filter_instance = ContourFilter()

        if filter_instance:
            filtered_image = filter_instance.apply_filter(minha_imagem)
            nome = nome + f'{self.filter_name}_filtered.jpg'
            filtered_image.save(nome)
            print(f'Filtro {self.filter_name} aplicado com sucesso! Arquivo salvo em {nome}')

def apply_filter(minha_imagem, filter_type, nome):
    filter_applicator = ImageFilter(filter_type)
    filter_applicator.apply_filter(minha_imagem, nome)
'''
class Util:
  def extrair_nome_extensao_url(self,url):
    # Faz o parse da URL
    parsed_url = urlparse(url)
    # Obtém o caminho do arquivo
    caminho_arquivo = parsed_url.path
    # Extrai o nome do arquivo e a extensão
    nome_arquivo, extensao = os.path.splitext(os.path.basename(caminho_arquivo))
    return nome_arquivo, extensao

  def wait_for_file(self,file_path, interval=1):
      print('Aguarde...')
      while not os.path.exists(file_path):
        time.sleep(interval)
        interval = interval + 1
        print(".", end=" ")

def Main(utilidades):
  def __init__(self, utilidades):
    self.utilidades = utilidades

  while True:
        chave = menu()

        if chave == 1:  # inserir o caminho da imagem
          caminho = input('Digite o caminho da imagem: ')
          nome = input('Digite o nome da imagem: ')
          imagem = cria_imagem(caminho)

          #download da imagem
          # função para inserir a url/imagem na lista
          # print(chave)

        elif chave == 2:
          # imagem = cria_imagem('https://raw.githubusercontent.com/my-prototypes/tflk/main/app/static/upload/armando.jpeg')
          #imagem_nova = cria_imagem('estou percebendo uma certa energia maligna.png')
          chave_temp = sub_menu_filtro()
          selecao_filtro(chave_temp, imagem, nome)
            # if chave_temp == '1':
            #   print('Aplicando filtro grayscale...')
            #   # Create an instance of the GrayscaleFilter
            #   grayscale_filter = GrayscaleFilter()
            #   # Apply the filter to the image
            #   filtered_image_grayscale = grayscale_filter.apply_filter(minha_imagem)
            #   # Save the filtered image
            #   nome = nome + '_greyscale.jpg'
            #   filtered_image_grayscale.save(nome)
            #   print(f'Filtro grayscale aplicado com sucesso! Arquivo salvo em {nome}')


          # print(chave)
        elif chave == 3:
          # lendo_arquivos = os.listdir()
          ler_arquivo('lista.txt')
          # print(lendo_arquivos)

        elif chave == 4:
          
          print("Fim do programa!")
          break



# Exemplos de URLs de imagens publicas:
# https://github.com/armandossrecife/lp/raw/main/engenhariasoftware.png
# https://raw.githubusercontent.com/armandossrecife/teste/main/Pizigani_1367_Chart_10MB.jpg

# Execução do programa a partir daqui:
utilidades = Util()
cria_arquivo()
app_principal = Main(utilidades)


'''def aplica_filtro_grayscale(minha_imagem, nome):
  print('Aplicando filtro grayscale...')
  # Create an instance of the GrayscaleFilter
  grayscale_filter = GrayscaleFilter()
  # Apply the filter to the image
  filtered_image_grayscale = grayscale_filter.apply_filter(minha_imagem)
  # Save the filtered image
  nome = nome + '_greyscale.jpg'
  filtered_image_grayscale.save(nome)
  print(f'Filtro grayscale aplicado com sucesso! Arquivo salvo em {nome}')

def aplica_filtro_black_and_white(minha_imagem, nome):
  print('Aplicando filtro BlackAndWhite...')
  # Create an instance of the BlackAndWhiteFilter
  black_and_white_filter = BlackAndWhiteFilter()
  # Apply the filter to the image
  filtered_image_black_and_white = black_and_white_filter.apply_filter(minha_imagem)
  # Save the filtered image
  nome = nome + '_black_and_white.jpg'
  filtered_image_black_and_white.save(nome)
  print(f'Filtro black_and_white aplicado com sucesso! Arquivo salvo em {nome}')

def aplica_filtro_edges(minha_imagem, nome):
  print('Aplicando filtro EdgesFilter...')
  # Create an instance of the EdgesFilter
  edges_filter = EdgesFilter()
  # Apply the filter to the image
  filtered_image_edges_filter = edges_filter.apply_filter(minha_imagem)
  # Save the filtered image
  nome = nome + '_edges.jpg'
  filtered_image_edges_filter.save(nome)
  print(f'Filtro edges aplicado com sucesso! Arquivo salvo em {nome}')

def aplica_filtro_smooth(minha_imagem, nome):
  print('Aplicando filtro SmoothFilter...')
  # Create an instance of the SmoothFilter
  smoothfilter = SmoothFilter()
  # Apply the filter to the image
  filtered_image_smooth_filter = smoothfilter.apply_filter(minha_imagem)
  # Save the filtered image
  nome = nome + '_smooth.jpg'
  filtered_image_smooth_filter.save(nome)
  print(f'Filtro Smooth aplicado com sucesso! Arquivo salvo em {nome}')

def aplica_filtro_blur(minha_imagem, nome):
  print('Aplicando filtro BlurFilter...')
  # Create an instance of the BlurFilter
  blurfilter = BlurFilter()
  # Apply the filter to the image
  filtered_image_blur_filter = blurfilter.apply_filter(minha_imagem)
  # Save the filtered image
  nome = nome + '_blur.jpg'
  filtered_image_blur_filter.save(nome)
  print(f'Filtro Blur aplicado com sucesso! Arquivo salvo em {nome}')

def aplica_filtro_detail(minha_imagem, nome):
  print('Aplicando filtro DetailFilter...')
  # Create an instance of the DetailFilter
  detailfilter = DetailFilter()
  # Apply the filter to the image
  filtered_image_detail_filter = detailfilter.apply_filter(minha_imagem)
  # Save the filtered image
  nome = nome + '_detail.jpg'
  filtered_image_detail_filter.save(nome)
  print(f'Filtro Detail aplicado com sucesso! Arquivo salvo em {nome}')

def aplica_filtro_contour(minha_imagem, nome):
  print('Aplicando filtro ContourFilter...')
  # Create an instance of the ContourFilter
  contourfilter = ContourFilter()
  # Apply the filter to the image
  filtered_image_contour_filter = contourfilter.apply_filter(minha_imagem)
  # Save the filtered image
  nome = nome + '_contour.jpg'
  filtered_image_contour_filter.save(nome)
  print(f'Filtro Contour aplicado com sucesso! Arquivo salvo em {nome}')
'''

# Cria uma imagem
#imagem1 = cria_imagem('https://raw.githubusercontent.com/my-prototypes/tflk/main/app/static/upload/armando.jpeg')
'''imagem_gatinho = cria_imagem('https://img.freepik.com/vetores-gratis/gatinho-fofo-no-prado_1308-141414.jpg?w=740&t=st=1690814811~exp=1690815411~hmac=8c4aeb08e064d9706d094c3b28e6df3a6f95f71b399391c40d514f0bacff7fba')
imagem_nova = cria_imagem('estou percebendo uma certa energia maligna.png')
imagem_cinzenta = cria_imagem('WhatsApp-Image-2023-08-05-at-18.20.31.jpg')'''

# Aplica filtros na imagem criada
'''aplica_filtro_grayscale(minha_imagem=imagem1, nome='armando')
aplica_filtro_black_and_white(minha_imagem=imagem1, nome='armando')
aplica_filtro_edges(minha_imagem=imagem1, nome='armando')
aplica_filtro_smooth(minha_imagem=imagem1, nome='armando')
aplica_filtro_blur(minha_imagem=imagem1, nome='armando')
aplica_filtro_detail(minha_imagem=imagem1, nome='armando')
aplica_filtro_contour(minha_imagem=imagem1, nome='armando')

aplica_filtro_grayscale(minha_imagem=imagem_gatinho, nome='gatinho')
aplica_filtro_black_and_white(minha_imagem=imagem_gatinho, nome='gatinho')
aplica_filtro_edges(minha_imagem=imagem_gatinho, nome='gatinho')
aplica_filtro_smooth(minha_imagem=imagem_gatinho, nome='gatinho')
aplica_filtro_blur(minha_imagem=imagem_gatinho, nome='gatinho')
aplica_filtro_detail(minha_imagem=imagem_gatinho, nome='gatinho')
aplica_filtro_contour(minha_imagem=imagem_gatinho, nome='gatinho')

aplica_filtro_grayscale(minha_imagem=imagem_nova, nome='nova')
aplica_filtro_black_and_white(minha_imagem=imagem_nova, nome='nova')
aplica_filtro_edges(minha_imagem=imagem_nova, nome='nova')
aplica_filtro_smooth(minha_imagem=imagem_nova, nome='nova')
aplica_filtro_blur(minha_imagem=imagem_nova, nome='nova')
aplica_filtro_detail(minha_imagem=imagem_nova, nome='nova')
aplica_filtro_contour(minha_imagem=imagem_nova, nome='nova')

aplica_filtro_grayscale(minha_imagem=imagem_cinzenta, nome='cinzenta')
aplica_filtro_black_and_white(minha_imagem=imagem_cinzenta, nome='cinzenta')
aplica_filtro_edges(minha_imagem=imagem_cinzenta, nome='cinzenta')
aplica_filtro_smooth(minha_imagem=imagem_cinzenta, nome='cinzenta')
aplica_filtro_blur(minha_imagem=imagem_cinzenta, nome='cinzenta')
aplica_filtro_detail(minha_imagem=imagem_cinzenta, nome='cinzenta')
aplica_filtro_contour(minha_imagem=imagem_cinzenta, nome='cinzenta')'''

# Aplica filtros
'''apply_filter(imagem1, 'grayscale', 'armando')
apply_filter(imagem1, 'black_and_white', 'armando')
apply_filter(imagem1, 'edges', 'armando')'''
