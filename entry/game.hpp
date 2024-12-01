#ifndef GAME_HPP
#define GAME_HPP

#include "field.hpp"

enum GameStatus {
    Win,
    Lose,
    InProgress
};

class Game {
public:
    Field field;
    Game(int rows, int cols, int mines) : field(rows, cols, mines) {}
    
    GameStatus getStatus() {
        if (field.getCellsOpen() == field.getCols() * field.getRows() - field.getMines()) {
            return GameStatus::Win;
        } else if (field.getMineIsOpen()) {
            return GameStatus::Lose;
        }
        return GameStatus::InProgress;
    }

};
#endif