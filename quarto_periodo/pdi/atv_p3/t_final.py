import cv2
import numpy as np
import matplotlib.pyplot as plt


def display_image(image, title="Image"):
    plt.figure(figsize=(10, 10))
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
    # Converter a imagem para o formato binário baseado nos objetos pretos
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    _, binary = cv2.threshold(gray, 1, 255, cv2.THRESH_BINARY_INV)

    # Aplicar morfologia matemática para remover pequenos objetos pretos
    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (3, 3))
    morphed = cv2.morphologyEx(binary, cv2.MORPH_OPEN, kernel, iterations=2)

    # Encontrar contornos e remover os objetos pretos
    contours, _ = cv2.findContours(morphed, cv2.RETR_EXTERNAL,
                                   cv2.CHAIN_APPROX_SIMPLE)
    for cnt in contours:
        cv2.drawContours(image, [cnt], 0, (255, 255, 255), -1)

    return image


def fill_colored_holes(image):
    # Separar os canais de cor
    b, g, r = cv2.split(image)

    # Função para detectar buracos em um único canal
    def detect_holes(channel):
        # Inverter a imagem para que os buracos se tornem objetos
        inverted_channel = cv2.bitwise_not(channel)

        # Encontrar contornos e preencher os buracos
        contours, _ = cv2.findContours(inverted_channel, cv2.RETR_TREE,
                                       cv2.CHAIN_APPROX_SIMPLE)

        # Criar uma máscara dos buracos
        mask = np.zeros_like(channel)
        for cnt in contours:
            if cv2.contourArea(cnt) >= 0:
                cv2.drawContours(mask, [cnt], 0, 255, -1)

        # Subtrair as bordas para obter apenas os buracos
        #edges = cv2.Canny(channel, 1, 1)
        #holes_mask = cv2.subtract(mask, edges)

        return mask

    # Função para preencher buracos em um único canal
    def fill_holes(channel, holes_mask):
        # Criar uma imagem de trabalho
        working_image = channel.copy()

        # Definir o kernel para operações morfológicas
        kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (3, 3))

        # Continuar dilatando até que os buracos sejam preenchidos
        while True:
            # Dilatar a imagem de trabalho
            dilated = cv2.dilate(working_image, kernel, iterations=1)

            # Aplicar a máscara para limitar a dilatação apenas às áreas dos buracos
            dilated_with_mask = cv2.bitwise_and(dilated,
                                                dilated,
                                                mask=holes_mask)

            # Verificar se houve mudanças
            if np.array_equal(dilated_with_mask, working_image):
                break

            # Atualizar a imagem de trabalho
            working_image = dilated_with_mask

        return working_image

    # Detectar buracos em cada canal
    b_holes = detect_holes(b)
    g_holes = detect_holes(g)
    r_holes = detect_holes(r)

    # Preencher buracos em cada canal
    b_filled = fill_holes(b, b_holes)
    g_filled = fill_holes(g, g_holes)
    r_filled = fill_holes(r, r_holes)

    b_filled = cv2.bitwise_not(b_filled)
    g_filled = cv2.bitwise_not(g_filled)
    r_filled = cv2.bitwise_not(r_filled)
    # Combinar os canais preenchidos de volta em uma imagem RGB
    result = cv2.merge((b_filled, g_filled, r_filled))

    return result


def convex_hull_colored_objects(image):
    inverted = cv2.bitwise_not(image)
    _, binary = cv2.threshold(inverted, 1, 255, cv2.THRESH_BINARY_INV)
    contours, _ = cv2.findContours(inverted, cv2.RETR_EXTERNAL,
                                   cv2.CHAIN_APPROX_SIMPLE)
    hull_image = np.zeros_like(image)
    for cnt in contours:
        hull = cv2.convexHull(cnt)
        cv2.drawContours(hull_image, [hull], -1, (255, 255, 255), -1)
    return hull_image


def skeletonize(image):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    _, binary = cv2.threshold(gray, 10, 255, cv2.THRESH_BINARY)
    skeleton = np.zeros_like(binary)
    element = cv2.getStructuringElement(cv2.MORPH_CROSS, (3, 3))
    while True:
        open_img = cv2.morphologyEx(binary, cv2.MORPH_OPEN, element)
        temp = cv2.subtract(binary, open_img)
        eroded = cv2.erode(binary, element)
        skeleton = cv2.bitwise_or(skeleton, temp)
        binary = eroded.copy()
        if cv2.countNonZero(binary) == 0:
            break
    return skeleton


def hit_or_miss(image, kernel):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    hitmiss = cv2.morphologyEx(gray, cv2.MORPH_HITMISS, kernel)
    return hitmiss


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
    kernel = np.array([[0, 1, 0], [1, -1, 1], [0, 1, 0]], dtype=np.int8)
    hitmiss_result = hit_or_miss(skeleton, kernel)
    display_image(hitmiss_result, "Hit-or-Miss Transform")


if __name__ == "__main__":
    main()
