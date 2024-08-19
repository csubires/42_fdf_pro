# ---------------------------------------------
# Filename: tes.py
# Version: 1.0
# By: CSUBIRES <j3xuz_cobmetal88@hotmail.com>
# Created: 2024/08/03 09:13:01 by CSUBIRES
# Updated: 2024/08/03 09:13:01 by CSUBIRES
# Description: .
# ---------------------------------------------

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Dimensiones de la matriz
ancho_matriz = 50
alto_matriz = 50

# Crear una matriz ejemplo con valores de altura
matriz = np.random.rand(alto_matriz, ancho_matriz) * 10  # Altura aleatoria

# Radio de la esfera
r = 1.0

# Inicializar las listas para almacenar los puntos 3D
X_esfera = []
Y_esfera = []
Z_esfera = []

# Convertir cada punto en el plano a un punto en la esfera
for y in range(alto_matriz):
    for x in range(ancho_matriz):
        # Normalizar coordenadas
        x_norm = 2 * x / (ancho_matriz - 1) - 1
        y_norm = 2 * y / (alto_matriz - 1) - 1

        # Calcular ángulos esféricos
        theta = x_norm * np.pi  # Longitud
        phi = y_norm * (np.pi / 2)  # Latitud

        # Calcular coordenadas cartesianas en la esfera
        X = r * np.cos(phi) * np.cos(theta)
        Y = r * np.cos(phi) * np.sin(theta)
        Z = r * np.sin(phi)

        # Almacenar las coordenadas calculadas
        X_esfera.append(X)
        Y_esfera.append(Y)
        Z_esfera.append(Z)

# Convertir las listas en arrays de NumPy
X_esfera = np.array(X_esfera)
Y_esfera = np.array(Y_esfera)
Z_esfera = np.array(Z_esfera)

# Visualizar la esfera resultante
fig = plt.figure(figsize=(8, 8))
ax = fig.add_subplot(111, projection='3d')

# Graficar los puntos de la esfera
ax.scatter(X_esfera, Y_esfera, Z_esfera, c='b', marker='o')

# Ajustes del gráfico
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_title('Proyección del Plano a una Esfera')

plt.show()
