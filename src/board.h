#pragma once
#include <vector>
#include <raylib.h>

class Board
{
public:
    Board(int cols);
    Board();
    void Initialize();
    void Print();
    void Draw();
    bool IsCellOutside(int row, int column);
    bool IsCellEmpty(int row, int column);
    void setHardMode(bool isHardMode);
    int ClearFullRows();
    int **grid;
private:
    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowDown(int row, int numRows);
    int numRows;
    int numCols;
    int numCols_h;
    int cellSize;
    std::vector<Color> colors;
};