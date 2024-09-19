#include "Coin.h"

Coin::Coin(const bool coinType, const Vector2 pos)
{
    scale = (coinType) ? 3.5f : 2.0f;
    position = pos;
}

Coin::~Coin()
{
    UnloadTexture(texture);
}

void Coin::draw() const
{
    const int width = texture.width / numberOfFrames;
    const int height = texture.height;
    DrawTexturePro(
        texture,
        Rectangle{static_cast<float>(width * frame), static_cast<float>(height), static_cast<float>(width), static_cast<float>(height)},
        Rectangle{position.x, position.y, static_cast<float>(scale * width), static_cast<float>(scale * height)},
        Vector2{0.0f, 0.0f},
        0.0f,
        WHITE);
}

void Coin::updateFrame(const float deltaTime)
{
    frameRunningTime += deltaTime;
    if (frameRunningTime > maximumFrameTime)
    {
        frameRunningTime = 0.0f;
        frame = (frame + 1) % numberOfFrames;
    }
}

Rectangle Coin::getBoundingBox() const
{
    const int width = texture.width / numberOfFrames;
    const int height = texture.height;
    DrawRectangleLines(position.x, position.y, static_cast<float>(width) * scale, static_cast<float>(height) * scale, RED);
    return Rectangle{position.x, position.y, static_cast<float>(width) * scale, static_cast<float>(height) * scale};
}
