import cv2
import numpy as np
import matplotlib.pyplot as plt
from skimage.morphology import binary_dilation, binary_erosion


def display_image(image, title="Image"):
    plt.figure(figsize=(4, 4))
    plt.imshow(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))
    plt.title(title)
    plt.axis('off')
    plt.show()


def fill_black_holes(image):
    # Converter a imagem para o formato binário baseado nos objetos pretos
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    _, binary = cv2.threshold(gray, 1, 255, cv2.THRESH_BINARY_INV)
    # Encontrar contornos e preenchê-los
    contours, _ = cv2.findContours(binary, cv2.RETR_CCOMP,
                                   cv2.CHAIN_APPROX_SIMPLE)
    for cnt in contours:
        cv2.drawContours(binary, [cnt], 0, 255, -1)
    # Inverter a imagem binária
    binary = cv2.bitwise_not(binary)
    # Aplicar a máscara na imagem original
    result = cv2.bitwise_and(image, image, mask=binary)
    return result


def remove_black_objects(image):
    # Converter a imagem para o formato HSV baseado nos objetos pretos
    hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

    # Definir o intervalo para a cor preta no espaço HSV
    inferior_black_limit = np.array([0, 0, 0])
    superior_black_limit = np.array([180, 255, 30])

    # Criar uma máscara para identificar os objetos pretos
    black_mask = cv2.inRange(hsv, inferior_black_limit, superior_black_limit)

    # Aplicar morfologia matemática para identificar remover pequenos objetos pretos
    kernel = np.ones((5, 5), np.uint8)
    black_mask_dil = cv2.dilate(black_mask, kernel, iterations=1)

    # Inverter a máscara dilatada para que os objetos pretos se tornem brancos (255)
    inverted_mask = cv2.bitwise_not(black_mask_dil)

    # Aplicar a máscara invertida na imagem original para remover os objetos pretos
    image = cv2.bitwise_and(image, image, mask=inverted_mask)

    # Substituir os objetos pretos por branco
    image[black_mask_dil == 255] = [255, 255, 255]
    return image


def fill_colored_holes(image):

    # Converter a imagem para o espaço de cores HSV
    hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

    # Definir intervalos de cores para azul, amarelo e verde
    inferior_blue_limit = np.array([100, 150, 0])
    superior_blue_limit = np.array([140, 255, 255])

    inferior_yellow_limit = np.array([20, 100, 100])
    superior_yellow_limit = np.array([30, 255, 255])

    inferior_green_limit = np.array([40, 50, 50])
    superior_green_limit = np.array([90, 255, 255])

    # Criar máscaras para identificar os objetos azul, amarelo e verde
    blue_mask = cv2.inRange(hsv_image, inferior_blue_limit,
                            superior_blue_limit)
    yellow_mask = cv2.inRange(hsv_image, inferior_yellow_limit,
                              superior_yellow_limit)
    green_mask = cv2.inRange(hsv_image, inferior_green_limit,
                             superior_green_limit)

    # Usar morfologia matemática para melhorar as máscaras, desenvolvendo uma nova mascara
    kernel = np.ones((5, 5), np.uint8)
    new_blue_mask = cv2.dilate(blue_mask, kernel, iterations=1)
    new_yellow_mask = cv2.dilate(yellow_mask, kernel, iterations=1)
    new_green_mask = cv2.dilate(green_mask, kernel, iterations=1)

    # Encontrar contornos dos objetos azul, amarelo e verde
    blue_contour, _ = cv2.findContours(new_blue_mask, cv2.RETR_EXTERNAL,
                                       cv2.CHAIN_APPROX_SIMPLE)
    yellow_contour, _ = cv2.findContours(new_yellow_mask, cv2.RETR_EXTERNAL,
                                         cv2.CHAIN_APPROX_SIMPLE)
    greeen_contour, _ = cv2.findContours(new_green_mask, cv2.RETR_EXTERNAL,
                                         cv2.CHAIN_APPROX_SIMPLE)

    # Preencher os contornos com as cores respectivas
    for contorno in blue_contour:
        cv2.drawContours(image, [contorno],
                         0, (255, 0, 0),
                         thickness=cv2.FILLED)

    for contorno in yellow_contour:
        cv2.drawContours(image, [contorno],
                         0, (0, 255, 255),
                         thickness=cv2.FILLED)

    for contorno in greeen_contour:
        cv2.drawContours(image, [contorno],
                         0, (0, 255, 0),
                         thickness=cv2.FILLED)

    return image


def convex_hull_colored_objects(image):
    # Converter a imagem de BGR para RGB
    image_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

    # Definir cores azul, verde e amarelo
    blue = (0, 0, 255)
    yellow = (255, 255, 0)
    green = (0, 255, 0)

    def mask(color):
        return cv2.inRange(image_rgb, color, color)

    # Função para encontrar o fecho convexo
    def convex_hull(mask, color):
        contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL,
                                       cv2.CHAIN_APPROX_SIMPLE)
        hull_image = np.zeros_like(mask)
        for contour in contours:
            hull = cv2.convexHull(contour)
            cv2.drawContours(hull_image, [hull], -1, 255, thickness=cv2.FILLED)
        return hull_image

    # Máscara para objetos vermelhos
    blue_mask = mask(blue)
    green_mask = mask(green)
    yellow_mask = mask(yellow)

    # Processar cada cor e combinar os fechos convexos
    blue_mask_f = convex_hull(blue_mask, blue)
    green_mask_f = convex_hull(green_mask, green)
    yellow_mask_f = convex_hull(yellow_mask, yellow)

    image = image_rgb.copy()

    image[np.where(blue_mask_f == 255)] = blue
    image[np.where(green_mask_f == 255)] = green
    image[np.where(yellow_mask_f == 255)] = yellow

    result_image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)

    return result_image


