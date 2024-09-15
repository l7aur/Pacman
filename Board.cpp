#include "Board.h"
#include <mem.h>

const float ERROR = 14.0f;
const float BORDER_SIZE = 10.0f;
const float TUNNEL_SIZE = 40.0f + ERROR + BORDER_SIZE;

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
    // Left walls
    coverage.push_back(Rectangle{0, 0, BORDER_SIZE, static_cast<float>(n) / 2 - TUNNEL_SIZE});
    coverage.push_back(Rectangle{0, static_cast<float>(n) / 2, BORDER_SIZE, static_cast<float>(n) / 2});
    // Right walls
    coverage.push_back(Rectangle{static_cast<float>(m) - BORDER_SIZE, 0, BORDER_SIZE, static_cast<float>(n) / 2 - TUNNEL_SIZE});
    coverage.push_back(Rectangle{static_cast<float>(m) - BORDER_SIZE, static_cast<float>(n) / 2, BORDER_SIZE, static_cast<float>(n) / 2});
    // Upper walls
    coverage.push_back(Rectangle{0, 0, static_cast<float>(m), BORDER_SIZE});
    // Lower walls
    coverage.push_back(Rectangle{0, static_cast<float>(n) - BORDER_SIZE, static_cast<float>(m), BORDER_SIZE});
    // Inner walls
    coverage.push_back(Rectangle{TUNNEL_SIZE, TUNNEL_SIZE, 200.0f - TUNNEL_SIZE, BORDER_SIZE});
    coverage.push_back(Rectangle{TUNNEL_SIZE + 200.0f, TUNNEL_SIZE, static_cast<float>(m) - 2 * TUNNEL_SIZE - 200.0f, BORDER_SIZE});
    coverage.push_back(Rectangle{2 * TUNNEL_SIZE, static_cast<float>(n) - TUNNEL_SIZE - BORDER_SIZE, static_cast<float>(m) - 2 * TUNNEL_SIZE, BORDER_SIZE});
    coverage.push_back(Rectangle{TUNNEL_SIZE, TUNNEL_SIZE, BORDER_SIZE, 246.0f});
    coverage.push_back(Rectangle{TUNNEL_SIZE, 2 * TUNNEL_SIZE + 350.0f, BORDER_SIZE, static_cast<float>(n) - 3 * TUNNEL_SIZE - 250.0f});
    coverage.push_back(Rectangle{static_cast<float>(m) - TUNNEL_SIZE - BORDER_SIZE, 0, BORDER_SIZE, 70.0f});
    coverage.push_back(Rectangle{0, static_cast<float>(n) / 2, 70.0f, BORDER_SIZE});
    coverage.push_back(Rectangle{static_cast<float>(m) - TUNNEL_SIZE - BORDER_SIZE, TUNNEL_SIZE + 100.0f, BORDER_SIZE, static_cast<float>(n) - 3 * TUNNEL_SIZE - 100.0f});
    coverage.push_back(Rectangle{2 * TUNNEL_SIZE, 2 * TUNNEL_SIZE, 300.0f, BORDER_SIZE});
    coverage.push_back(Rectangle{2 * TUNNEL_SIZE, 2 * TUNNEL_SIZE, BORDER_SIZE, 200.0f});
    coverage.push_back(Rectangle{300.0f, 2 * TUNNEL_SIZE, BORDER_SIZE, 200.0f});
    coverage.push_back(Rectangle{300.0f, 250.0f, 365.0f, BORDER_SIZE});
    coverage.push_back(Rectangle{590.0f, 225.0f - TUNNEL_SIZE, 200.0f, BORDER_SIZE});
    coverage.push_back(Rectangle{210.0f, 3 * TUNNEL_SIZE, BORDER_SIZE, 260.0f});
    coverage.push_back(Rectangle{430.0f, 250.0f + TUNNEL_SIZE, 300.0f, BORDER_SIZE});
    coverage.push_back(Rectangle{430.0f, 250.0f + TUNNEL_SIZE, BORDER_SIZE, 100.0f});
    coverage.push_back(Rectangle{210.0f, 510.0f - TUNNEL_SIZE, 100.0f, BORDER_SIZE});
    coverage.push_back(Rectangle{410.0f, 530.0f - TUNNEL_SIZE, 200.0f, BORDER_SIZE});
    coverage.push_back(Rectangle{500.0f, 445.0f - TUNNEL_SIZE, 165.0f, BORDER_SIZE});
    coverage.push_back(Rectangle{70.0f, 530.0f - 2 * TUNNEL_SIZE, 150.0f, BORDER_SIZE});
    coverage.push_back(Rectangle{600.0f, 450.0f - 2 * TUNNEL_SIZE, BORDER_SIZE, 150.0f});
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
