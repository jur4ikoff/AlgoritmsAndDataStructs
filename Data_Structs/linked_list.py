"""
Реализация односвязного списка на Python. 
"""


class Node(object):
    def __init__(self, data):
        self.data = data
        self.next = None

    def __str__(self):
        # Для красивого вывода с принта
        return f"{self.data}->{self.next}"


class LinkedList(object):
    def __init__(self):
        self.head = None

    def append_front(self, value):
        """Вставка в начала связанного списка"""
        new_node = Node(value)

        if not self.head:
            self.head = new_node
            return

        new_node.next = self.head
        self.head = new_node

    def append(self, value):
        """Вставка в конец списка"""

        new_node = Node(value)
        if not self.head:
            self.head = new_node
            return

        cur_node = self.head
        while cur_node.next:
            cur_node = cur_node.next

        cur_node.next = new_node

    def insert(self, search, data):
        """Вставка в позицию индекс"""
        new_node = Node(data)
        cur = self.head

        while cur:
            if cur.data == search:
                break
            cur = cur.next

        if cur is None:
            raise "Value not in LinkedList"

        new_node.next = cur.next
        cur.next = new_node

    def len(self):
        """Функция возвращает длину списка"""
        count = 0
        temp = self.head

        while temp:
            count += 1
            temp = temp.next

        return count

    def __str__(self):
        return f"{self.head}"


if __name__ == "__main__":
    linked_list = LinkedList()
    temp = Node(1)
    linked_list.head = temp

    for i in range(2, 15):
        temp.next = Node(i)
        temp = temp.next

    # 1->2->3->4->5->6->7->8->9->10->11->12->13->14->None

    print(linked_list.append_front(3))
    # print(linked_list) 3->1->2->3->4->5->6->7->8->9->10->11->12->13->14->None

    print(linked_list.append(1212))
    # print(linked_list) 3->1->2->3->4->5->6->7->8->9->10->11->12->13->14->1212->None

    print(linked_list.insert(4, 32))
    # print(linked_list) 3->1->2->3->4->32->5->6->7->8->9->10->11->12->13->14->1212->None