def skeletonize(image):
    image_hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

    lower_blue = np.array([100, 150, 50])
    upper_blue = np.array([140, 255, 255])

    lower_green = np.array([40, 50, 50])
    upper_green = np.array([80, 255, 255])

    lower_yellow = np.array([20, 100, 100])
    upper_yellow = np.array([30, 255, 255])

    blue_mask = cv2.inRange(image_hsv, lower_blue, upper_blue)
    green_mask = cv2.inRange(image_hsv, lower_green, upper_green)
    yellow_mask = cv2.inRange(image_hsv, lower_yellow, upper_yellow)

    def find_skeleton(mask):
        ES = cv2.getStructuringElement(cv2.MORPH_CROSS, (3, 3))
        skeleton = np.zeros_like(mask)
        while True:
            eroded = cv2.erode(mask, ES)
            temp = cv2.dilate(eroded, ES)
            temp = cv2.subtract(mask, temp)
            skeleton = cv2.bitwise_or(skeleton, temp)
            mask = eroded.copy()
            if cv2.countNonZero(mask) == 0:
                break
        return skeleton

    blue_skeleton = find_skeleton(blue_mask)
    green_skeleton = find_skeleton(green_mask)
    yellow_skeleton = find_skeleton(yellow_mask)
    skeleton_combined = cv2.bitwise_or(
        cv2.bitwise_or(blue_skeleton, green_skeleton), yellow_skeleton)

    result = image.copy()
    red_mask = cv2.inRange(image, (0, 0, 100), (50, 50, 255))

    result[(skeleton_combined == 0) & (red_mask == 0)] = [255, 255, 255]

    return result


def hit_or_miss(image):
    image_hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

    def hitmiss(image, pattern):
        # Inverter o padrão para aplicar erosão
        pattern_inv = np.logical_not(pattern)

        # Erosão do padrão na imagem
        erosion = binary_erosion(image, footprint=pattern).astype(np.uint8)

        # Dilatação da imagem com o padrão invertido
        dilated = binary_dilation(image,
                                  footprint=pattern_inv).astype(np.uint8)

        # Interseção entre erosão e dilatação
        result = erosion & dilated
        return result

    # Definir a faixa de cor para vermelho no espaço HSV
    red_lower1 = np.array([0, 50, 50],
                          dtype="uint8")  # Faixa inferior do vermelho
    red_upper1 = np.array([10, 255, 255],
                          dtype="uint8")  # Faixa superior do vermelho
    red_lower2 = np.array([160, 50, 50],
                          dtype="uint8")  # Faixa inferior do vermelho
    red_upper2 = np.array([180, 255, 255],
                          dtype="uint8")  # Faixa superior do vermelho

    # Criar máscaras para os tons vermelhos
    mask1 = cv2.inRange(image_hsv, red_lower1, red_upper1)
    mask2 = cv2.inRange(image_hsv, red_lower2, red_upper2)

    # Combinar as máscaras
    red_mask = mask1 | mask2
    red_mask_binary = red_mask > 0

    # Criar o padrão para o objeto vermelho
    pattern_size = 15
    pattern = np.zeros((pattern_size, pattern_size), dtype=np.uint8)
    cv2.circle(pattern, (pattern_size // 2, pattern_size // 2),
               pattern_size // 2, 255, -1)
    pattern_binary = pattern > 0

    # Aplicar a transformação Hit-or-Miss para localizar os objetos vermelhos
    result = hitmiss(red_mask_binary, pattern_binary)

    # Criar uma imagem resultante colorida para sobrepor os objetos encontrados
    result_colored = np.zeros_like(image)
    result_colored[result == 1] = [
        0, 0, 255
    ]  # Colorir os objetos encontrados de vermelho

    # Transformar os pixels pretos da imagem final em brancos
    # Criar uma máscara para os pixels pretos
    black_pixels = np.all(result_colored == [0, 0, 0], axis=-1)
    result_colored[black_pixels] = [255, 255, 255]

    return result_colored


def main():
    image = cv2.imread('Tarb.Final-1.png')
    display_image(image)

    # 1. Preencher todos os buracos dos objetos pretos
    filled_black_holes = fill_black_holes(image)
    display_image(filled_black_holes, "Filled Black Holes")

    # 2. Eliminar todos e somente os objetos pretos
    removed_black_objects = remove_black_objects(filled_black_holes)
    display_image(removed_black_objects, "Removed Black Objects")

    # 3. Preencher os buracos dos objetos de cor: azul, amarelo e verde
    filled_colored_holes = fill_colored_holes(removed_black_objects)
    display_image(filled_colored_holes, "Filled Colored Holes")

    # 4. Encontrar o fecho convexo dos objetos de cor: azul, amarelo e verde
    convex_hull = convex_hull_colored_objects(filled_colored_holes)
    display_image(convex_hull, "Convex Hull Colored Objects")

    # 5. Encontre o esqueleto dos objetos de cor: azul, amarelo e verde
    skeleton = skeletonize(convex_hull)
    display_image(skeleton, "Skeleton of Colored Objects")

    # 6. Utilizando a transformada hit-or-miss localize cada um dos objetos vermelhos restantes na imagem
    hitmiss_result = hit_or_miss(skeleton)
    display_image(hitmiss_result, "Hit-or-Miss Transform")


if __name__ == "__main__":
    main()
