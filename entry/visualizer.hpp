#ifndef IWINDOW_HPP
#define IWINDOW_HPP

class Visualizer {
public:
    Visualizer(Game& game) : game(game) {}

    virtual ~Visualizer() = default;

    virtual void start() = 0;
protected:
    Game& game;
};

#endif
