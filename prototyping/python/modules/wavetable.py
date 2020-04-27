#===============================================================================
import math

from .buffer import Buffer
from .phasor import Phasor
from .sample import Sample

#===============================================================================
class Wavetable(object):

    #===========================================================================
    def __init__(self, table_size):
        self.table_size = table_size
        self.wavetable = Buffer(table_size)

        self.phase = 0.0
        self.phase_delta = 0.0

    def __str__(self) -> str:
        return f"<Wavetable_obj: size = {self.table_size}, wavetable = {self.wavetable}>\n"

    #===========================================================================
    def fill_table(self) -> None:
        for i in range(self.table_size):
            phase = float(i / self.table_size)
            value = math.sin(phase * math.pi * 2.0)

            self.wavetable.set_sample(i, Sample(value))

    def get_next_sample(self, phasor: Phasor = None) -> Sample:
        if phasor == None:
            phase = self.phase
        else:
            phase = phasor.evaluate(self.phase)

        sample_index = int(phase * self.table_size) % self.table_size
        self.phase = (self.phase + self.phase_delta) % 1.0

        return self.wavetable.get_sample(sample_index)

    #===========================================================================
    def set_phase_delta(self, frequency: float, sample_rate: float) -> None:
        self.phase_delta = frequency / sample_rate

    def reset(self):
        self.reset_phase()
        self.reset_table()

    def reset_phase(self):
        self.phase = 0.0
        self.phase_delta = 0.0

    def reset_table(self):
        self.wavetable = Buffer(self.table_size)

    #===========================================================================
    def display(self, show: bool = False) -> None:
        self.wavetable.display(show = show)

    def print(self) -> None:
        print(self)