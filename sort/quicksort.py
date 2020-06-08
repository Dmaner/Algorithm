class a:
    def __init__(self):
        self.x = 0
    
    @property
    def x(self):
        return self.x

b = a()
b.x = 3
print(b.x)