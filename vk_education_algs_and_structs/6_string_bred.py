string = input()


def is_repeat(string):
    n = len(string)
    for i in range(n - 1):
        if string[i] == string[i + 1]:
            return True, i

    return False, -1


while (is_repeat(string)[0]):
    index = is_repeat(string)[1]
    # print(index)
    string = string[:index] + string[index + 2:]

print(string)
