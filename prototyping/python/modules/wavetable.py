#===============================================================================
import math

from .buffer import Buffer
from .sample import Sample

#===============================================================================
class Wavetable(object):

    #===========================================================================
    def __init__(self, table_size):
        assert (table_size >= 1), "Invalid table size"

        self.table_size = table_size
        self.wavetable = Buffer(table_size)
        self.create_table()

        self.phase = 0.0
        self.phase_delta = 0.0

    def __str__(self) -> str:
        return f"<Wavetable_obj: size = {self.table_size}, wavetable = {self.wavetable}>"

    #===========================================================================
    def create_table(self) -> None:
        for i in range(self.table_size):
            phase = float(i / self.table_size)
            value = math.sin(phase * math.pi * 2.0)

            self.wavetable.set_sample(i, Sample(value))

    def get_next_sample(self) -> Sample:
        sample_index = int(self.phase)
        self.phase = (self.phase + self.phase_delta) % self.table_size

        return self.wavetable.get_sample(sample_index)

    #===========================================================================
    def set_phase_delta(self, frequency: float, sample_rate: float) -> None:
        assert sample_rate >= 1, "Invalid sample rate"

        table_size_over_sample_rate = self.table_size / sample_rate
        self.phase_delta = frequency * table_size_over_sample_rate

    #===========================================================================
    def display(self) -> None:
        self.wavetable.display()

    def print(self) -> None:
        print(self)