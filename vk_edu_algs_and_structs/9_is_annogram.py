"""
На вход функции подается две строки a и b
Используя хеш таблицу, попытайтесь определить, является ли строка b анаграммой к строке a.
Анаграмма – это слово или фраза, образованные путем перестановки букв другого слова или фразы,
как правило, используя все исходные буквы ровно один раз
"""


def separate_on_letters(string):
    data = {}

    for char in string:
        if char not in data:
            data[char] = 1
        else:
            data[char] += 1

    return data


string1, string2 = input().replace('"', '').split()
data1 = separate_on_letters(string1)
data2 = separate_on_letters(string2)

if data1 == data2:
    print('true')
else:
    print('false')
