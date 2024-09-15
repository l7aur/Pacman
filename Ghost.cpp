#include "Ghost.h"

Ghost::Ghost()
{
    texture = LoadTexture("sprites\\RealThreat.png");
    numberOfFrames = 1;
    width = texture.width;
    height = texture.height;
    scale = 0.25f;
    position = {200.0f, 200.0f};
}

Ghost::~Ghost()
{
    UnloadTexture(texture);
}

void Ghost::updateFrame(const float deltaTime)
{
    frame = 0;
    frameRunningTime += deltaTime;
    if(frameRunningTime > maximumFrameTime)
        frameRunningTime = 0.0f;
}

Vector2 Ghost::createRandomDisplacement()
{
    Vector2 v = {0.0f, 0.0f};
    int test = rand() % 2;
    v.x = (test) ? 1.0f : 0.0f;
    v.y = (test) ? 0.0f : 1.0f;
    return Vector2Scale(v, (rand() % 2) ? 1.0f : -1.0f);
}

void Ghost::updateDirection(const Vector2 displacement)
{
    direction = (displacement.x < 0) ? -1 : 1;
}