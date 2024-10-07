n = int(input())
array = list(map(int, input().split()))
to_search = int(input())


def binary_search(arr, low, high, x):
    while low < high:
        mid = (high + low) // 2

        if arr[mid] == x:
            return mid - 1, mid + 1

        if arr[mid] < x:
            low = mid + 1

        else:
            high = mid - 1

    return high, low


def exp_search(arr, n, x):
    if arr[0] >= x:
        return 0, 1

    i = 1
    while i < n - 1 and arr[i] < x:
        if arr[i] == x:
            return i - 1, i + 1
        i *= 2
        if i > n - 1:
            i = n - 1

    return binary_search(arr, i // 2, i, x)


low, high = exp_search(array, n, to_search)
print(low, high)
