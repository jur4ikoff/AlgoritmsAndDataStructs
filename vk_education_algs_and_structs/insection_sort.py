a = [10, 1, 2, 232, 1, 4]


def insection_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1

        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key

    return  arr

print(*insection_sort(a))
