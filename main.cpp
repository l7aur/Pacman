#include <iostream>
#include "raylib.h"

#include "Board.h"
#include "PacWoman.h"

const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 800;
const Color WALL_COLOR = WHITE;

Vector2 handle_keyboard_movement();

int main()
{

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "PAC WOMAN");
    SetTargetFPS(120);

    Board *board = new Board(WINDOW_WIDTH, WINDOW_HEIGHT);
    board->createLayout1();

    PacWoman *pac = new PacWoman();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        board->draw(WALL_COLOR);

        pac->draw();
        Vector2 pacPositionDisplacement = handle_keyboard_movement();
        pac->updatePosition(pacPositionDisplacement);
        if (!board->isValidLocation(pac->getBoundingBox()))
            pac->updatePosition(Vector2Negate(pacPositionDisplacement));

        EndDrawing();
    }

    return 0;
}

Vector2 handle_keyboard_movement()
{
    Vector2 v{0.0f, 0.0f};
    if (IsKeyDown(KEY_W))
        v.y -= 1.0f;
    if (IsKeyDown(KEY_S))
        v.y += 1.0f;
    if (IsKeyDown(KEY_A))
        v.x -= 1.0f;
    if (IsKeyDown(KEY_D))
        v.x += 1.0f;
    return v;
}
