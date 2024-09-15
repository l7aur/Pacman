#include "PacWoman.h"

PacWoman::PacWoman()
{
    texture = LoadTexture("sprites\\PacMan.png");
    numberOfFrames = 8;
    position = {400.0f, 300.0f};
    width = height = 16;
    scale = 3.0f;
    velocity = 3.0f;
}

PacWoman::~PacWoman()
{
    UnloadTexture(texture);
}

void PacWoman::updateFrame(const float deltaTime)
{
    frameRunningTime += deltaTime;
    if (frameRunningTime >= maximumFrameTime)
    {
        frame = (frame + 1) % numberOfFrames;
        frameRunningTime = 0.0f;
    }
}
