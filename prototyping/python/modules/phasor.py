#===============================================================================
import matplotlib.pyplot as plt

from .point import Point

#===============================================================================
class Phasor(object):

    #===========================================================================
    def __init__(self, inflections: list):
        self.set_inflections(inflections)

    def __str__(self) -> str:
        return f"<Phasor_obj: inflections = {[str(inflection) for inflection in self.inflections]}>\n"

    #===========================================================================
    def get_inflection_count(self) -> int:
        return self.inflection_count

    def get_inflections(self) -> list:
        return self.inflections

    def set_inflection(self, index: int, inflection: Point) -> None:
        self.inflections[index] = inflection
        self.sort_inflections()

    def set_inflections(self, inflections: list) -> None:
        self.inflections = inflections
        self.inflection_count = len(inflections)
        self.sort_inflections()

    def sort_inflections(self) -> None:
        self.inflections.sort(key = lambda point: point.x)

    def reset_inflections(self) -> None:
        self.inflections = []
        self.inflection_count = 0

    #===========================================================================
    def evaluate(self, phase: float) -> float:
        p1, p2 = self.get_surrounding_inflections(phase)

        m, b = self.compute_line(p1, p2)
        return m * phase + b

    def get_surrounding_inflections(self, phase: float) -> Point:
        points = self.inflections + [Point(0.0, 0.0), Point(1.0, 1.0)] 
        points.sort(key = lambda point: point.x)

        low_index = 0
        for point in points[1:-2]:
            if phase > point.x:
                low_index += 1

        return points[low_index], points[low_index + 1]

    def compute_line(self, point1: Point, point2: Point) -> float:
        slope = point2.y - point1.y / point2.x - point1.x
        y_int = point2.y - slope * point2.x
        return slope, y_int

    #===========================================================================
    def display(self, show: bool = False) -> None:
        plt.title("Phasor")

        plt.xlabel("Input Phase")
        plt.xlim((0.0, 1.0))

        plt.ylabel("Output Phase")
        plt.ylim((0.0, 1.0))

        points = self.inflections + [Point(0.0, 0.0), Point(1.0, 1.0)] 
        points.sort(key = lambda point: point.x)

        x = [point.x for point in points]
        y = [point.y for point in points]

        plt.plot(x, y, "C2")

        if show:
            plt.show()

    def print(self) -> None:
        print(self)