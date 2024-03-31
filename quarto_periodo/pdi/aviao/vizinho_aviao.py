from PIL import Image
import numpy as np


def image2matrix(image_path):
    image = Image.open(image_path).convert('L')  # 'L' = convertendo para escala de cinza
    image_matrix = np.array(image)
    return image_matrix
    

def edge_pixels_vizinho4(image_matrix):
    image = np.ones(image_matrix.shape) * 255
    height, width = image_matrix.shape  # altura e largura da imagem na matriz

    for i in range(1, height - 1):
        for j in range(1, width - 1):
            # pega o pixel atual e verifica se ele é 0 (preto)
            if image_matrix[i, j] == 0:
                # Pintar os vizinhos de preto (0)
                image[i,j] = 0
                image[i, j-1] = 0
                image[i, j+1] = 0
                image[i-1, j] = 0
                image[i+1, j] = 0

    return image


def edge_pixels_vizinho8(image_matrix):
    image = np.ones(image_matrix.shape) * 255
    height, width = image_matrix.shape  # altura e largura da imagem na matriz

    for i in range(1, height - 1):
        for j in range(1, width - 1):
            # pega o pixel atual e verifica se ele é 0 (preto)
            if image_matrix[i, j] == 0:
                # Pintar os vizinhos de preto (0)
                image[i,j] = 0
                image[i, j-1] = 0
                image[i, j+1] = 0
                image[i-1, j] = 0
                image[i+1, j] = 0

                image[i-1, j-1] = 0
                image[i+1, j+1] = 0
                image[i+1, j-1] = 0
                image[i-1, j+1] = 0   

    return image


def edge_pixels_vizinhoD(image_matrix):
    image = np.ones(image_matrix.shape) * 255
    height, width = image_matrix.shape  # altura e largura da imagem na matriz

    for i in range(1, height - 1):
        for j in range(1, width - 1):
            # pega o pixel atual e verifica se ele é 0 (preto)
            if image_matrix[i, j] == 0:
                # Pintar os vizinhos de preto (0)
                image[i,j] = 0
                # image[i, j-1] = 0
                # image[i, j+1] = 0
                # image[i-1, j] = 0
                # image[i+1, j] = 0

                image[i-1, j-1] = 0
                image[i+1, j+1] = 0
                image[i+1, j-1] = 0
                image[i-1, j+1] = 0   

    return image


def main():
    image_path4 = 'aviao_adj4.png' # imagem de entrada
    image_path8 = 'aviao_adj8.png' # imagem de entrada
    image_pathM = 'aviao_adjM.png' # imagem de entrada

    image_matrix = image2matrix(image_path4)
    image_matrix8 = image2matrix(image_path8)
    image_matrixM = image2matrix(image_pathM)

    edge_points4 = edge_pixels_vizinho4(image_matrix) 
    edge_points4_8 = edge_pixels_vizinho8(image_matrix) 
    edge_points4_M = edge_pixels_vizinhoD(image_matrix) 

    edge_points8_4 = edge_pixels_vizinho4(image_matrix8) 
    edge_points8 = edge_pixels_vizinho8(image_matrix8) 
    edge_points8_M = edge_pixels_vizinhoD(image_matrix8)

    edge_pointsM_4 = edge_pixels_vizinho4(image_matrixM) 
    edge_pointsM_8 = edge_pixels_vizinho8(image_matrixM) 
    edge_pointsM = edge_pixels_vizinhoD(image_matrixM)

    modified_image4 = Image.fromarray(edge_points4.astype('uint8'))
    modified_image4_8 = Image.fromarray(edge_points4_8.astype('uint8'))
    modified_image4_D = Image.fromarray(edge_points4_M.astype('uint8'))

    modified_image8_4 = Image.fromarray(edge_points8_4.astype('uint8'))
    modified_image8 = Image.fromarray(edge_points8.astype('uint8'))
    modified_image8_D = Image.fromarray(edge_points8_M.astype('uint8'))

    modified_imageM_4 = Image.fromarray(edge_pointsM_4.astype('uint8'))
    modified_imageM_8 = Image.fromarray(edge_pointsM_8.astype('uint8'))
    modified_imageM_D = Image.fromarray(edge_pointsM.astype('uint8'))


    modified_image4.save("aviao_adj4_vizinho4.png")
    modified_image4_8.save("aviao_adj4_vizinho8.png")
    modified_image4_D.save("aviao_adj4_vizinhoD.png")

    modified_image8_4.save("aviao_adj8_vizinho4.png")
    modified_image8.save("aviao_adj8_vizinho8.png")
    modified_image8_D.save("aviao_adj8_vizinhoD.png")

    modified_imageM_4.save("aviao_adjM_vizinho4.png")
    modified_imageM_8.save("aviao_adjM_vizinho8.png")
    modified_imageM_D.save("aviao_adjM_vizinhoD.png")
    
    modified_image4.show()
    modified_image4_8.show()
    modified_image4_D.show()
    modified_image8_4.show()
    modified_image8.show()
    modified_image8_D.show()
    modified_imageM_4.show()
    modified_imageM_8.show()
    modified_imageM_D.show()


main()