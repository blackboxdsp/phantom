import math

import matplotlib.pyplot as plt
import numpy as np

class Phasor(object):
    def __init__(self, inflections = []):
        self.inflections = inflections
        self.phase_idx = 0

    def __str__(self):
        return f"Inflections : {self.inflections}\nPhase Index : {self.phase_idx}"
        
    def print(self):
        print(self)
        x, y = [0], [0]

        for inflection in self.inflections:
            x.append(inflection[0])
            y.append(inflection[1])

        x.append(1)
        y.append(1)

        plt.plot(x, y, "C2")
        plt.show()

def plt_init():
    plt.title("Phasor Table")

    plt.xlabel("Input Phase")
    plt.ylabel("Output Phase")

    plt.xlim([0.0, 1.0])
    plt.ylim([0.0, 1.0])

    plt.plot([0.0, 1.0], [0.0, 1.0], "k--")

def main():
    plt_init()

    phasor = Phasor([(0.1, 0.5)]) 
    phasor.print()
    
if __name__ == "__main__":
    main()