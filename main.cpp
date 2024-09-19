#include <iostream>
#include <vector>
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

enum
{
    SMALL_COIN,
    BIG_COIN
};

Vector2 handle_keyboard_movement();
bool didPacDie(PacWoman *main, Ghost *threats[]);
void place_coins(std::vector<Coin *> &coins);

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "PAC WOMAN");
    InitAudioDevice();

    SetTargetFPS(120);

    // Instantiations
    Sound pickUpSound = LoadSound("sounds\\pickup.ogg");

    Board *board = new Board(WINDOW_WIDTH, WINDOW_HEIGHT);
    PacWoman *pac = new PacWoman();
    Ghost *ghost[GHOST_NUMBER];
    std::vector<Coin *> coins;
    std::string endText;

    Vector2 ghostPositionDisplacement[GHOST_NUMBER];
    Vector2 pacPositionDisplacement{0.0f, 0.0f};

    bool gameEnded = false;

    // Initializations
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

    place_coins(coins);

    // Game loop
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
        for (auto coin = coins.begin(); coin != coins.end();)
        {
            (*coin)->draw();
            (*coin)->updateFrame(deltaTime);
            // Pick-up coins
            if (CheckCollisionRecs((*coin)->getBoundingBox(), pac->getBoundingBox()))
            {
                StopSound(pickUpSound);
                PlaySound(pickUpSound);
                coins.erase(coin);
            }
            else
                coin++;
        }

        // End conditions
        // if ((gameEnded = didPacDie(pac, ghost)) == true)
        //     endText = "GAME OVER! THREATS WON!";
        if (coins.empty())
        {
            endText = "PACMAN WON!";
            gameEnded = true;
        }

        EndDrawing();
        
        // End game loop
        while (gameEnded && !IsKeyPressed(KEY_Q) && !WindowShouldClose())
        {
            StopSound(pickUpSound);
            BeginDrawing();
            ClearBackground(BLACK);
            board->draw(WALL_COLOR);
            pac->draw();
            pac->updateFrame(deltaTime);
            for (int i = 0; i < GHOST_NUMBER; i++)
                ghost[i]->draw();
            DrawText(endText.c_str(), 200, 200, 30, TEXT_COLOR);
            EndDrawing();
        }
    }

    // Resource deallocation
    UnloadSound(pickUpSound);
    CloseAudioDevice();
    CloseWindow();
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

void place_coins(std::vector<Coin *> &coins)
{
    coins.push_back(new Coin(BIG_COIN, {10.0f, 10.0f}));
    coins.push_back(new Coin(SMALL_COIN, {65.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {100.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {135.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {170.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {205.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {240.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {275.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {310.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {345.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {370.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {405.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {440.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {475.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {510.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {545.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {580.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {615.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {650.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {685.0f, 22.0f}));
    // coins.push_back(new Coin(BIG_COIN, {735.0f, 10.0f}));
}
