#include "Ghost.h"

Ghost::Ghost()
{
    texture = LoadTexture("sprites\\RealThreat.png");
    numberOfFrames = 1;
    width = texture.width;
    height = texture.height;
    scale = 0.25f;
}

Ghost::~Ghost()
{
    UnloadTexture(texture);
}

void Ghost::updateFrame(const float deltaTime)
{
    frame = 0;
}

Rectangle Ghost::getBoundingBox() const
{
    return Rectangle{};
}
