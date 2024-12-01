#ifndef CELL_HPP
#define CELL_HPP

enum CellType {
    Opened,
    Flagged,
    Closed
};

class Cell {
public:
    Cell() : type(Closed), hasMine(false) {}
    Cell(bool isHasMine) : type(Closed), hasMine(isHasMine) {}

    void setType(CellType type) { this->type = type; }

    CellType getType() const { return type; }

    int getAdjacentMines() const { return adjacentMines; }

    void setAdjacentMines(int adjacentMines) { this->adjacentMines = adjacentMines; }

    bool isHasMine() const { return hasMine; }

    void toggleFlag() {
        if (type == Closed) {
            type = Flagged;
        } else if (type == Flagged) {
            type = Closed;
        }
    }

    void open() {
        type = Opened;
    }
private:
    int adjacentMines;
    CellType type;
    bool hasMine;
};

#endif