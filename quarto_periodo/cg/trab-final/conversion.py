import os
import shutil

# Diretório onde os arquivos originais estão localizados
source_dir = 'D:\Downloads\Animacao\Boy\Animations\Running'
# Diretório onde os arquivos renomeados serão salvos
destination_dir = 'D:\Downloads\Animacao\Boy\Animations\Running1'

# Verifique se o diretório de destino existe, caso contrário, crie-o
if not os.path.exists(destination_dir):
    os.makedirs(destination_dir)

# Loop para renomear e copiar arquivos
for i in range(500):
    # Nome do arquivo original (assumindo que estão em formato running0000.obj até running0024.obj)
    original_file = os.path.join(source_dir, f'running{i+1:04d}.obj')
    # Nome do novo arquivo (em formato running1.obj até running25.obj)
    new_file = os.path.join(destination_dir, f'running{i+1}.obj')

    # Copiar e renomear o arquivo
    shutil.copyfile(original_file, new_file)

print("Arquivos renomeados e copiados com sucesso.")
