import requests

class Download:
    def __init__(self, url_or_file_path, path_arquivo_local): # Construtor da classe
        self.url_or_file_path = url_or_file_path # Atributo que armazena a URL ou o caminho do arquivo
        self.path_arquivo_local = path_arquivo_local # Atributo que armazena o caminho do arquivo local

    def download_file(self): # Método que realiza o download do arquivo
        try: # Tenta realizar o download do arquivo
            if self.url_or_file_path.startswith('http://') or self.url_or_file_path.startswith('https://'): # Se a entrada for uma URL, realiza o download da imagem
                # Se a entrada for uma URL, realiza o download da imagem
                response = requests.get(self.url_or_file_path) # Faz a requisição da URL
                response.raise_for_status() # Verifica se a requisição foi bem sucedida
                with open(self.path_arquivo_local, 'wb') as file: # Abre o arquivo para escrita
                    file.write(response.content) # Escreve o conteúdo da requisição no arquivo
            else: # Se a entrada for um caminho local, copia o arquivo para o diretório local
                with open(self.url_or_file_path, 'rb') as src_file: # Abre o arquivo para leitura
                    with open(self.path_arquivo_local, 'wb') as dest_file: # Abre o arquivo para escrita
                        dest_file.write(src_file.read()) # Escreve o conteúdo do arquivo de origem no arquivo de destino

            print(f"Download completo. Arquivo salvo em: {self.path_arquivo_local}") # Exibe mensagem de sucesso
        except requests.exceptions.MissingSchema: # Se a URL estiver inválida, exibe mensagem de erro
            print("URL inválida. Certifique-se de fornecer uma URL válida.") 
        except requests.exceptions.RequestException as e: # Se ocorrer um erro na requisição, exibe mensagem de erro
            print(f"Erro na conexão: {e}")
        except IOError as e: # Se ocorrer um erro de leitura ou escrita, exibe mensagem de erro
            print(f"Erro ao ler ou escrever o arquivo: {e}")