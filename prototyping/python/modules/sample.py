#===============================================================================
class Sample(object):

    #===========================================================================
    def __init__(self, value):
        assert (value >= -1.0 and value < 1.0), "Distorted sample value"
        
        self.value = value

    def __str__(self):
        return f"<Sample_obj: value = {self.value}>"