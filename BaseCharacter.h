#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"
#include "raymath.h"

class BaseCharacter
{
public:
    void draw() const;
    inline void updatePosition(Vector2 v) { position = Vector2Add(position, Vector2Scale(v, velocity)); };
    virtual Rectangle getBoundingBox() const = 0;
    inline Vector2 getPosition() const { return this->position; };
    inline int getWidth() const { return this->width; };
    inline int getHeight() const {return this->height; };
    void handleTeleport(const int window_width, const int window_height);
    void updateDirection(const Vector2 displacement);
    virtual void updateFrame(const float deltaTime) = 0;

protected:
    Texture2D texture{};
    int frame{0};
    int numberOfFrames{0};
    Vector2 position{100.0f, 100.0f};
    int width{16};
    int height{16};
    int direction{1};
    float rotation{0.0f};
    float frameRunningTime{0.0f};
    const float maximumFrameTime{0.0625f};
    float scale{1.0f};
    float velocity{1.0f};

private:
};

#endif