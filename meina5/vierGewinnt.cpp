// ...

#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "unit.h"

// ...

const unsigned int Schwierigkeitsgrad = 2;

enum Color { empty, yellow, red };

void generateemptyBoard(int col, int row,
                        std::vector<std::vector<Color>>& checkBoard);
void printBoard(std::vector<std::vector<Color>>& checkBoard);

int setBoard(int col, Color color, std::vector<std::vector<Color>>& checkBoard);
float checkNeighbor(int col, Color color,
                    const std::vector<std::vector<Color>> checkBoard);
float measureChip(int startCol, int startRow, int endCol, int endRow,
                  const std::vector<std::vector<Color>> checkBoard);
void findColWithMinMax(std::vector<std::vector<Color>> checkBoard,
                       int remainDepth, bool isMax, int& targetCol,
                       float& targetValue);
void realGame();

void virtualGame();

int main() {
    realGame();
    return 0;
}

void virtualGame() {
    std::vector<std::vector<Color>> board;
    /* yellow to add and red to reduce */
    startGame(Schwierigkeitsgrad);
    generateemptyBoard(numCols, numRows, board);
    bool isYellow = true;
    setBoard(int(numCols / 2), Color::yellow, board);
    nextTurn(int(numCols / 2));
    while (1) {
        int targetCol = -1;
        float targetValue = 0.0;
        findColWithMinMax(board, 0, isYellow, targetCol, targetValue);
        setBoard(targetCol, Color::yellow, board);
        nextTurn(targetCol);
        setBoard(0, Color::red, board);
    }
}
void realGame() {
    std::vector<std::vector<Color>> board;
    /* yellow to add and red to reduce */
    startGame(Schwierigkeitsgrad);

    for (unsigned int game = 1; game <= numGames; game++) {
        generateemptyBoard(numCols, numRows, board);
        bool isYellow = true;
        if (game % 2 == 0) {
            int col = nextTurn(-1);
            isYellow = false;
            setBoard(col, Color::yellow, board);
        } else {
            setBoard(int(numCols / 2), Color::yellow, board);
            int col = nextTurn(int(numCols / 2));
            setBoard(col, Color::red, board);
        }

        while (1) {
            int targetCol = -1;
            float targetValue = 0.0;
            findColWithMinMax(board, 4, isYellow, targetCol, targetValue);
            if (isYellow) {
                setBoard(targetCol, Color::yellow, board);
                int col = nextTurn(targetCol);
                setBoard(col, Color::red, board);
            } else {
                setBoard(targetCol, Color::red, board);
                int col = nextTurn(targetCol);
                setBoard(col, Color::yellow, board);
            }
        }
    }
}

void generateemptyBoard(int col, int row,
                        std::vector<std::vector<Color>>& checkBoard) {
    checkBoard.clear();
    for (int i = 0; i < col; i++) {
        std::vector<Color> colorItem;
        for (int j = 0; j < row; j++) {
            colorItem.push_back(Color::empty);
        }
        checkBoard.push_back(colorItem);
    }
}

