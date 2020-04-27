#===============================================================================
from .point import Point

#===============================================================================
class Phasor(object):

    #===========================================================================
    def __init__(self, inflections: list):
        self.set_inflections(inflections)

    def __str__(self) -> str:
        return f"Phasor_obj: inflections = {self.inflections}"

    #===========================================================================
    def get_inflection_count(self) -> int:
        return self.inflection_count

    def get_inflections(self) -> list:
        return self.inflections

    def set_inflection(self, index: int, inflection: Point) -> None:
        assert index >= 0 and index < self.inflection_count, "Invalid inflection index"
        assert isinstance(inflection, Point), f"{inflection} is Non-Point object"

        self.inflections[index] = inflection

    def set_inflections(self, inflections: list) -> None:
        for inflection in inflections:
            assert isinstance(inflection, Point), f"{inflection} is Non-Point object"

        self.inflections = inflections
        self.inflection_count = len(inflections)

    def reset_inflections(self) -> None:
        self.inflections = []
        self.inflection_count = 0

    #===========================================================================
    def print(self) -> None:
        print(self)