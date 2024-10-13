"""Дана последовательность целых чисел и число K. Найдите максимальное произведение подпоследовательности размером K."""

n = int(input())
arr = list(map(int, input().split()))
k = int(input())

l, r = 0, k - 1
maxx = -10 * 8
while r < n:
    cur_eq = 1
    for i in range(l, r + 1):
        cur_eq *= arr[i]
    maxx = max(maxx, cur_eq)
    cur_eq = 1
    l += 1
    r += 1

print(maxx)
