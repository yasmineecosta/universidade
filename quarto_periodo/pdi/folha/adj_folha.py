from PIL import Image
import numpy as np


def image2matrix(image_path):
    image = Image.open(image_path).convert('L')  # 'L' = convertendo para escala de cinza
    image_matrix = np.array(image)
    return image_matrix
    

def vizinhos4(i, j, image_matrix):
    vizinhos = [image_matrix[i+1, j], image_matrix[i-1, j],  # Acima e abaixo
    image_matrix[i, j+1], image_matrix[i, j-1]   # À esquerda e à direita
    ]
    return vizinhos


def edge_pixels_adj4(image_matrix):
    edge_points = []
    height, width = image_matrix.shape  # altura e largura da imagem na matriz
    
    for i in range(1, height - 1):
        for j in range(1, width - 1):
            # pega o pixel atual e verifica se ele é 0 (preto)
            if image_matrix[i, j] == 255:
                vizinhos = vizinhos4(i, j, image_matrix)
                # verifica se algum vizinho é parte do fundo (branco)
                if any(v == 0 for v in vizinhos):
                    edge_points.append((i, j))
            
    return edge_points


def edge_pixels_adj8(image_matrix):
    edge_points = []
    height, width = image_matrix.shape  # altura e largura da imagem na matriz
    
    for i in range(1, height - 1):
        for j in range(1, width - 1):
            # pega o pixel atual e verifica se ele é 0 (preto)
            if image_matrix[i, j] == 255:
                vizinhos = [image_matrix[i+1, j], image_matrix[i-1, j],  # Acima e abaixo
                    image_matrix[i, j+1], image_matrix[i, j-1],   # À esquerda e à direita
                    image_matrix[i+1, j+1], image_matrix[i+1, j-1],  # Inferior direito e inferior esquerdo
                    image_matrix[i-1, j+1], image_matrix[i-1, j-1]   # Superior direito e superior esquerdo
                ]
                if any(v == 0 for v in vizinhos):
                    edge_points.append((i, j))
            
    return edge_points


def edge_pixels_adjM(image_matrix):
    edge_points = []
    height, width = image_matrix.shape  # altura e largura da imagem na matriz
    
    for i in range(1, height - 1):
        for j in range(1, width - 1):
            # pega o pixel atual e verifica se ele é 0 (preto)
            if image_matrix[i, j] == 255:
                # Vizinhança-4 de p
                N4_p = vizinhos4(i, j, image_matrix)
                # Vizinhança Diagonal de p
                ND_p = [    image_matrix[i+1, j+1], image_matrix[i+1, j-1],  # Inferior direito e inferior esquerdo
                            image_matrix[i-1, j+1], image_matrix[i-1, j-1]   # Superior direito e superior esquerdo
                ]
                # aplicando a definicao de adjM como critério para fronteira
                if any(v == 0 for v in N4_p) or (any(v == 0 for v in ND_p) and not any(v == 0 for v in N4_p + ND_p)):
                    edge_points.append((i, j))
            
    return edge_points


def image_from_edge(edge_points, image_matrix):
    matrix_edgy_image = np.zeros(image_matrix.shape) # matriz de 0 (preto)
    for point in edge_points:
       matrix_edgy_image[point[0], point[1]] = 255  # pontos da borda como parte do objeto (branco)

    edgy_image = Image.fromarray(matrix_edgy_image.astype('uint8'))
    return edgy_image


def main():
    image_path = 'folha.png' # imagem de entrada
    image_matrix = image2matrix(image_path)
    edge_points4 = edge_pixels_adj4(image_matrix) 
    edge_points8 = edge_pixels_adj8(image_matrix) 
    edge_pointsM = edge_pixels_adjM(image_matrix) 

    image_from_edge(edge_points4, image_matrix).show()
    image_from_edge(edge_points4, image_matrix).save('folha_adj4.png')
    
    image_from_edge(edge_points8, image_matrix).show()
    image_from_edge(edge_points8, image_matrix).save('folha_adj8.png')
    
    image_from_edge(edge_pointsM, image_matrix).show()
    image_from_edge(edge_pointsM, image_matrix).save('folha_adjM.png')


main()