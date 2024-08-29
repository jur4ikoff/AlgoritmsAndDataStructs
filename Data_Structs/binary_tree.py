"""Реализация структуры данных бинарное дерево на Python"""


class Node:
    def __init__(self, data):
        self.value = data
        self.left = None
        self.right = None
        self.parent = None
        self.bf = 0


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

    def search(self, to_find, node=-1):
        if node == -1:
            node = self.root

        if node is None:
            return False

        if node.value == to_find:
            return True

        if node.value > to_find:
            return self.search(to_find, node.left)
        else:
            return self.search(to_find, node.right)

    def min(self, node):
        while node.left is not None:
            node = node.left
        return node

    def max(self, node):
        while node.right is not None:
            node = node.right
        return node

    def delete(self, key, node=-1):
        if node == -1:
            node = self.root

        if node is None:
            return node

        if key < node.value:
            node.left = self.delete(key, node.left)
        elif key > node.value:
            node.right = self.delete(key, node.right)
        else:
            if node.left is None and node.right is None:
                node = None
            elif node.left is None:
                node = node.right
            elif node.right is None:
                node = node.left
            else:
                min_value = self.min(node.right)
                node.value = min_value.value
                node.right = self.delete(min_value.value, node.right)

        return node

    def breadth_tree(self, node=-1):
        """Обход в ширину"""
        if node == -1:
            node = self.root

        root = [node]
        result = []

        while root:
            queue = []
            for current in root:
                result.append(current.value)
                if current.left:
                    queue.append(current.left)
                if current.right:
                    queue.append(current.right)
            root = queue

        return result

    def print_tree(self, node=False):
        """LNR Обход в глубину"""
        if node == False:
            node = self.root

        if node is None:
            return

        self.print_tree(node.left)
        print(node.value, end=' ')
        self.print_tree(node.right)
        return


tree = BinaryTree(16)
tree.insert(11)
tree.insert(18)
tree.insert(9)
tree.insert(13)
tree.insert(17)
tree.insert(21)
tree.print_tree()
print()

print(tree.breadth_tree())
