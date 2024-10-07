"""Реализация структуры данных - стэка"""


class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

    def __str__(self):
        return f"{self.data}->{self.next}"


class Stack(object):
    def __init__(self):
        self.top = None

    def __str__(self):
        return f"{self.top}"

    def push(self, data):
        new_node = Node(data)

        if not self.top:
            self.top = new_node
            return

        new_node.next = self.top
        self.top = new_node

    def pop(self):
        if not self.top:
            return

        top = self.top

        if self.top.next:
            self.top = self.top.next
        else:
            self.top = None

        return top.data


def test():
    a = Stack()
    a.push(1)
    for i in range(10):
        a.push(i)

    print(a)
    a.pop()
    print(a)


if __name__ == "__main__":
    test()
