import sys
from PySide import QtCore
from PySide import QtGui
import time
import logging

LOGGER = logging.getLogger(__name__)

class NoValidPosibilities(Exception):
    pass

class NoSolution(Exception):
    pass

class Cell(QtGui.QLineEdit):
    CALCULATING = "calculating"
    def __init__(self, window, cell_id, value=0):
        super(Cell, self).__init__()
        if window:
            self.setMaxLength(1)
            self.setValidator(QtGui.QIntValidator(1, 9))

        self.initial_value = False
        self.collections = []
        self.window = window
        self.id = cell_id
        self.setValue(value)

    def addCollection(self, collection):
        """
        Ad a collection that the cell belongs to
        """
        self.collections.append(collection)

    def updateBackground(self, state=None, flush=True):
        """
        Update the cell background to reflect the current state
        """
        if not self.window:
            return
        if state == self.CALCULATING:
            LOGGER.debug("%s reducing", str(self.id))
            self.setStyleSheet("QLineEdit { background-color: rgba(0, 188, 0, 50);}")
        elif self.initial_value:
            LOGGER.debug("%s reducing", str(self.id))
            self.setStyleSheet("QLineEdit { background-color: rgba(0, 0, 100, 50);}")
        else:
            LOGGER.debug("%s normal", str(self.id))
            self.setStyleSheet("QLineEdit { background-color: rgba(255, 255, 255, 255);}")
        if flush:
            QtCore.QCoreApplication.processEvents()
            QtCore.QCoreApplication.flush()

    def freeze(self):
        self.initial_value = bool(self.value or self.text())
        self.updateBackground(flush=False)

    def getPosibilities(self):
        """
        Return a list of the available values that the cell can take
        """
        if self.value:
            # Value already set there are no posibilities
            return []
        available = set(range(1,10))
        for collection in self.collections:
            available = available.intersection(collection.available)
        return available

    def getValue(self):
        value = self.text()
        if not value:
            return '.'
        return value

    def setValue(self, value, state=None, flush=False):
        """
        Set the cell to the given value and update the collections it belongs to
        """
        self.value = value
        for collection in self.collections:
            collection.valueTaken(value)

        if self.window:
            str_value = ""
            if value in range(1,10):
                str_value = str(value)
            self.setText(str_value)
            self.updateBackground(state, flush)

    def pickValue(self):
        """
        Set the current value if there is only one choice for the value
        """
        if not self.value:
            available = self.getPosibilities()
            if self.window:
                self.window.set_status("%s: %s" % (self.id, available))
            self.updateBackground(self.CALCULATING)
            # time.sleep(0.25)
            # value = raw_input("Press any key")
            if not available:
                LOGGER.info("%s No available values", str(self.id))
                self.updateBackground()
                raise NoValidPosibilities()

            if len(available) == 1:
                value = available.pop()
                self.setValue(value)
                self.updateBackground()
                return True
        self.updateBackground()
        return False


class Collection(object):
    def __init__(self):
        self.cells = []
        self.resetAvailable()

    def resetAvailable(self):
        self.available = set(range(1,10))

    def addCell(self, cell):
        """
        Add cell to the collection and notify the cell that it belongs to this 
        collection
        """
        self.cells.append(cell)
        cell.addCollection(self)

    def valueTaken(self, value):
        """
        Remove value from available values
        """
        if not value:
            return
        int_value = int(value)
        if int_value in self.available:
            self.available.remove(int_value)
        else:
            LOGGER.warning("Value %s found but not available in collection: %s", value, self.available)

    def reduce(self):
        """
        Initialize available values for the collection
        """
        self.resetAvailable()
        for cell in self.cells:
            if cell.value:
                self.valueTaken(cell.value)

    def complete(self):
        """
        Verify that the collection contains a full set of values
        """
        values = set()
        for cell in self.cells:
            if cell.value:
                values.add(cell.value)
        return len(values) == 9


