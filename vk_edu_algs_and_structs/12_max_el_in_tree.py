"""Реализация структуры данных бинарное дерево на Python"""


class Node:
    def __init__(self, data):
        self.value = data
        self.left = None
        self.right = None


class BinaryTree:
    def __init__(self, root):
        self.root = Node(root)

    def insert(self, value, current_node=None):
        if current_node is None:
            current_node = self.root

        if value > current_node.value:
            if current_node.right is None:
                current_node.right = Node(value)
            else:
                self.insert(value, current_node.right)
        elif value < current_node.value:
            if current_node.left is None:
                current_node.left = Node(value)
            else:
                self.insert(value, current_node.left)

    def min(self, node):
        while node.right is not None:
            node = node.right
        return node


n = int(input())
arr = list(map(int, input().split()))
tree = BinaryTree(arr[0])
for i in range(1, n):
    tree.insert(arr[i])
print(tree.min(tree.root).value)
