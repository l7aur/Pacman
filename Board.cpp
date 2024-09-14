#include "Board.h"
#include <mem.h>

const float TUNNEL_SIZE = 20.0f;

Board::Board(const int width, const int height)
{
    n = height;
    m = width;
    data = new int *[height];
    for (int i = 0; i < height; i++)
        data[i] = new int[width];
}

void Board::createLayout1()
{
    const float borderSize = 10.0f;
    // Left walls
    coverage.push_back(Rectangle{0, 0, borderSize, static_cast<float>(n) / 2 - TUNNEL_SIZE / 2});
    coverage.push_back(Rectangle{0, static_cast<float>(n) / 2 + TUNNEL_SIZE / 2, borderSize, static_cast<float>(n) / 2 - TUNNEL_SIZE / 2});
    // Right walls
    coverage.push_back(Rectangle{static_cast<float>(m) - borderSize, 0, borderSize, static_cast<float>(n) / 2 - TUNNEL_SIZE / 2});
    coverage.push_back(Rectangle{static_cast<float>(m) - borderSize, static_cast<float>(n) / 2 + TUNNEL_SIZE / 2, borderSize, static_cast<float>(n) / 2 - TUNNEL_SIZE / 2});
    // Upper walls
    coverage.push_back(Rectangle{0, 0, static_cast<float>(m), TUNNEL_SIZE});
    // Lower walls
    coverage.push_back(Rectangle{0, static_cast<float>(n) - TUNNEL_SIZE, static_cast<float>(m), TUNNEL_SIZE});
}

void Board::draw(const Color wallColor) const
{
    for (auto i : coverage)
        DrawRectangle(i.x, i.y, i.width, i.height, wallColor);
}

bool Board::isValidLocation(Rectangle r) const
{
    for (auto i : coverage)
        if (CheckCollisionRecs(r, i))
            return false;
    return true;
}

Board::~Board()
{
    for (int i = 0; i < m; i++)
        delete[] data[i];
    delete[] data;
}
