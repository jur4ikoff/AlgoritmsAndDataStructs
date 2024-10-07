n = int(input())
array = list(map(int, input().split()))


def insection_sort(array: list, n: int):

    for i in range(1, n):
        key = array[i]
        j = i - 1

        while j >= 0 and array[j] > key:
            array[j + 1] = array[j]
            j -= 1

        array[j + 1] = key

insection_sort(array, n)
print(*array)