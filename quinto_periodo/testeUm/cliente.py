import socket

def start_client():
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect(("127.0.0.1", 9999))  # Conecte-se ao servidor na máquina local

    print("[INFO] Conectado ao servidor.")
    try:
        while True:
            number = input("Digite um número (ou 'sair' para encerrar): ")
            if number.lower() == "sair":
                print("[INFO] Encerrando conexão.")
                break

            client.send(number.encode())
            response = client.recv(1024).decode()
            print(f"[RESPOSTA DO SERVIDOR] {response}")
    finally:
        client.close()

if __name__ == "__main__":
    start_client()