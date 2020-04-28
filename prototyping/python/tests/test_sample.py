#===============================================================================
import unittest

from phantom import sample

#===============================================================================
class SampleTest(unittest.TestCase):

    #===========================================================================
    def test_is_float(self):
        s1 = sample.Sample(1)
        s2 = sample.Sample(1.0)

        self.assertFalse(hasattr(s1, "value"))
        self.assertTrue(isinstance(s2, sample.Sample))
        self.assertTrue(isinstance(s2.value, float))

#===============================================================================
if __name__ == '__main__':
    unittest.main()