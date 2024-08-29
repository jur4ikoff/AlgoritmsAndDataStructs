"""Реализация красно-черного дерева на Python"""


class Node:
    def __init__(self, data):
        self.data = data
        self.parent = None
        self.left = None
        self.right = None
        self.color = 1  # 0 - black 1 - red


class RedBlackTree:
    def __init__(self):

        # Создаем черный корень
        self.NULL = Node(0)
        self.NULL.color = 0
        self.NULL.left = self.NULL.right = None
        self.root = self.NULL

    def insert(self, key):
        """Вставка нового узла"""
        pass

    def search(self, node, key):
        """Поиск узла по значению"""
        pass

    def delete_node(self, node, key):
        """Удаления узла"""
        pass

    def minimum(self, node):
        pass

    def maximum(self, node):
        pass

    def left_rotate(self, x):
        pass

    def right_rotate(self, x):
        pass


def test():
    pass


if __name__ == "__main__":
    test()

