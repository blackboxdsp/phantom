#===============================================================================
import unittest

from phantom import point

#===============================================================================
class PointTest(unittest.TestCase):

    #===========================================================================
    def setUp(self):
        self.p1_int = point.Point(2, 5)
        self.p2_int = point.Point(2, 5)
        self.p3_int = point.Point(3, 6)
        self.p_int_str = f"<Point(int)[]_obj: [{self.p1_int}, {self.p2_int}, {self.p3_int}]>"

        self.p1_float = point.Point(2.0, 5.0)
        self.p2_float = point.Point(2.0, 5.0)
        self.p3_float = point.Point(3.0, 6.0)
        self.p_float_str = f"<Point(float)[]_obj: [{self.p1_float}, {self.p2_float}, {self.p3_float}]>"

    #===========================================================================
    def test_equal_points_ints(self):
        self.assertTrue(self.p1_int == self.p2_int, self.p_int_str)
        self.assertFalse(self.p1_int == self.p3_int, self.p_int_str)

    def test_le_ints(self):
        self.assertTrue(self.p1_int <= self.p2_int, self.p_int_str)
        self.assertTrue(self.p2_int <= self.p3_int, self.p_int_str)
        self.assertFalse(self.p3_int <= self.p2_int, self.p_int_str)

    def test_lt_ints(self):
        self.assertTrue(self.p1_int < self.p3_int, self.p_int_str)
        self.assertFalse(self.p3_int < self.p2_int, self.p_int_str)

    def test_ge_ints(self):
        self.assertTrue(self.p1_int >= self.p2_int, self.p_int_str)
        self.assertFalse(self.p2_int >= self.p3_int, self.p_int_str)
        self.assertTrue(self.p3_int >= self.p2_int, self.p_int_str)

    def test_gt_ints(self):
        self.assertFalse(self.p1_int > self.p3_int, self.p_int_str)
        self.assertTrue(self.p3_int > self.p2_int, self.p_int_str)

    #===========================================================================
    def test_equal_points_floats(self):
        self.assertTrue(self.p1_float == self.p2_float, self.p_float_str)
        self.assertFalse(self.p1_float == self.p3_float)

    def test_le_floats(self):
        self.assertTrue(self.p1_float <= self.p2_float, self.p_float_str)
        self.assertTrue(self.p2_float <= self.p3_float, self.p_float_str)
        self.assertFalse(self.p3_float <= self.p2_float, self.p_float_str)

    def test_lt_floats(self):
        self.assertTrue(self.p1_float < self.p3_float, self.p_float_str)
        self.assertFalse(self.p3_float < self.p2_float, self.p_float_str)

    def test_ge_floats(self):
        self.assertTrue(self.p1_float >= self.p2_float, self.p_float_str)
        self.assertFalse(self.p2_float >= self.p3_float, self.p_float_str)
        self.assertTrue(self.p3_float >= self.p2_float, self.p_float_str)

    def test_gt_floats(self):
        self.assertFalse(self.p1_float > self.p3_float, self.p_float_str)
        self.assertTrue(self.p3_float > self.p2_float, self.p_float_str)

#===============================================================================
if __name__ == '__main__':
    unittest.main()