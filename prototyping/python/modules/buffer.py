#===============================================================================
import matplotlib.pyplot as plt
import numpy as np
import wavio as w

from .sample import Sample

#===============================================================================
class Buffer(object):

    #===========================================================================
    def __init__(self, buffer_size: int):
        self.buffer_size = int(buffer_size)
        self.clear()

    def __str__(self) -> str:
        return f"<Buffer_obj: size = {self.buffer_size}, buffer = [{self.buffer[0]}, ..., {self.buffer[-1]}]>\n"

    #===========================================================================
    def clear(self) -> None:
        self.buffer = [Sample(0.0) for _ in range(self.buffer_size)]

    def get_raw_buffer(self) -> list:
        return [sample.value for sample in self.buffer]

    def get_buffer(self) -> list:
        return [sample for sample in self.buffer]

    def set_buffer(self, buffer: list) -> None:
        self.buffer = buffer
        self.buffer_size = len(buffer)

    #===========================================================================
    def get_sample(self, index: int) -> Sample:
        return self.buffer[index]

    def set_sample(self, index: int, sample: Sample) -> None:
        self.buffer[index] = sample

    #===========================================================================
    def display(self, show: bool = False) -> None:
        plt.title("Buffer")

        plt.xlabel("Sample Index")
        plt.xlim((0, 2048))

        plt.ylim((-1.0, 1.0))
        plt.ylabel("Amplitude")

        x = [i for i in range(self.buffer_size)]
        y = self.get_raw_buffer()

        plt.plot(x, y, "C2")

        if show:
            plt.show()

    def print(self) -> None:
        print(self)

    #===========================================================================
    def export_wav(self, filename: str, sampling_rate: int) -> None:
        signal = np.array(self.get_raw_buffer())

        w.write(filename, signal, sampling_rate, sampwidth = 3)

        print(f"Buffer exported to \"{filename}\"")