#include "raylib.h"

typedef struct Player
{
    Rectangle player_rect;
    Vector2 position;
    float speed;
    bool can_jump;
} Player;

typedef struct Env_element
{
    Rectangle env_rect;
    int blocking;
    Color Env_element_color;
} Env_element;

#define MAX_ENV_ELEMENT 4

int main()
{
    InitWindow(600, 600, "Platformer Game");
    SetTargetFPS(60);

    // Set player
    Player player = {{270, 350, 50, 50}, (Vector2){275, 350}, 0, false};

    // Set Environment
    Env_element enviroment[MAX_ENV_ELEMENT] = {
        {{0, 0, 600, 600}, 0, BEIGE},    // background
        {{0, 400, 600, 200}, 1, BROWN},  // ground
        {{100, 330, 100, 10}, 1, BROWN}, // small platform
        {{200, 265, 300, 10}, 1, BROWN}  // wide platform
    };

    while (!WindowShouldClose())
    {
        // Updating

        // Drawing
        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        for (int i = 0; i < MAX_ENV_ELEMENT; i++)
        {
            DrawRectangleRec(enviroment[i].env_rect, enviroment[i].Env_element_color);
        }

        // The player MUST be drawn after the environment
        // because in environment , we draw the background as well
        DrawRectangleRec(player.player_rect, RED);

        EndDrawing();
    }

    CloseWindow();
}