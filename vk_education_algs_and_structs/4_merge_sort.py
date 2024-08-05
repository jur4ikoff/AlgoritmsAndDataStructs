n = int(input())
array = list(map(int, input().split()))


def merge(array: int, left: int, mid: int, right: int):
    # Нисходящая сортировка присваиваением
    sub_array_one = mid - left + 1
    sub_array_two = right - mid

    # create temp array
    left_array = [0] * sub_array_one
    right_array = [0] * sub_array_two

    for i in range(sub_array_one):
        left_array[i] = array[left + i]
    for i in range(sub_array_two):
        right_array[i] = array[mid + i + 1]

    index_array_one, index_array_two, index_of_merged = 0, 0, left

    while index_array_one < sub_array_one and index_array_two < sub_array_two:
        if left_array[index_array_one] <= right_array[index_array_two]:
            array[index_of_merged] = left_array[index_array_one]
            index_array_one += 1
        else:
            array[index_of_merged] = right_array[index_array_two]
            index_array_two += 1
        index_of_merged += 1

    while index_array_one < sub_array_one:
        array[index_of_merged] = left_array[index_array_one]
        index_array_one += 1
        index_of_merged += 1

    while index_array_two < sub_array_two:
        array[index_of_merged] = right_array[index_array_two]
        index_array_two += 1
        index_of_merged += 1


def merge_sort(array: int, begin: int, end: int):
    if begin >= end:
        return

    mid = begin + (end - begin) // 2
    merge_sort(array, begin, mid)
    merge_sort(array, mid + 1, end)
    merge(array, begin, mid, end)


merge_sort(array, 0, n - 1)
print(*array)
