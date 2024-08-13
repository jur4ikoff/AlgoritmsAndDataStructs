"""
Дан отсортированный по возрастанию массив целых чисел и заданное число.
Заданное число может и не находиться в массиве.
Тогда необходимо вернуть предполагаемый индекс, где мог бы находится элемент.
Другими словами, найдите правильное место для вставки элемента. Если же число есть, то возвращаем его индекс.
"""


def search_insert(nums, target):
    left, right = 0, len(nums)

    while left < right:
        mid = (left + right) // 2

        if array[mid] == target:
            return mid

        if nums[mid] < target:
            left = mid + 1
        else:
            right = mid

    return left


n = int(input())
array = list(map(int, input().split()))
element = int(input())
index = search_insert(array, element)
print(index)
