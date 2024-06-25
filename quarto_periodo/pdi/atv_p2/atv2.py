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

    if len(image.shape) == 2:  # Grayscale image
        hist_image, _ = np.histogram(image.flatten(), 256, [0, 256])
        hist_ref, _ = np.histogram(reference.flatten(), 256, [0, 256])

        cdf_image = calculate_cdf(hist_image)
        cdf_ref = calculate_cdf(hist_ref)

        cdf_image_normalized = (cdf_image - cdf_image.min()) * 255 / (
            cdf_image.max() - cdf_image.min())
        cdf_image_normalized = cdf_image_normalized.astype('uint8')

        image_equalized = cdf_image_normalized[image]
        return image_equalized
    else:
        # Implementação para imagens coloridas
        raise NotImplementedError(
            "Especificação de histograma para imagens coloridas não está implementada."
        )


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
    # Converter a imagem para preto e branco (escala de cinza)
    image_pb = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Exibir a imagem em preto e branco
    plt.figure(figsize=(6, 6))
    plt.imshow(image_pb, cmap='gray')
    plt.title('Imagem em Preto e Branco')
    plt.axis('off')  # Ocultar os eixos
    plt.show()


# Carregar imagem
# image = cv2.imread('cookies.jpg')
# image = cv2.imread('donuts.jpg')
image = cv2.imread('rio.jpg')

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
