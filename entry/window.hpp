#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>

#include "textures.hpp"
#include "game.hpp"

using namespace std;

const int CELL_SIZE = 16;

class Window {
public:
    Window(const Game& game, const Textures& textures) : window(
            sf::VideoMode(game.field.getRows() * CELL_SIZE, game.field.getCols() * CELL_SIZE), 
            "Minesweeper",
            sf::Style::Titlebar | sf::Style::Close
        ), game(game), textures(textures) {
        window.setFramerateLimit(60);
    }

    void start() {
        bool isFirstClick = false;
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::MouseButtonPressed) {
                    int col = event.mouseButton.x / CELL_SIZE;
                    int row = event.mouseButton.y / CELL_SIZE;

                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if (!isFirstClick) {
                            game.field.placeMines(row, col);
                            isFirstClick = true;
                        }
                        game.field.openCell(row, col);
                    } else if (event.mouseButton.button == sf::Mouse::Right) {
                        game.field.toggleFlag(row, col);
                    }
                }
            }

            window.clear();

            const auto& grid = game.field.getGrid();
            for (int row = 0; row < game.field.getRows(); ++row) {
                for (int col = 0; col < game.field.getCols(); ++col) {
                    sf::Sprite sprite;

                    if (grid[row][col].getType() == Closed) {
                        sprite.setTexture(textures.hidden);
                    } else if (grid[row][col].getType() == Opened) {
                        int adjMines = grid[row][col].getAdjacentMines();
                        if (grid[row][col].isHasMine()) {
                            sprite.setTexture(textures.mine);
                        } else if (adjMines == 0) {
                            sprite.setTexture(textures.opened);
                        } else {
                            sprite.setTexture(textures.numbers[adjMines - 1]);
                        }
                    } else if (grid[row][col].getType() == Flagged) {
                        sprite.setTexture(textures.flag);
                    }

                    sprite.setPosition(col * CELL_SIZE, row * CELL_SIZE);
                    window.draw(sprite);
                }
            }

            window.display();

            if (game.getStatus() == GameStatus::Win) {
                cout << "You win" << endl;
                break;
            } else if (game.getStatus() == GameStatus::Lose) {
                cout << "You lose" << endl;
                break;
            }
        }
    }
private:
    sf::RenderWindow window;
    Textures textures;
    Game game;
};

#endif