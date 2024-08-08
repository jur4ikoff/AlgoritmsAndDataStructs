"""Реалазация очереди на Python"""


class Node:
    def __init__(self, data=None):
        self.data = data
        self.prev = None
        self.next = None

    def __str__(self):
        return f"{self.data}->{self.next}"


class Queue:
    def __init__(self):
        self.head = Node()
        self.tail = Node()

        self.head.next = self.tail  # При инициализации начало указывает на конец
        self.tail.prev = self.head
        self.size = 0

    def push(self, data):
        new_node = Node(data)
        new_node.next = self.head.next
        new_node.prev = self.head

        self.head.next.prev = new_node
        self.head.next = new_node
        self.size += 1

    def pop(self):
        if self.head.prev == self.tail:
            return

        pop_result = self.tail.prev
        self.tail.prev = pop_result.prev
        pop_result.prev.next = pop_result.next

        pop_result.next = None
        pop_result.prev = None

        self.size -= 1
        return pop_result.data


print(a)
