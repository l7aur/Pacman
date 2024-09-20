#include <iostream>
#include <vector>
#include <string>

#include "raylib.h"
#include "Board.h"
#include "PacWoman.h"
#include "Ghost.h"
#include "Coin.h"

const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 800;
const Color WALL_COLOR = Color{0, 101, 101, 255};
const Color TEXT_COLOR = Color{180, 120, 255, 255};
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
    std::string endText = "GAME NOT ENDED!"; 
    std::pair<int, int> textPosition = {250, 300};

    Vector2 ghostPositionDisplacement[GHOST_NUMBER];
    Vector2 pacPositionDisplacement{0.0f, 0.0f};

    bool gameEnded = false;
    int score = 0;

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
                score += (*coin)->getValue();
                coins.erase(coin);
            }
            else
                coin++;
        }

        // End conditions
        if ((gameEnded = didPacDie(pac, ghost)) == true) {
            endText = "GAME OVER! THREATS WON!";
            textPosition.first = 190;
        }
        if (coins.empty())
        {
            endText = "PACMAN WON! Score: " + std::to_string(score);
            textPosition.first = 230;
            gameEnded = true;
        }

        EndDrawing();
        
        // End game loop
        while (gameEnded && !IsKeyPressed(KEY_Q) && !WindowShouldClose())
        {
            BeginDrawing();
            ClearBackground(BLACK);
            board->draw(WALL_COLOR);
            pac->draw();
            pac->updateFrame(deltaTime);
            for (int i = 0; i < GHOST_NUMBER; i++)
                ghost[i]->draw();
            DrawText(endText.c_str(), textPosition.first, textPosition.second, 30, TEXT_COLOR);
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
    coins.push_back(new Coin(SMALL_COIN, {380.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {415.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {450.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {485.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {520.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {555.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {590.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {625.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {660.0f, 22.0f}));
    coins.push_back(new Coin(SMALL_COIN, {695.0f, 22.0f}));
    coins.push_back(new Coin(BIG_COIN, {735.0f, 10.0f}));
    coins.push_back(new Coin(SMALL_COIN, {20.0f, 85.0f}));
    coins.push_back(new Coin(SMALL_COIN, {80.0f, 85.0f}));
    coins.push_back(new Coin(SMALL_COIN, {115.0f, 85.0f}));
    coins.push_back(new Coin(SMALL_COIN, {150.0f, 85.0f}));
    coins.push_back(new Coin(SMALL_COIN, {185.0f, 85.0f}));
    coins.push_back(new Coin(SMALL_COIN, {220.0f, 85.0f}));
    coins.push_back(new Coin(SMALL_COIN, {255.0f, 85.0f}));
    coins.push_back(new Coin(SMALL_COIN, {290.0f, 85.0f}));
    coins.push_back(new Coin(SMALL_COIN, {325.0f, 85.0f}));
    coins.push_back(new Coin(SMALL_COIN, {360.0f, 85.0f}));
    coins.push_back(new Coin(SMALL_COIN, {395.0f, 85.0f}));
    coins.push_back(new Coin(SMALL_COIN, {430.0f, 85.0f}));
    coins.push_back(new Coin(SMALL_COIN, {465.0f, 85.0f}));
    coins.push_back(new Coin(SMALL_COIN, {500.0f, 85.0f}));
    coins.push_back(new Coin(SMALL_COIN, {535.0f, 85.0f}));
    coins.push_back(new Coin(SMALL_COIN, {570.0f, 85.0f}));
    coins.push_back(new Coin(SMALL_COIN, {605.0f, 85.0f}));
    coins.push_back(new Coin(SMALL_COIN, {640.0f, 85.0f}));
    coins.push_back(new Coin(SMALL_COIN, {675.0f, 85.0f}));
    coins.push_back(new Coin(SMALL_COIN, {710.0f, 85.0f}));
    coins.push_back(new Coin(SMALL_COIN, {745.0f, 85.0f}));
    coins.push_back(new Coin(SMALL_COIN, {430.0f, 117.5f}));
    coins.push_back(new Coin(SMALL_COIN, {465.0f, 117.5f}));
    coins.push_back(new Coin(SMALL_COIN, {500.0f, 117.5f}));
    coins.push_back(new Coin(SMALL_COIN, {535.0f, 117.5f}));
    coins.push_back(new Coin(SMALL_COIN, {570.0f, 117.5f}));
    coins.push_back(new Coin(SMALL_COIN, {605.0f, 117.5f}));
    coins.push_back(new Coin(SMALL_COIN, {640.0f, 117.5f}));
    coins.push_back(new Coin(SMALL_COIN, {675.0f, 117.5f}));
    coins.push_back(new Coin(SMALL_COIN, {710.0f, 117.5f}));
    coins.push_back(new Coin(SMALL_COIN, {745.0f, 117.5f}));
    coins.push_back(new Coin(SMALL_COIN, {20.0f, 150.0f}));
    coins.push_back(new Coin(SMALL_COIN, {85.0f, 150.0f}));
    coins.push_back(new Coin(SMALL_COIN, {150.0f, 150.0f}));
    coins.push_back(new Coin(SMALL_COIN, {185.0f, 150.0f}));
    coins.push_back(new Coin(SMALL_COIN, {220.0f, 150.0f}));
    coins.push_back(new Coin(SMALL_COIN, {255.0f, 150.0f}));
    coins.push_back(new Coin(SMALL_COIN, {325.0f, 150.0f}));
    coins.push_back(new Coin(SMALL_COIN, {360.0f, 150.0f}));
    coins.push_back(new Coin(SMALL_COIN, {395.0f, 150.0f}));
    coins.push_back(new Coin(SMALL_COIN, {430.0f, 150.0f}));
    coins.push_back(new Coin(SMALL_COIN, {465.0f, 150.0f}));
    coins.push_back(new Coin(SMALL_COIN, {500.0f, 150.0f}));
    coins.push_back(new Coin(SMALL_COIN, {535.0f, 150.0f}));
    coins.push_back(new Coin(SMALL_COIN, {20.0f, 205.0f}));
    coins.push_back(new Coin(SMALL_COIN, {85.0f, 205.0f}));
    coins.push_back(new Coin(SMALL_COIN, {160.0f, 205.0f}));
    coins.push_back(new Coin(SMALL_COIN, {245.0f, 205.0f}));
    coins.push_back(new Coin(SMALL_COIN, {325.0f, 205.0f}));
    coins.push_back(new Coin(SMALL_COIN, {360.0f, 205.0f}));
    coins.push_back(new Coin(SMALL_COIN, {395.0f, 205.0f}));
    coins.push_back(new Coin(SMALL_COIN, {430.0f, 205.0f}));
    coins.push_back(new Coin(SMALL_COIN, {465.0f, 205.0f}));
    coins.push_back(new Coin(SMALL_COIN, {500.0f, 205.0f}));
    coins.push_back(new Coin(SMALL_COIN, {535.0f, 205.0f}));
    coins.push_back(new Coin(SMALL_COIN, {570.0f, 205.0f}));
    coins.push_back(new Coin(SMALL_COIN, {605.0f, 205.0f}));
    coins.push_back(new Coin(SMALL_COIN, {640.0f, 205.0f}));
    coins.push_back(new Coin(SMALL_COIN, {675.0f, 205.0f}));
    coins.push_back(new Coin(SMALL_COIN, {745.0f, 205.0f}));
    coins.push_back(new Coin(SMALL_COIN, {675.0f, 240.0f}));
    coins.push_back(new Coin(SMALL_COIN, {20.0f, 260.0f}));
    coins.push_back(new Coin(SMALL_COIN, {85.0f, 270.0f}));
    coins.push_back(new Coin(SMALL_COIN, {160.0f, 270.0f}));
    coins.push_back(new Coin(SMALL_COIN, {245.0f, 270.0f}));
    coins.push_back(new Coin(SMALL_COIN, {325.0f, 270.0f}));
    coins.push_back(new Coin(SMALL_COIN, {430.0f, 270.0f}));
    coins.push_back(new Coin(SMALL_COIN, {465.0f, 270.0f}));
    coins.push_back(new Coin(SMALL_COIN, {500.0f, 270.0f}));
    coins.push_back(new Coin(SMALL_COIN, {535.0f, 270.0f}));
    coins.push_back(new Coin(SMALL_COIN, {570.0f, 270.0f}));
    coins.push_back(new Coin(SMALL_COIN, {605.0f, 270.0f}));
    coins.push_back(new Coin(SMALL_COIN, {640.0f, 270.0f}));
    coins.push_back(new Coin(SMALL_COIN, {675.0f, 270.0f}));
    coins.push_back(new Coin(SMALL_COIN, {745.0f, 270.0f}));
    coins.push_back(new Coin(SMALL_COIN, {20.0f, 340.0f}));
    coins.push_back(new Coin(SMALL_COIN, {52.5f, 340.0f}));
    coins.push_back(new Coin(SMALL_COIN, {85.0f, 340.0f}));
    coins.push_back(new Coin(SMALL_COIN, {122.5f, 340.0f}));
    coins.push_back(new Coin(SMALL_COIN, {160.0f, 340.0f}));
    coins.push_back(new Coin(SMALL_COIN, {245.0f, 340.0f}));
    coins.push_back(new Coin(SMALL_COIN, {277.5f, 340.0f}));
    coins.push_back(new Coin(SMALL_COIN, {310.0f, 340.0f}));
    coins.push_back(new Coin(SMALL_COIN, {345.0f, 340.0f}));
    coins.push_back(new Coin(SMALL_COIN, {380.0f, 340.0f}));
    coins.push_back(new Coin(SMALL_COIN, {455.0f, 340.0f}));
    coins.push_back(new Coin(SMALL_COIN, {490.0f, 340.0f}));
    coins.push_back(new Coin(SMALL_COIN, {525.0f, 340.0f}));
    coins.push_back(new Coin(SMALL_COIN, {560.0f, 340.0f}));
    coins.push_back(new Coin(SMALL_COIN, {615.0f, 340.0f}));
    coins.push_back(new Coin(SMALL_COIN, {650.0f, 340.0f}));
    coins.push_back(new Coin(SMALL_COIN, {685.0f, 340.0f}));
    coins.push_back(new Coin(SMALL_COIN, {745.0f, 340.0f}));
    coins.push_back(new Coin(SMALL_COIN, {245.0f, 400.0f}));
    coins.push_back(new Coin(SMALL_COIN, {277.5f, 400.0f}));
    coins.push_back(new Coin(SMALL_COIN, {310.0f, 400.0f}));
    coins.push_back(new Coin(SMALL_COIN, {345.0f, 400.0f}));
    coins.push_back(new Coin(SMALL_COIN, {380.0f, 400.0f}));
    coins.push_back(new Coin(SMALL_COIN, {20.0f, 420.0f}));
    coins.push_back(new Coin(SMALL_COIN, {52.5f, 420.0f}));
    coins.push_back(new Coin(SMALL_COIN, {85.0f, 420.0f}));
    coins.push_back(new Coin(SMALL_COIN, {122.5f, 420.0f}));
    coins.push_back(new Coin(SMALL_COIN, {160.0f, 420.0f}));
    coins.push_back(new Coin(SMALL_COIN, {455.0f, 420.0f}));
    coins.push_back(new Coin(SMALL_COIN, {490.0f, 420.0f}));
    coins.push_back(new Coin(SMALL_COIN, {525.0f, 420.0f}));
    coins.push_back(new Coin(SMALL_COIN, {560.0f, 420.0f}));
    coins.push_back(new Coin(SMALL_COIN, {615.0f, 420.0f}));
    coins.push_back(new Coin(SMALL_COIN, {650.0f, 420.0f}));
    coins.push_back(new Coin(SMALL_COIN, {685.0f, 420.0f}));
    coins.push_back(new Coin(SMALL_COIN, {745.0f, 420.0f}));
    coins.push_back(new Coin(SMALL_COIN, {20.0f, 485.0f}));
    coins.push_back(new Coin(SMALL_COIN, {80.0f, 485.0f}));
    coins.push_back(new Coin(SMALL_COIN, {115.0f, 485.0f}));
    coins.push_back(new Coin(SMALL_COIN, {150.0f, 485.0f}));
    coins.push_back(new Coin(SMALL_COIN, {185.0f, 485.0f}));
    coins.push_back(new Coin(SMALL_COIN, {220.0f, 485.0f}));
    coins.push_back(new Coin(SMALL_COIN, {255.0f, 485.0f}));
    coins.push_back(new Coin(SMALL_COIN, {290.0f, 485.0f}));
    coins.push_back(new Coin(SMALL_COIN, {325.0f, 485.0f}));
    coins.push_back(new Coin(SMALL_COIN, {360.0f, 485.0f}));
    coins.push_back(new Coin(SMALL_COIN, {395.0f, 485.0f}));
    coins.push_back(new Coin(SMALL_COIN, {430.0f, 485.0f}));
    coins.push_back(new Coin(SMALL_COIN, {465.0f, 485.0f}));
    coins.push_back(new Coin(SMALL_COIN, {500.0f, 485.0f}));
    coins.push_back(new Coin(SMALL_COIN, {535.0f, 485.0f}));
    coins.push_back(new Coin(SMALL_COIN, {570.0f, 485.0f}));
    coins.push_back(new Coin(SMALL_COIN, {605.0f, 485.0f}));
    coins.push_back(new Coin(SMALL_COIN, {640.0f, 485.0f}));
    coins.push_back(new Coin(SMALL_COIN, {675.0f, 485.0f}));
    coins.push_back(new Coin(SMALL_COIN, {710.0f, 485.0f}));
    coins.push_back(new Coin(SMALL_COIN, {745.0f, 485.0f}));
    coins.push_back(new Coin(BIG_COIN, {10.0f, 530.0f}));
    coins.push_back(new Coin(SMALL_COIN, {80.0f, 545.0f}));
    coins.push_back(new Coin(SMALL_COIN, {115.0f, 545.0f}));
    coins.push_back(new Coin(SMALL_COIN, {150.0f, 545.0f}));
    coins.push_back(new Coin(SMALL_COIN, {185.0f, 545.0f}));
    coins.push_back(new Coin(SMALL_COIN, {220.0f, 545.0f}));
    coins.push_back(new Coin(SMALL_COIN, {255.0f, 545.0f}));
    coins.push_back(new Coin(SMALL_COIN, {290.0f, 545.0f}));
    coins.push_back(new Coin(SMALL_COIN, {325.0f, 545.0f}));
    coins.push_back(new Coin(SMALL_COIN, {360.0f, 545.0f}));
    coins.push_back(new Coin(SMALL_COIN, {395.0f, 545.0f}));
    coins.push_back(new Coin(SMALL_COIN, {430.0f, 545.0f}));
    coins.push_back(new Coin(SMALL_COIN, {465.0f, 545.0f}));
    coins.push_back(new Coin(SMALL_COIN, {500.0f, 545.0f}));
    coins.push_back(new Coin(SMALL_COIN, {535.0f, 545.0f}));
    coins.push_back(new Coin(SMALL_COIN, {570.0f, 545.0f}));
    coins.push_back(new Coin(SMALL_COIN, {605.0f, 545.0f}));
    coins.push_back(new Coin(SMALL_COIN, {640.0f, 545.0f}));
    coins.push_back(new Coin(SMALL_COIN, {675.0f, 545.0f}));
    coins.push_back(new Coin(SMALL_COIN, {710.0f, 545.0f}));
    coins.push_back(new Coin(BIG_COIN, {735.0f, 530.0f}));
}
