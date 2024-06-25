import cv2
import numpy as np
import matplotlib.pyplot as plt


def show_hist(image, title="Histograma"):
    if len(image.shape) == 2:  # Grayscale image
        plt.hist(image.ravel(), 256, [0, 256])
    else:
        color = ('b', 'g', 'r')
        for i, col in enumerate(color):
            histr = cv2.calcHist([image], [i], None, [256], [0, 256])
            plt.plot(histr, color=col)
            plt.xlim([0, 256])
    plt.title(title)
    plt.show()


def eq_hist(image):
    if len(image.shape) == 2:  # Grayscale image
        return cv2.equalizeHist(image)
    else:
        img_y_cr_cb = cv2.cvtColor(image, cv2.COLOR_BGR2YCrCb)
        y, cr, cb = cv2.split(img_y_cr_cb)
        y_eq = cv2.equalizeHist(y)
        img_y_cr_cb_eq = cv2.merge((y_eq, cr, cb))
        return cv2.cvtColor(img_y_cr_cb_eq, cv2.COLOR_YCrCb2BGR)


def specify_hist(image, reference):

    def calculate_cdf(hist):
        cdf = hist.cumsum()
        cdf_normalized = cdf * hist.max() / cdf.max()
        return cdf_normalized

    def create_lookup(cdf1, cdf2):
        lookup_table = np.zeros(256, dtype=np.uint8)
        for i in range(256):
            diff = np.abs(cdf1[i] - cdf2)
            lookup_table[i] = np.argmin(diff)
        return lookup_table

    if len(image.shape) == 2:  # Grayscale image
        hist_image, _ = np.histogram(image.flatten(), 256, [0, 256])
        hist_ref, _ = np.histogram(reference.flatten(), 256, [0, 256])

        cdf_image = calculate_cdf(hist_image)
        cdf_ref = calculate_cdf(hist_ref)

        lookup_table = create_lookup(cdf_image, cdf_ref)
        image_specified = lookup_table[image]

        return image_specified
    else:  # Color image
        image_specified = np.zeros_like(image)
        for i in range(3):  # Process each channel independently
            hist_image, _ = np.histogram(image[:, :, i].flatten(), 256,
                                         [0, 256])
            hist_ref, _ = np.histogram(reference[:, :, i].flatten(), 256,
                                       [0, 256])

            cdf_image = calculate_cdf(hist_image)
            cdf_ref = calculate_cdf(hist_ref)

            lookup_table = create_lookup(cdf_image, cdf_ref)
            image_specified[:, :, i] = lookup_table[image[:, :, i]]

        return image_specified


def rgb_para_hsv(image):
    return cv2.cvtColor(image, cv2.COLOR_BGR2HSV)


def hsv_para_rgb(image):
    return cv2.cvtColor(image, cv2.COLOR_HSV2BGR)


def transformar_para_pb(image):
    return cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)


def exibir_canais_de_cor(image):
    b, g, r = cv2.split(image)
    plt.figure(figsize=(15, 5))

    plt.subplot(1, 3, 1)
    plt.imshow(b, cmap='gray')
    plt.title('Canal Azul')

    plt.subplot(1, 3, 2)
    plt.imshow(g, cmap='gray')
    plt.title('Canal Verde')

    plt.subplot(1, 3, 3)
    plt.imshow(r, cmap='gray')
    plt.title('Canal Vermelho')

    plt.show()


def exibir_imagem_pb(image):
    # Check if the image is already grayscale
    if len(image.shape) == 2:
        image_ = image  # If grayscale, no conversion needed
    else:
        # Converter a imagem para preto e branco (escala de cinza)
        image_ = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Exibir a imagem em preto e branco
    plt.figure(figsize=(6, 6))
    plt.imshow(image_, cmap='gray')
    plt.title('Imagem em Preto e Branco')
    plt.axis('off')  # Ocultar os eixos
    plt.show()


def especificar_histogramas_e_mostrar(image, reference):
    # Especificar histograma
    specified_image = specify_hist(image, reference)

    # Mostrar histogramas e imagens
    plt.figure(figsize=(18, 6))

    plt.subplot(2, 3, 1)
    plt.imshow(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))
    plt.title('Imagem Original')
    plt.axis('off')

    plt.subplot(2, 3, 2)
    plt.imshow(cv2.cvtColor(reference, cv2.COLOR_BGR2RGB))
    plt.title('Imagem de Referência')
    plt.axis('off')

    plt.subplot(2, 3, 3)
    plt.imshow(cv2.cvtColor(specified_image, cv2.COLOR_BGR2RGB))
    plt.title('Imagem com Histograma Especificado')
    plt.axis('off')

    plt.subplot(2, 3, 4)
    show_hist(image, title="Histograma Original")

    plt.subplot(2, 3, 5)
    show_hist(reference, title="Histograma de Referência")

    plt.subplot(2, 3, 6)
    show_hist(specified_image, title="Histograma Especificado")

    plt.show()


# Carregar imagem
# image = cv2.imread('cookies.jpg')
#image = cv2.imread('donuts.jpg')
#image2 = cv2.imread('rio.jpg')

image2 = cv2.imread('donuts.jpg')
image = cv2.imread('rio.jpg')
imagepb = transformar_para_pb(image)
imagepb2 = transformar_para_pb(image2)

# Exibir histogramas originais
show_hist(image, title="Histograma Original")

# Equalizar histograma
image_eq = eq_hist(image)
show_hist(image_eq, title="Histograma Equalizado")

# Transformar para HSV e exibir canais de cor
image_hsv = rgb_para_hsv(image)
exibir_canais_de_cor(image_hsv)

# Transformar para preto e branco
image_pb = transformar_para_pb(image)
exibir_imagem_pb(image)
show_hist(image_pb, title="Histograma Preto e Branco")
show_hist(image_hsv, title="Histograma HSV")
# Especificar histogramas e mostrar resultados
#image_especify = specify_hist(image, image_pb)
#show_hist(image_especify, title="Histograma Especificado")
exibir_imagem_pb(imagepb2)
especificar_histogramas_e_mostrar(imagepb, imagepb2)
# Salvar e exibir resultados
# cv2.imwrite('resultado_equalizado.jpg', image_eq)
# cv2.imwrite('resultado_pb.jpg', image_pb)

# Discussão dos resultados
# print("Discussão dos Resultados:")
# print(
#     "1. Equalização do Histograma: A equalização distribui a intensidade de forma mais uniforme, melhorando o contraste."
# )
# print(
#     "2. Transformação para HSV: Facilita a manipulação dos componentes de cor."
# )
# print(
#     "3. Transformação para Preto e Branco: Permite análise de histogramas de intensidade em imagens coloridas."
# )

# Nota: Utilize imagens apropriadas e adicione mais análises conforme necessário.
