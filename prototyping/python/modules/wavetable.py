#===============================================================================
from .buffer import Buffer

#===============================================================================
class Wavetable(object):

    #===========================================================================
    def __init__(self, table_size):
        assert (table_size >= 1), "Invalid table size"

        self.table_size = table_size
        self.wavetable = Buffer(table_size)

    def __str__(self):
        return f"<Wavetable_obj: size = {self.table_size}, wavetable = {self.wavetable}>"

    #===========================================================================
    def display(self):
        ...

    def print(self):
        print(self)