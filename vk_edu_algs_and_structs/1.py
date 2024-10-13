n: int = int(input())
array: list = list(map(int, input().split()))
element: int = int(input())

count: int = 0
for i in range(n):
    if array[i] != element:
        count += 1

print(count)
