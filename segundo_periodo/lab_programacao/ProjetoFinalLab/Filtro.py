from PIL import ImageFilter

class Filtro:
    def create(self, filtro, image):
        if filtro == 1:
            return image.convert("L")
        if filtro == 2:
            return image.convert('1')
        if filtro == 3:
            return image.filter(ImageFilter.FIND_EDGES)
        if filtro == 4:
            return image.filter(ImageFilter.SMOOTH)
        if filtro == 5:
            return image.filter(ImageFilter.BLUR)
        if filtro == 6:
            return image.filter(ImageFilter.DETAIL)
        if filtro == 7:
            return image.filter(ImageFilter.CONTOUR)