from PIL import Image
import os

class Imagem:
    minha_imagem = None # Atributo que armazena a imagem

    def __init__(self, id, nome_arquivo, path_arquivo): # Construtor da classe
        self.id = id # Atributo que armazena o id da imagem
        self.nome_arquivo = nome_arquivo # Atributo que armazena o nome do arquivo
        self.local_referencia = path_arquivo # Atributo que armazena o caminho do arquivo
        try: # Tenta criar a imagem
            self.minha_imagem = Image.open(path_arquivo) # Cria a imagem
        except Exception as ex: # Se ocorrer um erro, exibe mensagem de erro
            print(f'Erro ao criar a imagem com o arquivo {nome_arquivo} na referência {path_arquivo}: {str(ex)}')

    # Métodos que retornam informações da imagem
    def dimensoes(self):
        return self.minha_imagem.size

    def tamanho(self):
        return os.path.getsize(self.local_referencia)

    def formato(self):
        return self.minha_imagem.format

    def conteudo(self):
        return self.minha_imagem

    def __str__(self):
        return f'Nome: {self.nome_arquivo}, Dimensoes:{self.dimensoes()}, Formato: {self.formato()}, Tamanho: {self.tamanho()} Bytes'