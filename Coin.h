#ifndef COIN_H
#define COIN_H

#include "raylib.h"

class Coin
{
public:
    Coin(const bool coinType, const Vector2 pos);
    ~Coin();
    void draw() const;
    void updateFrame(const float deltaTime);
    int getValue() const { return this->value; };
    Rectangle getBoundingBox() const;

private:
    const Texture2D texture{LoadTexture("sprites\\BigCoin.png")};
    int frame{0};
    const int numberOfFrames{8};
    float scale{1.0f};
    Vector2 position{0.0f, 0.0f};
    float frameRunningTime{0.0f};
    const float maximumFrameTime{0.0625f};
    int value{0};
};

#endif