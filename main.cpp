#include <iostream>
#include "raylib.h"

#include "Board.h"
#include "PacWoman.h"
#include "Ghost.h"
#include "Coin.h"

const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 800;
const Color WALL_COLOR = BLUE;
const Color TEXT_COLOR = GREEN;
const int GHOST_NUMBER = 4;
const int SMALL_COIN_NUMBER = 2;
enum {
    SMALL_COIN,
    BIG_COIN
};

Vector2 handle_keyboard_movement();
bool didPacDie(PacWoman *main, Ghost *threats[]);
void place_coins(Coin *coins[]);

int main()
{

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "PAC WOMAN");
    SetTargetFPS(120);

    Board *board = new Board(WINDOW_WIDTH, WINDOW_HEIGHT);

    PacWoman *pac = new PacWoman();
    Ghost *ghost[GHOST_NUMBER];
    Coin *coin[SMALL_COIN_NUMBER];

    Vector2 ghostPositionDisplacement[GHOST_NUMBER];
    Vector2 pacPositionDisplacement{0.0f, 0.0f};

    bool gameEnded = false;

    board->createLayout1();
    for (int i = 0; i < GHOST_NUMBER; i++)
    {
        ghost[i] = new Ghost();
        ghostPositionDisplacement[i] = ghost[i]->createRandomDisplacement();
    }

    ghost[0]->setPosition(Vector2{230.0f, 95.0f});
    ghost[1]->setPosition(Vector2{250.0f, 350.0f});
    ghost[2]->setPosition(Vector2{100.0f, 450.0f});
    ghost[3]->setPosition(Vector2{640.0f, 415.0f});

    place_coins(coin);

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

        // Ghosts
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

        // Coins
        for(int i = 0; i<SMALL_COIN_NUMBER; i++) {
            coin[i]->draw();
            coin[i]->updateFrame(deltaTime);
        }

        // End condition
        // if ((gameEnded = didPacDie(pac, ghost)) == true)
        // {
        //     DrawText("GAME OVER! THREATS WON!", 200, 200, 30, TEXT_COLOR);
        // }

        EndDrawing();
        if (gameEnded)
            WaitTime(5);
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

bool didPacDie(PacWoman *main, Ghost *threats[])
{
    Rectangle r = main->getBoundingBox();
    for (int i = 0; i < GHOST_NUMBER; i++)
        if (CheckCollisionRecs(r, threats[i]->getBoundingBox()) == true)
            return true;
    return false;
}

void place_coins(Coin *coins[])
{
    coins[0] = new Coin(SMALL_COIN, {30.0f, 30.0f});
    coins[1] = new Coin(BIG_COIN, {100.0f, 30.0f});
}
