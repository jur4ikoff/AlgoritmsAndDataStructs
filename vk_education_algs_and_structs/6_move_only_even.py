# Дан не отсортированный массив целых чисел. Необходимо перенести в начало массива все четные числа. При этом последовательность четных чисел должна быть сохранена. То есть если 8 стояла после 6, то после переноса в начало, она по-прежнему должна стоять после 6.

n = int(input())
array = list(map(int, input().split()))


def move(array: list, n: int):
    even_index = 0

    for i in range(n):
        if array[i] % 2 == 0:
            array[even_index], array[i] = array[i], array[even_index]
            even_index += 1

    return array

array = move(array, n)
print(*array)
