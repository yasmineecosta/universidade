import socket
import threading
import random

SERVERS = [
    ("127.0.0.1", 9999),
    ("127.0.0.1", 9998),
    ("127.0.0.1", 9997),
]

active_clients = []
active_servers = SERVERS.copy()
lock = threading.Lock()

# Função para lidar com clientes

def handle_client(client_socket, address):
    print(f"[INFO] Conexão estabelecida com {address}")
    try:
        while True:
            # Recebe o número do cliente
            data = client_socket.recv(1024).decode()
            if not data:
                break

            print(f"[INFO] Número recebido de {address}: {data}")

            try:
                number = int(data)
                result = number ** 2
                client_socket.send(f"O quadrado de {number} é {result}".encode())
            except ValueError:
                client_socket.send("Por favor, envie um número válido.".encode())
    except ConnectionResetError:
        print(f"[INFO] Conexão com {address} foi encerrada.")
    finally:
        client_socket.close()

# Servidor principal com balanceamento de carga

def start_server(ip, port):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((ip, port))
    server.listen(5)
    print(f"[INFO] Servidor iniciado em {ip}:{port}. Aguardando conexões...")

    try:
        while True:
            client_socket, address = server.accept()
            thread = threading.Thread(target=handle_client, args=(client_socket, address))
            thread.start()
            active_clients.append(thread)
            print(f"[INFO] Conexões ativas: {len(active_clients)}")
    except Exception as e:
        print(f"[INFO] Servidor em {ip}:{port} foi desconectado: {e}")
        with lock:
            active_servers.remove((ip, port))

# Função para escolher um servidor aleatório para balanceamento

def choose_server():
    with lock:
        if not active_servers:
            raise RuntimeError("Nenhum servidor disponível")
        return random.choice(active_servers)

# Adicionar um novo servidor dinamicamente

def add_server(ip, port):
    with lock:
        if (ip, port) not in active_servers:
            active_servers.append((ip, port))
            print(f"[INFO] Novo servidor adicionado: {ip}:{port}")

# Início de múltiplos servidores

def main():
    threads = []
    for ip, port in SERVERS:
        thread = threading.Thread(target=start_server, args=(ip, port))
        thread.start()
        threads.append(thread)

    try:
        for thread in threads:
            thread.join()
    except KeyboardInterrupt:
        print("[INFO] Encerrando aplicação...")

if __name__ == "__main__":
    main()
