"""Дан массив целых чисел. Необходимо вернуть элемент, который встречается больше половины раз.
Если такого элемента нет, возвращайте -1"""

n = int(input())
array = list(map(int, input().split()))

elements = {}

for i in range(n):
    if array[i] not in elements:
        elements[array[i]] = 1
    else:
        elements[array[i]] += 1

max_key = max(elements, key=elements.get)
max_value = elements[max_key]

if max_value > n // 2:
    print(max_key)
else:
    print(-1)
