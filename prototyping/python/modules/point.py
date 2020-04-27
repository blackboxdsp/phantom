#===============================================================================
class Point(object):

    #===========================================================================
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __str__(self) -> str:
        return f"<Point_obj: ({self.x:.03}, {self.y:.03})>"

    #===========================================================================
    def __eq__(self, other) -> bool:
        return self.x == other.x and self.y == other.y

    def __ge__(self, other) -> bool:
        return self.x >= other.x and self.y >= other.y

    def __gt__(self, other) -> bool:
        return self.x > other.x and self.y > other.y

    def __le__(self, other) -> bool:
        return self.x <= other.x and self.y <= other.y

    def __lt__(self, other) -> bool:
        return self.x < other.x and self.y < other.y