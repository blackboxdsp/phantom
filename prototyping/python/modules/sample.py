#===============================================================================
class Sample(object):

    #===========================================================================
    def __init__(self, value):
        self.value = value

    def __str__(self) -> str:
        return f"<Sample_obj: value = {self.value}>"