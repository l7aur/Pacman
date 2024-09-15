#include "BaseCharacter.h"

void BaseCharacter::draw() const
{
    DrawTexturePro(texture,
                   Rectangle{static_cast<float>(width * frame), static_cast<float>(height), static_cast<float>(direction * width), static_cast<float>(height)},
                   Rectangle{position.x, position.y, static_cast<float>(scale * width), static_cast<float>(scale * height)},
                   Vector2{static_cast<float>(width * scale) / 2, static_cast<float>(height * scale) / 2},
                   rotation,
                   WHITE);
}

void BaseCharacter::handleTeleport(const int window_width, const int window_height)
{
    Vector2 currentPosition = position;
    const float PADDING = 2.0f;

    if (currentPosition.x <= -width)
        position = Vector2{window_width - PADDING, currentPosition.y};
    else if (currentPosition.x >= window_width)
        position = Vector2{-width + PADDING, currentPosition.y};
    else if (currentPosition.y <= -height)
        position = Vector2{currentPosition.x, window_height - PADDING};
    else if (currentPosition.y >= window_height)
        position = Vector2{currentPosition.x, -height + PADDING};
}

void BaseCharacter::updateDirection(const Vector2 displacement)
{
    if (displacement.x > 0)
    {
        direction = 1;
        rotation = 0.0f;
    }
    if (displacement.x < 0)
    {
        direction = -1;
        rotation = 0.0f;
    }
    if (displacement.y > 0)
    {
        direction = 1;
        rotation = 90.0f;
    }
    if (displacement.y < 0)
    {
        direction = 1;
        rotation = -90.0f;
    }
}
