#===============================================================================
from .point import Point

#===============================================================================
class Phasor(object):

    #===========================================================================
    def __init__(self, inflections):
        self.inflections = inflections
        self.inflection_count = len(inflections)

    def __str__(self):
        return f"Phasor_obj: inflections = {self.inflections}"

    #===========================================================================
    def get_inflection_count(self) -> int:
        return self.inflection_count

    def get_inflections(self) -> list:
        return self.inflections

    def set_inflections(self, inflections: list):
        self.inflections = inflections

    def reset_inflections(self):
        self.inflections = []

    #===========================================================================
    def display(self):
        ...

    def print(self):
        print(self)