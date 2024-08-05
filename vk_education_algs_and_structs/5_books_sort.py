def merge_sort(books):
    if len(books) <= 1:
        return books
    
    mid = len(books) // 2
    left_half = merge_sort(books[:mid])
    right_half = merge_sort(books[mid:])
    
    return merge(left_half, right_half)

def merge(left, right):
    sorted_books = []
    i = j = 0
    
    while i < len(left) and j < len(right):
        # Сравниваем по году издания и затем по названию
        if (left[i][2], left[i][1]) < (right[j][2], right[j][1]):
            sorted_books.append(left[i])
            i += 1
        else:
            sorted_books.append(right[j])
            j += 1
    
    # Добавляем оставшиеся элементы
    sorted_books.extend(left[i:])
    sorted_books.extend(right[j:])
    
    return sorted_books


n = int(input().strip())
books = []

for _ in range(n):
    line = input().strip()
    # Разделяем строку на части; ISBN - первая часть, название - остаток до года, год - последняя часть
    parts = line.split('"')
    isbn = parts[0].strip()
    title = parts[1].strip()
    year = int(parts[2].strip())
    
    books.append((isbn, title, year))

# Сортируем книги
sorted_books = merge_sort(books)

# Выводим отсортированные книги
for book in sorted_books:
    print(f'{book[0]} "{book[1]}" {book[2]}')