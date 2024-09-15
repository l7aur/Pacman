#include <iostream>
#include "raylib.h"

#include "Board.h"
#include "PacWoman.h"
#include "Ghost.h"

const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 800;
const Color WALL_COLOR = BLUE;

Vector2 handle_keyboard_movement();

int main()
{

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "PAC WOMAN");
    SetTargetFPS(120);

    Board *board = new Board(WINDOW_WIDTH, WINDOW_HEIGHT);
    board->createLayout1();

    PacWoman *pac = new PacWoman();
    Ghost * ghost = new Ghost();

    Vector2 ghostPositionDisplacement{1.0f, 0.0f};
    Vector2 pacPositionDisplacement{0.0f, 0.0f};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        float deltaTime = GetFrameTime();

        //Board
        board->draw(WALL_COLOR);

        //Pac
        pac->draw();
        pac->updateFrame(deltaTime);
        pacPositionDisplacement = handle_keyboard_movement();
        pac->updatePosition(pacPositionDisplacement);
        pac->updateDirection(pacPositionDisplacement);
        if (!board->isValidLocation(pac->getBoundingBox()))
            pac->updatePosition(Vector2Negate(pacPositionDisplacement));
        pac->handleTeleport(WINDOW_WIDTH, WINDOW_HEIGHT);

        //Ghost
        ghost->draw();
        ghost->updatePosition(ghostPositionDisplacement);
        ghost->updateDirection(ghostPositionDisplacement);
        if (!board->isValidLocation(ghost->getBoundingBox())) {
            ghost->updatePosition(Vector2Negate(ghostPositionDisplacement));
            ghostPositionDisplacement = ghost->createRandomDisplacement();
        }
        ghost->handleTeleport(WINDOW_WIDTH, WINDOW_HEIGHT);

        EndDrawing();
    }

    return 0;
}

Vector2 handle_keyboard_movement()
{
    if (IsKeyDown(KEY_W))
        return Vector2{0.0f, -1.0f};
    if (IsKeyDown(KEY_S))
        return Vector2{0.0f, 1.0f};
    if (IsKeyDown(KEY_A))
        return Vector2{-1.0f, 0.0f};
    if (IsKeyDown(KEY_D))
        return Vector2{1.0f, 0.0f};
    return Vector2{0.0f, 0.0f};
}
