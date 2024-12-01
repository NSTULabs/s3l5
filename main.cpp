#include <SFML/Graphics.hpp>
#include <iostream>

#include "entry/cell.hpp"
#include "entry/field.hpp"
#include "entry/textures.hpp"
#include "entry/game.hpp"
#include "entry/window.hpp"


int main() {
    const int rows = 10, cols = 10, mines = 10;

    srand(time(nullptr));

    Textures textures;
    Game game(rows, cols, mines);

    Window window(game, textures);
    window.start();

    return 0;
}
