#include "PacWoman.h"

PacWoman::PacWoman()
{

}

PacWoman::~PacWoman()
{
    UnloadTexture(texture);
}

void PacWoman::draw() const
{
    DrawRectangle(position.x, position.y, 40, 40, RED);
}

Rectangle PacWoman::getBoundingBox() const
{
    return Rectangle{position.x, position.y, static_cast<float>(width), static_cast<float>(height)};
}
