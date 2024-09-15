#include <iostream>
#include "raylib.h"

#include "Board.h"
#include "PacWoman.h"
#include "Ghost.h"

const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 800;
const Color WALL_COLOR = BLUE;
const Color TEXT_COLOR = GREEN;
const int GHOST_NUMBER = 4;

Vector2 handle_keyboard_movement();
bool didPacDie(PacWoman *main, Ghost *threats[]);

int main()
{

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "PAC WOMAN");
    SetTargetFPS(120);

    Board *board = new Board(WINDOW_WIDTH, WINDOW_HEIGHT);

    PacWoman *pac = new PacWoman();
    Ghost *ghost[GHOST_NUMBER];

    Vector2 ghostPositionDisplacement[GHOST_NUMBER];
    Vector2 pacPositionDisplacement{0.0f, 0.0f};

    bool gameEnded = false;
    
    board->createLayout1();
    for (int i = 0; i < GHOST_NUMBER; i++)
    {
        ghost[i] = new Ghost();
        ghostPositionDisplacement[i] = ghost[i]->createRandomDisplacement();
    }
    

    while (!WindowShouldClose() && !gameEnded)
    {
        BeginDrawing();
        ClearBackground(BLACK);

        float deltaTime = GetFrameTime();

        // Board
        board->draw(WALL_COLOR);

        // Pac
        pac->draw();
        pac->updateFrame(deltaTime);
        pacPositionDisplacement = handle_keyboard_movement();
        pac->updatePosition(pacPositionDisplacement);
        pac->updateDirection(pacPositionDisplacement);
        if (!board->isValidLocation(pac->getBoundingBox()))
            pac->updatePosition(Vector2Negate(pacPositionDisplacement));
        pac->handleTeleport(WINDOW_WIDTH, WINDOW_HEIGHT);

        // Ghost
        for (int i = 0; i < GHOST_NUMBER; i++)
        {
            ghost[i]->draw();
            ghost[i]->updatePosition(ghostPositionDisplacement[i]);
            ghost[i]->updateDirection(ghostPositionDisplacement[i]);
            if (!board->isValidLocation(ghost[i]->getBoundingBox()))
            {
                ghost[i]->updatePosition(Vector2Negate(ghostPositionDisplacement[i]));
                ghostPositionDisplacement[i] = ghost[i]->createRandomDisplacement();
            }
            ghost[i]->handleTeleport(WINDOW_WIDTH, WINDOW_HEIGHT);
        }
        if ((gameEnded = didPacDie(pac, ghost)) == true)
        {
            DrawText("GAME OVER! THREATS WON!", 200, 200, 30, TEXT_COLOR);
        }

        EndDrawing();
        if (gameEnded)
            WaitTime(5);
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

bool didPacDie(PacWoman *main, Ghost *threats[])
{
    Rectangle r = main->getBoundingBox();
    for (int i = 0; i < GHOST_NUMBER; i++)
        if (CheckCollisionRecs(r, threats[i]->getBoundingBox()) == true)
            return true;
    return false;
}
