#===============================================================================
import unittest

from modules import buffer, phasor, point, sample, wavetable

#===============================================================================
class PointTest(unittest.TestCase):

    #===========================================================================
    def test_equal_points_ints(self):
        p1 = point.Point(2, 5)
        p2 = point.Point(2, 5)
        p3 = point.Point(3, 5)

        self.assertTrue(p1 == p2)
        self.assertFalse(p1 == p3)

    def test_le_ints(self):
        p1 = point.Point(2, 5)
        p2 = point.Point(2, 5)
        p3 = point.Point(3, 6)

        self.assertTrue(p1 <= p2)
        self.assertTrue(p2 <= p3)
        self.assertFalse(p3 <= p2)

    def test_lt_ints(self):
        p1 = point.Point(2, 5)
        p2 = point.Point(2, 5)
        p3 = point.Point(3, 6)

        self.assertTrue(p1 < p3)
        self.assertFalse(p3 < p2)

    def test_ge_ints(self):
        p1 = point.Point(2, 5)
        p2 = point.Point(2, 5)
        p3 = point.Point(3, 6)

        self.assertTrue(p1 >= p2)
        self.assertFalse(p2 >= p3)
        self.assertTrue(p3 >= p2)

    def test_gt_ints(self):
        p1 = point.Point(2, 5)
        p2 = point.Point(2, 5)
        p3 = point.Point(3, 6)

        self.assertFalse(p1 > p3)
        self.assertTrue(p3 > p2)

    #===========================================================================
    def test_equal_points_floats(self):
        p1 = point.Point(2.0, 5.0)
        p2 = point.Point(2.0, 5.0)
        p3 = point.Point(3.0, 5.0)

        self.assertTrue(p1 == p2)
        self.assertFalse(p1 == p3)

    def test_le_floats(self):
        p1 = point.Point(2.0, 5.0)
        p2 = point.Point(2.0, 5.0)
        p3 = point.Point(3.0, 6.0)

        self.assertTrue(p1 <= p2)
        self.assertTrue(p2 <= p3)
        self.assertFalse(p3 <= p2)

    def test_lt_floats(self):
        p1 = point.Point(2.0, 5.0)
        p2 = point.Point(2.0, 5.0)
        p3 = point.Point(3.0, 6.0)

        self.assertTrue(p1 < p3)
        self.assertFalse(p3 < p2)

    def test_ge_floats(self):
        p1 = point.Point(2.0, 5.0)
        p2 = point.Point(2.0, 5.0)
        p3 = point.Point(3.0, 6.0)

        self.assertTrue(p1 >= p2)
        self.assertFalse(p2 >= p3)
        self.assertTrue(p3 >= p2)

    def test_gt_floats(self):
        p1 = point.Point(2.0, 5.0)
        p2 = point.Point(2.0, 5.0)
        p3 = point.Point(3.0, 6.0)

        self.assertFalse(p1 > p3)
        self.assertTrue(p3 > p2)

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
if __name__ == "__main__":
    unittest.main()