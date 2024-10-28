import os
import matplotlib.pyplot as plt
import pandas as pd
from mpl_toolkits.mplot3d import Axes3D

# Получение пути к текущему скрипту
script_path = os.path.abspath(__file__)
# Получение директории, в которой находится скрипт
script_directory = os.path.dirname(script_path)
data_directory = f"{script_directory}/../"


df_memory = pd.read_csv(f"{data_directory}memory.csv", delimiter=';')

print("Создание графика памяти")
# Создание 3D графика
fig = plt.figure(figsize=(10, 7))
ax = fig.add_subplot(111, projection='3d')

ax.scatter(df_memory['size'], df_memory['fill'], df_memory['def'], c='red', marker='o', label="Размер обычной матрицы")
ax.scatter(df_memory['size'], df_memory['fill'], df_memory['csc'], c='blue', marker='x', label="Размер матрицы в формате CSC")

ax.set_xlabel('Размер массива')
ax.set_ylabel('Процент заполнения')
ax.set_zlabel('Объем занимаемой памяти (байты)')
ax.set_title('График зависимости занимаемой памяти от размеров и процента заполнения массива')

plt.legend(loc="upper left")
plt.savefig(f"{data_directory}/charts/memory_chart.svg")
plt.show()

print("Создание графика скорости")
df_speed = pd.read_csv(f"{data_directory}speed.csv", delimiter=';')
# Создание 3D графика
fig = plt.figure(figsize=(10, 7))
ax = fig.add_subplot(111, projection='3d')

ax.scatter(df_speed['size'], df_speed['fill'], df_speed['def'], c='red', marker='o', label="Размер обычной матрицы")
ax.scatter(df_speed['size'], df_speed['fill'], df_speed['csc'], c='blue', marker='x', label="Размер матрицы в формате CSC")

ax.set_xlabel('Размер массива')
ax.set_ylabel('Процент заполнения')
ax.set_zlabel('Скорость выполнения (наносекунды)')
ax.set_title('График зависимости скорости алгоритма от размера и процента заполнения')

plt.legend(loc="upper left")
plt.savefig(f"{data_directory}/charts/speed_chart.svg")
plt.show()
