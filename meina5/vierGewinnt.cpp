

#include <cmath>
#include <ostream>
#include <string>
#include <vector>

#include "unit.h"

enum Color { empty, yellow, red };

class Board {
   private:
    std::vector<Color> gameBoard;
    int row;
    int col;
    int lastTurn;

   public:
    explicit Board(int row = 1, int col = 1);
    ~Board(){};
    Board(const Board&);

    // operator
    Color& operator()(int, int);
    Color operator()(int, int) const;
    Board operator=(const Board&);

    int getRow() { return row; };
    int getCol() { return col; };

    Board& reset(int, int);

    bool setBoard(Color, int);
    bool toLastTurn();
    bool isLegalCol(int);
    bool isEnd();
};

Board::Board(int row, int col) { this->reset(row, col); }

Board::Board(const Board& Board) : gameBoard(Board.gameBoard) {
    row = Board.row;
    col = Board.col;
}

Board Board::operator=(const Board& Board) {
    this->reset(Board.row, Board.col);
    this->gameBoard = Board.gameBoard;
    return *this;
}

Color& Board::operator()(int row, int cole) {
    return gameBoard[row * col + cole];
}

Color Board::operator()(int row, int cole) const {
    return gameBoard[row * col + cole];
}

Board& Board::reset(int getRow, int getCol) {
    this->row = getRow;
    this->col = getCol;
    gameBoard.resize(row * col);
    for (int i = 0; i < int(gameBoard.size()); i++) {
        gameBoard[i] = empty;
    }
    return *this;
}

bool Board::setBoard(Color color, int cole) {
    if (isLegalCol(cole) == true) {
        for (int i = row - 1; int(i) >= 0; i--) {
            if ((*this)(i, cole) == empty) {
                (*this)(i, cole) = color;
                lastTurn = cole;
                return true;
            }
        }
    }
    return false;
}

bool Board::toLastTurn() {
    for (int i = 0; i < row; i++) {
        if ((*this)(i, lastTurn) != empty) {
            (*this)(i, lastTurn) = empty;
            return true;
        }
    }
    return false;
}

bool Board::isLegalCol(int cole) {
    if ((*this)(0, cole) == empty) {
        return true;
    } else {
        return false;
    }
}

bool Board::isEnd() {
    int counter;
    Color baseColor, colorInLine;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            baseColor = (*this)(i, j);
            if (baseColor == empty) continue;

            // 4 horizontal
            counter = 1;
            for (int k = 1; k < 4 && j + 3 < col; k++) {
                colorInLine = (*this)(i, j + k);
                if (baseColor == colorInLine) {
                    counter++;
                } else {
                    break;
                }
            }
            if (counter == 4) {
                return true;
            }

            // 4 vertikal
            counter = 1;
            for (int k = 1; k < 4 && i + 3 < row; k++) {
                colorInLine = (*this)(i + k, j);
                if (baseColor == colorInLine) {
                    counter++;
                } else {
                    break;
                }
            }
            if (counter == 4) {
                return true;
            }

            // 4 diagonal RechtsUnten
            counter = 1;
            for (int k = 1; k < 4 && i + 3 < row && j + 3 < col; k++) {
                colorInLine = (*this)(i + k, j + k);
                if (baseColor == colorInLine) {
                    counter++;
                } else {
                    break;
                }
            }
            if (counter == 4) {
                return true;
            }

            // 4 diagonal LinksUnten
            counter = 1;
            for (int k = 1; k < 4 && i + 3 < row && j - 3 >= 0; k++) {
                colorInLine = (*this)(i + k, j - k);
                if (baseColor == colorInLine) {
                    counter++;
                } else {
                    break;
                }
            }
            if (counter == 4) {
                return true;
            }
        }
    }

    return false;
}

float getHeuristicValue(int redNum, int yellowNum) {
    float z2 = 0.05, z3 = 0.2;
    if (redNum * yellowNum == 0) {
        if (redNum == 2) {
            return -z2;
        }
        if (yellowNum == 2) {
            return z2;
        }
        if (redNum == 3) {
            return -z3;
        }
        if (yellowNum == 3) {
            return z3;
        }
        if (redNum == 4) {
            return -1;
        }
        if (yellowNum == 4) {
            return 1;
        }
    }
    return 0;
}

