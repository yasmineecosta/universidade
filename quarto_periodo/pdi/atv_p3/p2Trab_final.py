import cv2
from skimage import io
from matplotlib import pyplot as plt
import numpy as np

# Carregar a imagem
image_path = 'Tarb.Final-2.png'
image = io.imread(image_path)

# Verificar se a imagem é RGB e converter se necessário
if image.ndim == 3 and image.shape[2] == 3:
    gray_image = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)
else:
    gray_image = image

# Equalização de histograma
equalized_image = cv2.equalizeHist(gray_image)

# Aplicar binarização
_, binary_image = cv2.threshold(equalized_image, 0, 255,
                                cv2.THRESH_BINARY + cv2.THRESH_OTSU)

# Aplicar operações morfológicas para remover ruídos e preencher buracos
kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5, 5))
cleaned_image = cv2.morphologyEx(binary_image,
                                 cv2.MORPH_CLOSE,
                                 kernel,
                                 iterations=2)

# Detectar bordas usando o Canny
edges = cv2.Canny(cleaned_image, 100, 200)

# Encontrar contornos das hemácias usando as bordas detectadas
contours, _ = cv2.findContours(edges, cv2.RETR_EXTERNAL,
                               cv2.CHAIN_APPROX_SIMPLE)

# Desenhar contornos encontrados
segmented_image = cv2.drawContours(image.copy(), contours, -1, (255, 0, 0), 2)

# Calcular a área total das hemácias com base nas bordas
hemacia_area = sum(cv2.contourArea(c) for c in contours)
total_area = gray_image.shape[0] * gray_image.shape[
    1]  # Usar a imagem em escala de cinza para área total
percent_area = (hemacia_area / total_area) * 100

# Exibir resultados
fig, axes = plt.subplots(2, 2, figsize=(10,5))
axes[0, 0].imshow(image)
axes[0, 0].set_title('Imagem Original')
axes[1, 0].imshow(equalized_image, cmap='gray')
axes[1, 0].set_title('Equalização de Histograma')
axes[0, 1].imshow(cleaned_image, cmap='gray')
axes[0, 1].set_title('Imagem Limpa')
axes[1, 1].imshow(segmented_image)
axes[1, 1].set_title('Segmentação das Hemácias')

for ax in axes.flat:
    ax.axis('off')

plt.tight_layout()
plt.show()
print(f"Área total das hemácias: {hemacia_area} pixels")
