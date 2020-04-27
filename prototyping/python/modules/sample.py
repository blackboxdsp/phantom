#===============================================================================
class Sample(object):

    #===========================================================================
    def __init__(self, value: float):
        if isinstance(value, float):
            self.value = value

    def __str__(self) -> str:
        return f"<Sample_obj: value = {self.value:.03}>"