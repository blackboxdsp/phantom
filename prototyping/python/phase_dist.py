#===============================================================================
import math

import matplotlib.pyplot as plt
import numpy as np

#===============================================================================
class Point(object):
    def __init__(self, x = 0.0, y = 0.0):
        self.x = x
        self.y = y

    def __str__(self):
        return f"({self.x}, {self.y})"

#===============================================================================
class Phasor(object):
    def __init__(self, inflections = []):
        self.inflections = inflections + [Point(0.0, 0.0), Point(1.0, 1.0)]
        self.phase = 0.0

    def __str__(self):
        return f"Inflections : {[str(point) for point in self.inflections]}\nPhase : {self.phase}"

    def add_inflection(self, point):
        if isinstance(point, Point):
            self.inflections.append(Point(point.x, point.y))
        self.order_inflections()

    def order_inflections(self):
        self.inflections.sort(key = lambda p: p.x)

    def evaluate(self):
        function_idx = 0
        for inflection in self.inflections[1:-2]:
            if self.phase > inflection.x:
                function_idx += 1

        p1 = self.inflections[function_idx]
        p2 = self.inflections[function_idx + 1]

        m, b = self.compute_line(p1, p2)

        result = m * self.phase + b

        print(f"Input phase : {self.phase}")
        print(f"Output phase : {result}\n")

        return result

    def compute_line(self, p1, p2):
        slope = p2.y - p1.y / p2.x - p1.x
        y_int = p2.y - slope * p2.x
        return slope, y_int
        
    def display(self):
        print(self)
        
        x = [point.x for point in self.inflections]
        y = [point.y for point in self.inflections]

        plt.plot(x, y, "C2")
        plt.show()

#===============================================================================
def plt_init():
    plt.title("Phasor Table")

    plt.xlabel("Input Phase")
    plt.xlim([0.0, 1.0])

    plt.ylabel("Output Phase")
    plt.ylim([0.0, 1.0])

    plt.plot([0.0, 1.0], [0.0, 1.0], "k--")

#===============================================================================
def main():
    plt_init()

    phasor = Phasor()

    phasor.add_inflection(Point(0.1, 0.6))
    phasor.add_inflection(Point(0.6, 0.9))
    for i in range(1, 100, 10):
        phasor.phase = i / 100
        phasor.evaluate()

    phasor.display()
    
if __name__ == "__main__":
    main()