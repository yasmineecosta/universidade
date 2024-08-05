import threading
import time
import multiprocessing
import random

class FIFO:
    
    def __init__(self, tamanho):
        self.fila = [0] * tamanho  # cria vetor com capacidade = 'tamanho'
        self.cauda = 0
        self.cabeca = 0
        self.qtd_elementos = 0
        self.lock = threading.Condition()

    def enqueue(self, elemento):
        with self.lock:
            while self.cheia():
                print("Fila cheia")
                self.lock.wait()
            self.fila[self.cauda] = elemento  # insere elemento na cauda
            if self.cauda == len(self.fila) - 1:  # se indice cauda aponta fim do vetor(length-1 pois indice vai de 0 a length-1)
                self.cauda = 0  # circula e volta para o inicio
            else:  # indice cauda não aponta o fim
                self.cauda += 1  # incrementa indice cauda
            self.qtd_elementos += 1  # incrementa qtd de elementos
            self.lock.notify_all()
    
    def dequeue(self):
        with self.lock:
            while self.vazia():
                print("Fila vazia")
                self.lock.wait()
            valor = self.fila[self.cabeca]  # extrai o primeiro da fila
            if self.cabeca == len(self.fila) - 1:  # se indice cabeca aponta fim do vetor(cabeca vai de 0 a length-1)
                self.cabeca = 0  # circula e volta pro inicio
            else:  # indice cabeca não aponta o fim
                self.cabeca += 1  # incrementa indice cabeca
            self.qtd_elementos -= 1  # decrementa qtd de elementos
            self.lock.notify_all()
            return valor
    
    def cheia(self):
        return self.qtd_elementos == len(self.fila)
    
    def vazia(self):
        return self.qtd_elementos == 0


class ConsumerProducer:

    def __init__(self, fila):
        self.fila = fila  # variavel fila referencia uma fila passada como argumento

    def produce(self):
        elemento = 0
        while True:  # executa em loop
            with self.fila.lock:
                while self.fila.cheia():  # se fila cheia
                    self.fila.lock.wait()
                self.fila.enqueue(elemento)  # insere elemento
                print(f"Elemento {elemento} produzido")
                elemento += 1
                self.fila.lock.notify_all()
            time.sleep(random.uniform(1,3))  # pequena pausa para simulação

    def consume(self):
        while True:
            with self.fila.lock:
                while self.fila.vazia():  # se fila vazia
                    self.fila.lock.wait()
                elemento = self.fila.dequeue()  # retira primeiro da fila
                print(f"Elemento {elemento} consumido")
                self.fila.lock.notify_all()
            time.sleep(random.uniform(0.5,4))  # pequena pausa para simulação


if __name__ == "__main__":
    # OBJETOS
    fila = FIFO(3)  # fila de tamanho 3
    programa = ConsumerProducer(fila)  # fila é passado como buffer para novo Objeto ConsumerProducer

    # THREADS
    produtor = threading.Thread(target=programa.produce)
    consumidor = threading.Thread(target=programa.consume)

    # INICIA PROGRAMA
    produtor.start()
    consumidor.start()

    # main abdica do controle - aguarda execucao das threads
    produtor.join()
    consumidor.join()