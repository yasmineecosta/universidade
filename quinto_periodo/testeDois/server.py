from fastapi import FastAPI, WebSocket, WebSocketDisconnect
from typing import List
import uvicorn
import argparse  # Biblioteca para tratar argumentos da linha de comando

app = FastAPI()

# Lista para armazenar conexões ativas
connected_clients: List[WebSocket] = []

@app.websocket("/ws")
async def websocket_endpoint(websocket: WebSocket):
    await websocket.accept()
    connected_clients.append(websocket)
    try:
        while True:
            message = await websocket.receive_text()
            print(f"Mensagem recebida: {message}")

# Repassa a mensagem para todos os outros nós conectados
            for client in connected_clients:
                if client != websocket:
                    await client.send_text(f"Mensagem de um nó: {message}")
    except WebSocketDisconnect:
        print(f"Um nó foi desconectado")
        connected_clients.remove(websocket)

if name == "main":
    # Configuração do argparse para capturar a porta da linha de comando
    parser = argparse.ArgumentParser(description="Iniciar servidor FastAPI com WebSockets.")
    parser.add_argument("port", type=int, nargs="?", default=8000, help="Porta para o servidor FastAPI (padrão: 8000)")
    args = parser.parse_args()

    # Executa o servidor na porta especificada
    uvicorn.run(app, host="0.0.0.0", port=args.port)