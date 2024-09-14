#ifndef PAC_WOMAN_H
#define PAC_WOMAN_H

#include "raylib.h"
#include "raymath.h"

class PacWoman
{
public:
    PacWoman();
    ~PacWoman();
    void draw() const;
    inline void updatePosition(Vector2 v) { position = Vector2Add(position, v); };
    Rectangle getBoundingBox() const;
private:
    Texture2D texture{};
    int frame{0};
    int numberOfFrames{0};
    Vector2 position{400.0f, 300.0f};
    int width{50};
    int height{50};
};

#endif