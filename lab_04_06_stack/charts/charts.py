import pandas as pd
import os, sys
import matplotlib.pyplot as plt


# Получение пути к текущему скрипту
script_path = os.path.abspath(__file__)
# Получение директории, в которой находится скрипт
script_directory = os.path.dirname(script_path)
data_directory = f"{script_directory}/../"


df_memory = pd.read_csv(f"{data_directory}data/memory.csv", delimiter=';')
print("Создание графика памяти")
fig = plt.figure(figsize=(10, 7))
ax = fig.add_subplot(111)
ax.plot(df_memory['size'], df_memory['static'], c='red', label="Размер стека на основе массива")
ax.plot(df_memory['size'], df_memory['list'], c='blue',label="Размер стека на основе списка")

ax.set_xlabel('Размер стека')
ax.set_ylabel('Объем занимаемой памяти (байты)')
ax.set_title('График зависимости памяти, занимаемой каждым методом, от размера')

plt.legend(loc="upper left")
plt.grid(True)
plt.savefig(f"{data_directory}/charts/memory_chart_1.svg")
plt.show()


speed_memory = pd.read_csv(f"{data_directory}data/speed.csv", delimiter=';')
print("Создание графика скорости")
fig = plt.figure(figsize=(10, 7))
ax = fig.add_subplot(111)

ax.plot(speed_memory['size'], speed_memory['static'], c='red', label="Скорость стека на основе массива")
ax.plot(speed_memory['size'], speed_memory['list'], c='blue',label="Скорость стека на основе списка")

ax.set_xlabel('Размер стека')
ax.set_ylabel('Скорость (наносекунды)')
ax.set_title('График зависимости скорости работы каждыого метода от размера')

plt.legend(loc="upper left")
plt.grid(True)
plt.savefig(f"{data_directory}/charts/speed_chart_1.svg")
plt.show()
