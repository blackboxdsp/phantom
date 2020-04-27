#===============================================================================
import math
import random

import matplotlib.pyplot as plt
import numpy as np
import wavio

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

    def get_point_in_table(self, index):
        if index >= 0 and index < len(self.table):
            return self.table[index]

    def reset_table(self):
        self.create_table()

    def write_file(self, frequency = 220.0, rate = 44100, time = 1.0):
        max_num_samples = round(rate * time)
        sample_index = 0
        samples = []

        phase_delta = (frequency / rate) * math.pi * 2.0
        phase = 0
        while(sample_index < max_num_samples):
            sample_point = self.get_point_in_table(int(self.table_size * phase) % self.table_size)
            samples.append(sample_point.y)

            sample_index += 1

            phase = (phase + phase_delta) % (math.pi * 2.0)

        plt.plot(samples[:rate], "C2")
        plt.show()

        filename = "phase-distortion.wav"
        wavio.write(filename, np.array(samples), rate, sampwidth = 3)
        print(f"Audio exported as \"{filename}\"")

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
    frequency = 220.0
    rate = 44100
    time = 3.0

    wavetable = Wavetable(table_size = 2048, map_func = math.sin)
    wavetable.create_table()

    inflection_count = eval(input("Enter inflection count: "))
    inflection_points = [Point(random.uniform(0.0, 1.0), random.uniform(0.0, 1.0)) for _ in range(inflection_count)]

    phasor = Phasor(inflection_points)
    phasor.display(show = True)

    wavetable.apply_phasor(phasor)
    wavetable.display(show = True)
    wavetable.write_file(frequency, rate, time)
    
if __name__ == "__main__":
    main()