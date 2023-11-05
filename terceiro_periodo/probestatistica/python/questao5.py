import statistics
forca_ruptura = [49, 52, 51, 53, 55]
media_forca = statistics.mean(forca_ruptura)
desvio_padrao_forca = statistics.stdev(forca_ruptura)
cv_forca = (desvio_padrao_forca / media_forca) * 100

print("Coeficiente de Variação para força de ruptura:", cv_forca)

precipitacao_chuva = [5.5, 4.5, 4, 6]
media_chuva = statistics.mean(precipitacao_chuva)
desvio_padrao_chuva = statistics.stdev(precipitacao_chuva)
cv_chuva = (desvio_padrao_chuva / media_chuva) * 100

print("Coeficiente de Variação para precipitação de chuva:", cv_chuva)

print("Tendo calculado ambos os coeficientes de variação, o coeficiente mais disperso é:")
if cv_chuva<cv_forca:
    print("Da força de ruptura")
    print(cv_forca)
else:
    print("Da precipitação da chuva")
    print(cv_chuva)