import numpy as np

def generate_random_matrix(rows, cols, low=0, high=20):
    """
    Генерирует матрицу случайных чисел.

    :param rows: Количество строк в матрице
    :param cols: Количество столбцов в матрице
    :param low: Минимальное значение случайного числа (включительно)
    :param high: Максимальное значение случайного числа (не включительно)
    :return: Сгенерированная матрица случайных чисел
    """
    return np.random.randint(low, high, size=(rows, cols))

def save_matrix_to_file(matrix, filename):
    """
    Записывает матрицу в текстовый файл.

    :param matrix: Матрица, которую нужно записать
    :param filename: Имя файла для записи
    """
    with open(filename, 'w') as f:
        for row in matrix:
            # Преобразуем строку в строку с разделёнными пробелами числами
            row_str = ' '.join(map(str, row))
            f.write(row_str + '\n')

# Задаем размеры матрицы
rows = 25   # Количество строк
cols = 25   # Количество столбцов

# Генерируем матрицу
random_matrix = generate_random_matrix(rows, cols)

# Указываем имя файла для записи
filename = "random_matrix.txt"

# Сохраняем матрицу в файл
save_matrix_to_file(random_matrix, filename)

print(f"Матрица успешно записана в файл: {filename}")