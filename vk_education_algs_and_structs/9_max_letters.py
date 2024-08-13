"""Есть строка с многократным повторением разных букв.
Надо понять какое максимальное количество повторений встречается в строке.
Используя хеш таблицу, записывайте пару буква - количество вхождений в строку
"""

string = input()
hash_table = {}

for char in string:
    if char not in hash_table:
        hash_table[char] = 1
    else:
        hash_table[char] += 1

max_key = max(hash_table, key=hash_table.get)
max_value = hash_table[max_key]
print(max_value)
# abababav
