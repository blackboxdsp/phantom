#===============================================================================
class Display(object):

    #===========================================================================
    def __init__(self, width, height):
        self.width = width
        self.height = height

    def __str__(self):
        return f"<Display_obj: width = {self.width}, height = {self.height}>"