# По хорошему задачу решать через linked array

n = int(input())
array = list(map(int, input().split()))

zero_count: int = 0
i = 0
while i != n:
    if array[i] == 0:
        zero_count += 1
        array.pop(i)
        i -= 1
        n -= 1
    else:
        i += 1

array = array + [0] * zero_count
print(*array)
