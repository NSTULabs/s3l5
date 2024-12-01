#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <SFML/Graphics.hpp>

using namespace std;

struct Textures {
    sf::Texture hidden, opened, mine, flag;
    sf::Texture numbers[8];

    Textures() {
        if (!hidden.loadFromFile("assets/not_open.png") ||
            !opened.loadFromFile("assets/empty.png") ||
            !mine.loadFromFile("assets/mine.png") ||
            !flag.loadFromFile("assets/flag.png")) {
            throw runtime_error("Error loading texture");
        }

        for (int i = 0; i < 8; ++i) {
            if (!numbers[i].loadFromFile("assets/numbers/" + to_string(i + 1) + ".png")) {
                throw runtime_error("Error loading number texture");
            }
        }
    }
};

#endif