#===============================================================================
from .sample import Sample

#===============================================================================
class Buffer(object):

    #===========================================================================
    def __init__(self, buffer_size: int):
        assert buffer_size >= 1, f"Invalid buffer size"

        self.buffer_size = int(buffer_size)
        self.clear_buffer()

    def __str__(self):
        return f"<Buffer_obj: size = {self.buffer_size}, buffer = [{self.buffer[0]}, ..., {self.buffer[-1]}]>"

    #===========================================================================
    def clear_buffer(self):
        self.buffer = [Sample(0.0) for _ in range(self.buffer_size)]

    def get_buffer(self) -> list:
        return self.buffer

    def set_buffer(self, buffer: list):
        self.buffer = buffer
        self.buffer_size = len(buffer)

    #===========================================================================
    def get_sample(self, index: int) -> Sample:
        assert (index >= 0 and index < self.buffer_size), f"Invalid sample index for buffer of size {self.buffer_size}"
        return self.buffer[index]

    def set_sample(self, index: int, sample: Sample):
        assert (index >= 0 and index < self.buffer_size), f"Invalid sample index for buffer of size {self.buffer_size}"
        self.buffer[index] = sample

    #===========================================================================
    def display(self):
        ...

    def print(self):
        print(self)