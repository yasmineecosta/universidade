class Peer:
    #construtor
    def __init__(self, peer_id: str, address: str, port: int):
        self.peer_id = peer_id
        self.address = address
        self.port = port
        self.files = []

#metodos    
    #add_file: adiciona um arquivo ao peer  
    def add_file(self, file: str):
        self.files.append(file)

    #remove_file: remove um arquivo do peer
    def remove_file(self, file: str):
        self.files.remove(file)

    #has_file: verifica se o peer tem um arquivo
    def has_file(self, file: str):
        return file in self.files
    
    #get_files: retorna a lista de arquivos do peer
    def get_peer_id(self):
        return self.peer_id
    
    #identifica qual peer tem um dado arquivo
    def get_files(self):
        return self.files

    #retorna o endereço do peer
    def __str__(self):
        return f'Peer {self.peer_id} at {self.address}:{self.port}'

    def __repr__(self):
        return self.__str__()

