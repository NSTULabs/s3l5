#ifndef FIELD_HPP
#define FIELD_HPP

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "cell.hpp"

using namespace std;

class Field {
public:
    Field(int rows, int cols, int mines)
        : rows(rows), cols(cols), mines(mines) {
        grid.resize(rows, vector<Cell>(cols));
    }

    // Open cell by click
    void openCell(int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            return;
        }
        if (grid[row][col].getType() == Opened) {
            openCellsAround(row, col);
            return;
        }
        if (grid[row][col].getType() == Flagged) {
            return;
        }
        if (grid[row][col].isHasMine()) {
            grid[row][col].open();
            mineIsOpen = true;
            return;
        }

        openNeighborCells(row, col);
    }

    void placeMines(int firstRow, int firstCol) {
        for (int i = 0; i < mines; ++i) {
            int row, col;
            do {
                row = rand() % rows;
                col = rand() % cols;
            } while (grid[row][col].isHasMine() || (row + 1 >= firstRow && row - 1 <= firstRow && col + 1 >= firstCol && col - 1 <= firstCol));
            grid[row][col] = new Cell(true);
        }
        calculateAdjacency();
    }

    vector<vector<Cell>>& getGrid() {
        return grid;
    }

    int getCellsOpen() const { return cellsOpen; }

    bool getMineIsOpen() const { return mineIsOpen; }

    int getRows() const { return rows; }

    int getCols() const { return cols; }

    int getMines() const { return mines; }
private:
    int rows, cols, mines;
    int cellsOpen = 0;
    bool mineIsOpen = false;
    vector<vector<Cell>> grid;

    // Open cells if click on opened cell
    void openCellsAround(int row, int col) {
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                int y = row + dr;
                int x = col + dc;
                if (!(dr == 0 && dc == 0) && grid[y][x].getType() == Closed) {
                    grid[y][x].open();
                    if (grid[y][x].isHasMine()) {
                        mineIsOpen = true;
                    }
                }
            }
        }
    }

    // Open neighbor cells if cell don't have mines around
    void openNeighborCells(int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols || grid[row][col].getType() != Closed) {
            return;
        }

        grid[row][col].open();
        cellsOpen++;

        if (grid[row][col].getAdjacentMines() > 0) {
            return;
        }

        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (!(dr == 0 && dc == 0)) {
                    openNeighborCells(row + dr, col + dc);
                }
            }
        }
    }

    void calculateAdjacency() {
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (grid[row][col].isHasMine()) continue;

                int mineCount = 0;
                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {
                        int r = row + dr;
                        int c = col + dc;
                        if (r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c].isHasMine()) {
                            ++mineCount;
                        }
                    }
                }
                grid[row][col].setAdjacentMines(mineCount);
            }
        }
    }
};

#endif