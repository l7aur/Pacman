#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "raylib.h"

class Board {
public:
    Board(const int width, const int height);
    void createLayout1();
    void draw(const Color wallColor) const;
    bool isValidLocation(Rectangle r) const;
    ~Board();
private:
    int ** data{nullptr};
    std::vector<Rectangle> coverage;
    int n{0};
    int m{0};
};

#endif