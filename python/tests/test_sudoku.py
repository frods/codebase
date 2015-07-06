import unittest
import sys
import os
from PySide import QtGui
import logging
import time

LOGGER = logging.getLogger(__name__)

if __name__ == "__main__":
    logging.basicConfig()
    
    ROOT_PATH = os.path.abspath(os.path.join(os.path.dirname(__file__),
                                             os.pardir))
    if ROOT_PATH not in sys.path:
        sys.path.append(ROOT_PATH)

import sudoku

app = QtGui.QApplication(sys.argv)

class CollectionTestCase(unittest.TestCase):
    def testIterate(self):
        collection = sudoku.Collection()
        for x in range(9):
            collection.addCell(sudoku.Cell(None, x, x))
        values = set()
        for cell in collection.cells:
            values.add(int(cell.text()))
        self.assertEqual(list(values), range(9))

    def testComplete(self):
        collection = sudoku.Collection()
        for x in range(9):
            collection.addCell(sudoku.Cell(None, x, x))
        self.assertTrue(collection.complete())      

    def testCompleteFail(self):
        collection = sudoku.Collection()
        for x in range(9):
            collection.addCell(sudoku.Cell(None, x, x))
        collection.cells[0].setValue(0)
        self.assertFalse(collection.complete())

class CellTestCase(unittest.TestCase):
    def testGetAvailable(self):
        cell = sudoku.Cell(None, 0)
        cell.addCollection(sudoku.Collection())
        cell.addCollection(sudoku.Collection())
        cell.addCollection(sudoku.Collection())
        available = cell.getPosibilities()
        self.assertEquals(len(available), 9)

    def testGetAvailableReduced(self):
        cell = sudoku.Cell(None, 0)
        cell.addCollection(sudoku.Collection())
        cell.addCollection(sudoku.Collection())
        cell.addCollection(sudoku.Collection())
        cell.collections[0].avialable = set([1,2,3,4,5,6,7,8,9])
        cell.collections[1].available = set([1,2,3,4])
        cell.collections[2].available = set([1,     5,6,7,8])
        available = cell.getPosibilities()
        self.assertEquals(len(available), 1)

class SolverTestCase(unittest.TestCase):
    def testInvalidPuzzle(self):
        window = sudoku.Window()
        window.show()

        window.sudoku.setValues([[1, 1, 3, 4, 5, 6, 7, 8, 9],
                                 [4, 5, 6, 7, 8, 9, 1, 2, 3],
                                 [7, 8, 9, 1, 2, 3, 4, 5, 6],
                                 [5, 6, 7, 8, 9, 1, 2, 3, 4],
                                 [2, 3, 4, 5, 6, 7, 8, 9, 1],
                                 [8, 9, 1, 2, 3, 4, 5, 6, 7],
                                 [3, 4, 5, 6, 7, 8, 9, 1, 2],
                                 [6, 7, 8, 9, 1, 2, 3, 4, 5],
                                 [9, 1, 2, 3, 4, 5, 6, 7, 0]])
        self.assertFalse(window.sudoku.solved())
        self.assertRaises(sudoku.NoSolution, window.sudoku.solve())
        window.close()

    def testSimpleSolve(self):
        window = sudoku.Window()
        window.show()

        window.sudoku.setValues([[1, 2, 3, 4, 5, 6, 7, 8, 9],
                                 [4, 5, 6, 7, 8, 9, 1, 2, 3],
                                 [7, 8, 9, 1, 2, 3, 4, 5, 6],
                                 [5, 6, 7, 8, 9, 1, 2, 3, 4],
                                 [2, 3, 4, 5, 6, 7, 8, 9, 1],
                                 [8, 9, 1, 2, 3, 4, 5, 6, 7],
                                 [3, 4, 5, 6, 7, 8, 9, 1, 2],
                                 [6, 7, 8, 9, 1, 2, 3, 4, 5],
                                 [9, 1, 2, 3, 4, 5, 6, 7, 0]])
        self.assertFalse(window.sudoku.solved())
        window.sudoku.solve()
        self.assertTrue(window.sudoku.solved())
        window.close()

    def testEasySolve(self):
        window = sudoku.Window()
        window.show()

        window.sudoku.solve_puzzle('003020600900305001001806400008102900700000008006708200002609500800203009005010300')
        self.assertTrue(window.sudoku.solved())
        window.close()

    def testHardSolve2(self):
        window = sudoku.Window()
        window.show()

        window.sudoku.solve_puzzle('4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......')
        self.assertTrue(window.sudoku.solved())
        window.close()

    def testHardSolve3(self):
        window = sudoku.Window()
        window.show()

        window.sudoku.solve_puzzle("417369825030050000050720000020030060000080400000010000289643571573290600164070000")
        self.assertTrue(window.sudoku.solved())
        window.close()


    def testMediumSolve(self):
        window = sudoku.Window()
        window.show()

        window.sudoku.solve_puzzle([[0, 3, 0, 0, 9, 8, 4, 0, 0],
                                   [9, 0, 8, 4, 0, 0, 0, 0, 5],
                                   [0, 0, 0, 0, 0, 1, 0, 0, 2],
                                   [0, 0, 0, 0, 0, 0, 1, 0, 3],
                                   [0, 4, 0, 0, 0, 0, 0, 6, 0],
                                   [1, 0, 2, 0, 0, 0, 0, 0, 0],
                                   [2, 0, 0, 1, 0, 0, 0, 0, 0],
                                   [4, 0, 0, 0, 0, 5, 6, 0, 8],
                                   [0, 0, 7, 8, 3, 0, 0, 9, 0]])
        self.assertTrue(window.sudoku.solved())
        window.close()

    def testHardSolve(self):
        window = sudoku.Window()
        window.show()

        window.sudoku.solve_puzzle([[0, 0, 7, 0, 0, 0, 9, 0, 0],
                                    [0, 0, 0, 9, 0, 3, 0, 0, 0],
                                    [8, 0, 0, 0, 7, 0, 0, 0, 1],
                                    [0, 3, 0, 6, 0, 8, 0, 2, 0],
                                    [0, 0, 9, 0, 2, 0, 1, 0, 0],
                                    [0, 2, 0, 1, 0, 5, 0, 8, 0],
                                    [2, 0, 0, 0, 4, 0, 0, 0, 7],
                                    [0, 0, 0, 8, 0, 9, 0, 0, 0],
                                    [0, 0, 5, 0, 0, 0, 4, 0, 0]])
        # value = raw_input(" asdf")
        self.assertTrue(window.sudoku.solved())
        window.close()

    def testImposibleSolve(self):
        window = sudoku.Sudoku(None)
        # window.show()

        self.assertFalse(window.solved())
        window.solve()
        self.assertTrue(window.solved())
        # window.close()

    def testFromFile(self):
        window = sudoku.Sudoku(None)

        with open("sudoku_puzzles.txt") as r:
            puzzles = r.readlines()
        for puzzle in puzzles:
            start = time.clock()
            window.solve_puzzle(puzzle)
            self.assertTrue(window.solved())
            duration = time.clock() - start
            print "Puzzle solved in: %f s" % duration


if __name__ == "__main__":
    unittest.main()        