class Sudoku(QtGui.QWidget):
    def __init__(self, window):
        super(Sudoku, self).__init__()
        self.window = window
        self.rows = []
        self.cols = []
        self.blocks = []
        self.show()

    def resetPuzzle(self):
        """
        Reset state to completely unset
        """
        for collection in self.iterCollections():
            collection.resetAvailable()

        for cell in self.iterCells():
            cell.setValue(0)      

    def setValues(self, values):
        """
        Use values to set the state of the puzzle
        Values can either be a string with each value indicated by
        a digit 1-9 unset values are indicated with 0 or .
        All other characters are ignored.
        Values can also be a matrix setting all the values
        """
        if isinstance(values, basestring):
            value_grid = []
            chars = [c for c in values if c in "123456789" or c in '0.']
            assert len(chars) == 81
            for idx, char in enumerate(chars):
                row = idx // 9
                col = idx % 9
                if len(value_grid) <=    row:
                    value_grid.append([0] * 9)
                if char == ".":
                    char = '0'
                value_grid[row][col] = int(char)
            values = value_grid

        assert len(values) == len(self.rows)
        assert len(values[0]) == len(self.cols)

        self.resetPuzzle()
        for row_num, row in enumerate(self.rows):
            for cell_num, cell in enumerate(row.cells):
                value = values[row_num][cell_num]
                cell.setValue(value, flush=False)
        if not self.window:
            QtCore.QCoreApplication.processEvents()
            QtCore.QCoreApplication.flush()

    def iterCollections(self):
        collections = self.rows + self.cols + self.blocks
        for collection in collections:
            yield collection

    def iterCells(self):
        for row in self.rows:
            for cell in row.cells:
                yield cell

    def updateState(self, puzzle):
        """
        Set the puzzle to the given state and 
        reduce the collection values
        """
        self.setValues(puzzle)
        for collection in self.iterCollections():
            collection.reduce()

    def freezeInitialValues(self):
        for cell in self.iterCells():
            cell.freeze()

    def serialize(self):
        """
        Create a string of the current state of the puzzle
        """
        grid = ""
        for cell in self.iterCells():
            grid += cell.getValue()

        return grid

    def solved(self):
        """
        Check if the puzzle is in a solved state
        Return True if solved, False otherwise
        """
        for collection in self.iterCollections():
            if not collection.complete():
                return False
        return True

    def solve(self):
        """
        Solve the current puzzle
        """
        self.freezeInitialValues()
        solved = self.solve_puzzle(self.serialize())

    def solve_puzzle(self, puzzle):
        """
        Recursively solve the puzzle
        Perform constraing propagation until no obvious values can be set.
        Then choose the cell with the fewest possible values and recurse trying
        each value.
        """
        LOGGER.info("Solving puzzle: %s", puzzle)
        self.updateState(puzzle)

        try:
            number_set = True
            while number_set:
                number_set = False
                for cell in self.iterCells():
                    result = cell.pickValue()
                    if result:
                        number_set = True
        except NoValidPosibilities:
            # A cell had no possible values to set
            LOGGER.info("No more valid posibilities")
            return False

        if not self.solved():
            min_cell = None
            min_available = range(0,10)
            for row_idx, row in enumerate(self.rows):
                for cell_idx, cell in enumerate(row.cells):
                    available = cell.getPosibilities()
                    if available and len(available) < len(min_available):
                        min_available = available
                        min_cell = cell
            assert len(min_available) > 1
            solved = False
            if not min_cell:
                LOGGER.error("Couldn't find a min cell\n%s", self.serialize())
                return False
            LOGGER.info("Trying cell %s with choices: %s", min_cell.id, min_available)
            puzzle = self.serialize()
            for option in min_available:
                self.updateState(puzzle)
                LOGGER.info("%s Trying option %s", min_cell.id, option)
                min_cell.setValue(option, Cell.CALCULATING)
                solved = self.solve_puzzle(self.serialize())
                if solved:
                    return solved
            return False
        else:
            return True

    def paintEvent(self, e):
        qp = QtGui.QPainter()
        qp.begin(self)
        self.drawLines(qp)
        qp.end()

    def drawLines(self, qp):
        pen = QtGui.QPen(QtCore.Qt.black, 2, QtCore.Qt.SolidLine)

        qp.setPen(pen)
        qp.drawLine(0, 102, 400, 102)
        qp.drawLine(0, 195, 400, 195)

        qp.drawLine(130, 0, 130, 300)
        qp.drawLine(250, 0, 250, 300)

    def show(self):
        self.grid_layout = QtGui.QGridLayout()
        self.rows = []
        self.cols = []
        self.blocks = []
        for row in range(9):
            if len(self.rows) <= row:
                self.rows.append(Collection())
            for col in range(9):
                if len(self.cols) <= col:
                    self.cols.append(Collection())
                block_num = (col / 3) + (3 * (row / 3))
                if len(self.blocks) <= block_num:
                    self.blocks.append(Collection())

                cell = Cell(self.window, (row, col))
                self.grid_layout.addWidget(cell, row + row / 3, col + col / 3)
                self.rows[row].addCell(cell)
                self.cols[col].addCell(cell)
                self.blocks[block_num].addCell(cell)

        self.setLayout(self.grid_layout)


class Window(QtGui.QMainWindow):
    """
    Main application window
    """
    def __init__(self):
        super(Window, self).__init__()
        self.settings = QtCore.QSettings()

    def loadSettings(self):
        pass

    def storeSettings(self):
        pass

    def closeEvent(self, event):
        self.storeSettings()
        event.accept()

    def set_status(self, message):
        """
        Set the status message of the window
        """
        self.statusBar().showMessage(message)

    def loadPuzzle(self, puzzle):
        self.sudoku.setValues(puzzle)

    def show(self):
        file_menu = self.menuBar().addMenu("&File")
        exit_action = QtGui.QAction("Exit",
                                    self,
                                    shortcut=QtGui.QKeySequence.Quit,
                                    statusTip="Exit the applicaiton",
                                    triggered=self.close)
        file_menu.addAction(exit_action)

        window = QtGui.QWidget()
        window_layout = QtGui.QVBoxLayout()

        self.sudoku = Sudoku(self)
        window_layout.addWidget(self.sudoku)

        solve_button = QtGui.QPushButton("Solve")
        window_layout.addWidget(solve_button)
        solve_button.clicked.connect(self.sudoku.solve)

        window.setLayout(window_layout)
        self.setCentralWidget(window)

        self.statusBar()

        self.loadSettings()

        self.setMaximumSize(400,379)

        super(Window, self).show()    

try:
    from version import *
except ImportError:
    VERSION = "DEVELOPMENT"

def main():
    """
    Run when launched directly
    """
    root_logger = logging.getLogger()
    root_logger.setLevel(logging.INFO)
    
    file_handler = logging.FileHandler("log.txt", 'a')
    file_handler.setLevel(logging.INFO)
    file_handler.setFormatter(logging.Formatter(
        '%(asctime)s %(name)s %(levelname)-8s %(message)s',
        '%a, %d %b %Y %H:%M:%S'))
    root_logger.addHandler(file_handler)

    # Create a Qt application
    app = QtGui.QApplication(sys.argv)

    window = Window()
    # pylint: disable=C0103,F0401,W0401,E1101
    window.setWindowTitle("Sudoku Solver v%s" % VERSION)

    window.show()

    if len(sys.argv) == 2:
        window.loadPuzzle(sys.argv[1])
        

    # Enter Qt application main loop
    sys.exit(app.exec_())

if __name__ == "__main__":
    main()