void printBoard(std::vector<std::vector<Color>>& checkBoard) {
    int row = int(checkBoard[0].size());
    for (int j = row - 1; j >= 0; j--) {
        for (int i = 0; i < int(checkBoard.size()); i++) {
            std::cout << checkBoard[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

int setBoard(int col, Color color,
             std::vector<std::vector<Color>>& checkBoard) {
    int colMax = int(checkBoard.size());
    int rowMax = int(checkBoard[0].size());
    int setRow = -1;
    if (0 <= col && col < colMax) {
        for (int top = 0; top < rowMax; top++) {
            if (checkBoard[col][top] == Color::empty) {
                checkBoard[col][top] = color;
                setRow = top;
                break;
            }
        }
    }
    return setRow;
}

float measureChip(int startCol, int startRow, int endCol, int endRow,
                  const std::vector<std::vector<Color>> checkBoard) {
    int col = int(checkBoard.size());
    int row = int(checkBoard[0].size());
    if ((startCol < 0) || (startRow < 0) || (endCol >= col) ||
        (endRow >= row)) {
        return 0.0;
    } else {
        int yellowNum = 0;
        int redNum = 0;
        int colStep = (endCol - startCol) / 3;
        int rowStep = (endRow - startRow) / 3;
        int currRow = startRow;
        int currCol = startCol;
        for (int i = 0; i < 4; i++) {
            if (checkBoard[currCol][currRow] == Color::yellow) {
                yellowNum++;
            } else if (checkBoard[currCol][currRow] == Color::red) {
                redNum++;
            }
            currCol += colStep;
            currRow += rowStep;
        }
        if (redNum > 0 && yellowNum > 0) {
            return 0.0;
        } else {
            if (redNum == 4) {
                return -1;
            }
            if (redNum == 3) {
                return -0.2;
            }
            if (redNum == 2) {
                return -0.05;
            }
            if (yellowNum == 4) {
                return 1;
            }
            if (yellowNum == 3) {
                return 0.2;
            }
            if (yellowNum == 2) {
                return 0.05;
            }
        }
    }
    return 0.0;
}

float checkNeighbor(int col, Color color,
                    const std::vector<std::vector<Color>> checkBoard) {
    std::vector<std::vector<Color>> copyBoard = checkBoard;
    int row = setBoard(col, color, copyBoard);
    float heuristic = 0.0;
    if (row >= 0) {
        /*----*/
        float maxAbs = 0.0;
        float maxValue = 0.0;
        for (int i = 0; i < 4; i++) {
            int startCol = col - i;
            int endCol = startCol + 3;
            int startRow = row;
            int endRow = row;
            float result =
                measureChip(startCol, startRow, endCol, endRow, copyBoard);
            if (fabs(result) == 1) {
                return result;
            } else {
                if (fabs(result) >= maxAbs) {
                    maxValue = result;
                }
            }
        }
        heuristic += maxValue;
        /*||||*/
        // maxAbs = 0.0;
        // maxValue = 0.0;
        for (int i = 0; i < 4; i++) {
            int startCol = col;
            int endCol = col;
            int startRow = row - i;
            int endRow = startRow + 3;
            float result =
                measureChip(startCol, startRow, endCol, endRow, copyBoard);
            if (fabs(result) == 1) {
                return result;
            } else {
                if (fabs(result) >= maxAbs) {
                    maxValue = result;
                }
            }
        }
        heuristic += maxValue;
        /*////*/
        // maxAbs = 0.0;
        // maxValue = 0.0;
        for (int i = 0; i < 4; i++) {
            int startCol = col - i;
            int endCol = startCol + 3;
            int startRow = row - i;
            int endRow = startRow + 3;
            float result =
                measureChip(startCol, startRow, endCol, endRow, copyBoard);
            if (fabs(result) == 1) {
                return result;
            } else {
                if (fabs(result) >= maxAbs) {
                    maxValue = result;
                }
            }
        }
        heuristic += maxValue;
        /*\\\\*/
        // maxAbs = 0.0;
        // maxValue = 0.0;
        for (int i = 0; i < 4; i++) {
            int startCol = col - i;
            int endCol = startCol + 3;
            int startRow = row + i;
            int endRow = startRow - 3;
            float result =
                measureChip(startCol, startRow, endCol, endRow, copyBoard);
            if (fabs(result) == 1) {
                return result;
            } else {
                if (fabs(result) >= maxAbs) {
                    maxValue = result;
                }
            }
        }
        heuristic += maxValue;
    }
    return heuristic;
}

void findColWithMinMax(std::vector<std::vector<Color>> checkBoard,
                       int remainDepth, bool isMax, int& targetCol,
                       float& targetValue) {
    int colNum = int(checkBoard.size());
    int rowNum = int(checkBoard[0].size());
    if (true) {
        if (isMax) {
            float currMax = -1.1;
            std::vector<int> maxCol;
            maxCol.push_back(-1.1);
            for (int i = 0; i < colNum; i++) {
                if (checkBoard[i][rowNum - 1] == Color::empty) {
                    float value = checkNeighbor(i, Color::yellow, checkBoard);
                    if (value > currMax) {
                        maxCol.clear();
                        maxCol.push_back(i);
                        currMax = value;
                    } else if (value == currMax) {
                        maxCol.push_back(i);
                    }
                    if (currMax == 1) {
                        break;
                    }
                }
            }
            if (currMax == 1 || remainDepth == 0) {
                targetValue = currMax;
                targetCol = maxCol[rand() % int(maxCol.size())];
            } else {
                float currMax = -1.1;
                std::vector<int> maxCol;
                maxCol.push_back(-1.1);
                for (int i = 0; i < colNum; i++) {
                    if (checkBoard[i][rowNum - 1] == Color::empty) {
                        int pos = -1;
                        float value = 0;
                        int nextDepth = remainDepth - 1;
                        std::vector<std::vector<Color>> boardCopy = checkBoard;
                        setBoard(i, Color::yellow, boardCopy);
                        findColWithMinMax(boardCopy, nextDepth, false, pos,
                                          value);
                        if (value > currMax) {
                            maxCol.clear();
                            maxCol.push_back(i);
                            currMax = value;
                        } else if (value == currMax) {
                            maxCol.push_back(i);
                        }
                        if (currMax == 1) {
                            break;
                        }
                    }
                }
                targetCol = maxCol[rand() % int(maxCol.size())];
                targetValue = currMax;
            }

        } else {
            float currMin = 1.1;
            std::vector<int> minCol;
            minCol.push_back(1.1);
            for (int i = 0; i < colNum; i++) {
                if (checkBoard[i][rowNum - 1] == Color::empty) {
                    float value = checkNeighbor(i, Color::red, checkBoard);
                    if (value < currMin) {
                        minCol.clear();
                        minCol.push_back(i);
                        currMin = value;
                    } else if (value == currMin) {
                        minCol.push_back(i);
                    }
                    if (currMin == -1) {
                        break;
                    }
                }
            }
            if (currMin == -1 || remainDepth == 0) {
                targetValue = currMin;
                targetCol = minCol[rand() % int(minCol.size())];
            } else {
                float currMin = 1.1;
                std::vector<int> minCol;
                minCol.push_back(1.1);
                for (int i = 0; i < colNum; i++) {
                    if (checkBoard[i][rowNum - 1] == Color::empty) {
                        int pos = -1;
                        float value = 0;
                        int nextDepth = remainDepth - 1;
                        std::vector<std::vector<Color>> boardCopy = checkBoard;
                        setBoard(i, Color::red, boardCopy);
                        findColWithMinMax(boardCopy, nextDepth, true, pos,
                                          value);
                        if (value < currMin) {
                            minCol.clear();
                            minCol.push_back(i);
                            currMin = value;
                        } else if (value == currMin) {
                            minCol.push_back(i);
                        }
                        if (currMin == -1) {
                            break;
                        }
                    }
                }
                targetCol = minCol[rand() % int(minCol.size())];
                targetValue = currMin;
            }
        }
    }
}