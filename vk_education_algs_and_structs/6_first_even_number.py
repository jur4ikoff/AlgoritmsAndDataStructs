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


n = int(input())
try:
    array = list(map(int, input().split()))
except Exception as e:
    # print(e)
    pass
stack = Stack()
for i in range(n):
    stack.push(array[i])

flag = False
while n > 0:
    cur = stack.pop()
    if cur % 2 == 0:
        print(cur)
        flag = True
        break
    n -= 1

if not flag:
    print(-1)