float heuristic(Board gameBoard) {
    int yellowNum = 0;
    int redNum = 0;
    float value = 0.0, currValue = 0.0;

    for (int i = 0; i < gameBoard.getRow(); i++) {
        for (int j = 0; j < gameBoard.getCol(); j++) {
            yellowNum = 0;
            redNum = 0;
            for (int k = 0; k < 4 && j + 3 < gameBoard.getCol(); k++) {
                if (gameBoard(i, j + k) == Color::yellow) {
                    yellowNum++;
                } else if (gameBoard(i, j + k) == Color::red) {
                    redNum++;
                }
            }
            currValue = getHeuristicValue(redNum, yellowNum);
            if (fabs(currValue) == 1) {
                return currValue;
            } else {
                value += currValue;
            }
            yellowNum = 0;
            redNum = 0;
            for (int k = 0; k < 4 && i + 3 < gameBoard.getRow(); k++) {
                if (gameBoard(i + k, j) == Color::yellow) {
                    yellowNum++;
                } else if (gameBoard(i + k, j) == Color::red) {
                    redNum++;
                }
            }
            currValue = getHeuristicValue(redNum, yellowNum);
            if (fabs(currValue) == 1) {
                return currValue;
            } else {
                value += currValue;
            }
            yellowNum = 0;
            redNum = 0;
            for (int k = 0; k < 4 && i + 3 < gameBoard.getRow() &&
                            j + 3 < gameBoard.getCol();
                 k++) {
                if (gameBoard(i + k, j + k) == Color::yellow) {
                    yellowNum++;
                } else if (gameBoard(i + k, j + k) == Color::red) {
                    redNum++;
                }
            }
            currValue = getHeuristicValue(redNum, yellowNum);
            if (fabs(currValue) == 1) {
                return currValue;
            } else {
                value += currValue;
            }
            yellowNum = 0;
            redNum = 0;
            for (int k = 0; k < 4 && i + 3 < gameBoard.getRow() && j - 3 >= 0;
                 k++) {
                if (gameBoard(i + k, j - k) == Color::yellow) {
                    yellowNum++;
                } else if (gameBoard(i + k, j - k) == Color::red) {
                    redNum++;
                }
            }
            currValue = getHeuristicValue(redNum, yellowNum);
            if (fabs(currValue) == 1) {
                return currValue;
            } else {
                value += currValue;
            }
        }
    }
    return value;
}

float findColWithMinMax(Board gameBoard, int remainDepth, bool isMax,
                        int& targetCol) {
    if (remainDepth == 0 || gameBoard.isEnd()) {
        return heuristic(gameBoard);
    }
    if (isMax) {
        float currMax = -1000;
        int currCol = -1;
        std::vector<int> maxCol;
        maxCol.push_back(-1);
        for (int i = 0; i < gameBoard.getCol(); i++) {
            if (gameBoard.isLegalCol(i)) {
                gameBoard.setBoard(Color::yellow, i);
                float currValue = findColWithMinMax(gameBoard, remainDepth - 1,
                                                    !isMax, currCol);
                gameBoard.toLastTurn();
                if (currValue > currMax) {
                    currMax = currValue;
                    maxCol.clear();
                    maxCol.push_back(i);
                } else if (currValue == currMax) {
                    maxCol.push_back(i);
                }
            }
        }
        targetCol = maxCol[rand() % int(maxCol.size())];
        return currMax;
    } else {
        float currMin = 1000;
        int currCol = -1;
        std::vector<int> minCol;
        minCol.push_back(-1);
        for (int i = 0; i < gameBoard.getCol(); i++) {
            if (gameBoard.isLegalCol(i)) {
                gameBoard.setBoard(Color::red, i);
                float currValue = findColWithMinMax(gameBoard, remainDepth - 1,
                                                    !isMax, currCol);
                gameBoard.toLastTurn();
                if (currValue < currMin) {
                    currMin = currValue;
                    minCol.clear();
                    minCol.push_back(i);
                } else if (currValue == currMin) {
                    minCol.push_back(i);
                }
            }
        }
        targetCol = minCol[rand() % int(minCol.size())];
        return currMin;
    }
}

int miniMax(Board gameBoard, bool isYellow, int depth) {
    int col = -1;
    findColWithMinMax(gameBoard, depth, isYellow, col);
    if (col == -1) {
        for (int i = 0; i < gameBoard.getCol(); i++) {
            if (gameBoard.isLegalCol(i) == true) {
                return i;
            }
        }
    }
    return col;
}

int main() {
    int Schwierigkeitsgrad = 4;
    Board gameBoard(numRows, numCols);
    startGame(Schwierigkeitsgrad);

    for (unsigned int game = 1; game <= numGames; game++) {
        gameBoard.reset(numRows, numCols);
        bool isYellow = true;
        if (game % 2 == 0) {
            int col = nextTurn(-1);
            isYellow = false;
            gameBoard.setBoard(Color::yellow, col);
        } else {
            gameBoard.setBoard(Color::yellow, int(numCols / 2));
            int col = nextTurn(int(numCols / 2));
            gameBoard.setBoard(Color::red, col);
        }

        while (1) {
            int targetCol = -1;
            int col = -1;
            targetCol = miniMax(gameBoard, isYellow, 5);
            if (isYellow) {
                gameBoard.setBoard(Color::yellow, targetCol);
                col = nextTurn(targetCol);
                gameBoard.setBoard(Color::red, col);
            } else {
                gameBoard.setBoard(Color::red, targetCol);
                col = nextTurn(targetCol);
                gameBoard.setBoard(Color::yellow, col);
            }
            if (col < 0 || targetCol < 0) {
                break;
            }
        }
    }

    return 0;
}
