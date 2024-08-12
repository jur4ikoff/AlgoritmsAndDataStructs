def binary_search(array, n, search):
    left, right = 0, n - 1
    while left < right:
        mid = (left + right) // 2

        if array[mid] == search:
            return True

        if array[mid] < search:
            left = mid + 1
        else:
            right = mid - 1

    return False


n = int(input())
array = list(map(int, input().split()))
to_search = int(input())

res = binary_search(array, n, to_search)
if (res):
    print("true")
else:
    print("false")
