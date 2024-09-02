def search_index(items, k) -> int:
    for i in range(len(items)):
        if items[i] == k:
            return i
