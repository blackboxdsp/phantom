#===============================================================================
import math
import random

import matplotlib.pyplot as plt
import numpy as np

#===============================================================================
class Point(object):
    def __init__(self, x = 0.0, y = 0.0):
        self.x = x
        self.y = y

    def __str__(self):
        return f"({self.x:.02}, {self.y:.02})"

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __gt__(self, other):
        return self.x > other.x and self.y > other.y

    def __lt__(self, other):
        return self.x < other.x and self.y < other.y

#===============================================================================
class Wavetable(object):
    def __init__(self, table_size = 2048, map_func = math.sin):
        self.table_size = table_size
        self.table = []
        self.map_func = map_func

    def __str__(self):
        return f"Wavetable ({self.table_size}) -> {self.map_func}, [{self.table[0]}, ..., {self.table[-1]}]"

    def apply_phasor(self, phasor):
        for i in range(self.table_size + 1):
            phase = float(i / self.table_size)
            value = self.map_func(phasor.evaluate(phase) * math.pi * 2.0) / 2.0 + 0.5
            self.table[i] = Point(phase, value)

    def create_table(self):
        self.table = []
        for i in range(self.table_size + 1):
            phase = float(i / self.table_size)
            value = self.map_func(phase * math.pi * 2.0) / 2.0 + 0.5
            self.table.append(Point(phase, value))

    def display(self, show = False):
        plt.xlabel("Phase")
        plt.ylabel("Amplitude")
        plt.plot([0.0, 1.0], [0.0, 1.0], "k--")

        x = [point.x for point in self.table]
        y = [point.y for point in self.table]

        plt.plot(x, y, "C4")

        if show:
            plt.show()

    def reset_table(self):
        self.create_table()

#===============================================================================
class Phasor(object):
    def __init__(self, inflections = []):
        self.inflections = []

        for point in inflections:
            if point > Point(0.0, 0.0) and point < Point(1.0, 1.0):
                self.inflections = inflections + [Point(0.0, 0.0), Point(1.0, 1.0)]

        self.inflection_count = len(self.inflections) - 2
        self.order_inflections()

    def __str__(self):
        return f"Phasor ({self.inflection_count}) -> {[str(point) for point in self.inflections[1:-1]]}"

    def add_inflection(self, point):
        if isinstance(point, Point):
            self.inflections.append(Point(point.x, point.y))
            self.inflection_count += 1
        self.order_inflections()

    def compute_line(self, p1, p2):
        slope = (p2.y - p1.y) / (p2.x - p1.x)
        y_int = p2.y - slope * p2.x
        return slope, y_int
        
    def display(self, show = False):
        plt.title(f"Phasor Table (inflections = {self.inflection_count})")
        plt.xlabel("Input Phase")
        plt.ylabel("Output Phase")
        plt.plot([0.0, 1.0], [0.0, 1.0], "k--")

        print(self)
        
        x = [point.x for point in self.inflections]
        y = [point.y for point in self.inflections]

        plt.plot(x, y, "C2")
        if show:
            plt.show()

    def evaluate(self, phase):
        function_idx = 0
        for inflection in self.inflections[1:-1]:
            if phase > inflection.x:
                function_idx += 1

        p1 = self.inflections[function_idx]
        p2 = self.inflections[function_idx + 1]

        m, b = self.compute_line(p1, p2)

        return m * phase * phase + b

    def randomize(self):
        self.inflections = [Point(0.0, 0.0), Point(1.0, 1.0)]

        for i in range(self.inflection_count):
            x = random.uniform(0.0, 1.0)
            y = random.uniform(0.0, 1.0)

            p = Point(x, y)

            self.add_inflection(p)
            self.order_inflections()

        self.inflection_count = len(self.inflections) - 2

    def order_inflections(self):
        self.inflections.sort(key = lambda p: p.x)

#===============================================================================
def main():
    wavetable = Wavetable(table_size = 2048, map_func = math.sin)
    wavetable.create_table()

    inflection_count = eval(input("Enter inflection count: "))

    for i in range(1, inflection_count + 1):
        phasor = Phasor([Point(random.uniform(0.0, 1.0), random.uniform(0.0, 1.0)) for _ in range(i)])
        phasor.display(show = False)

        wavetable.apply_phasor(phasor)
        wavetable.display(show = True)
    
if __name__ == "__main__":
    main()