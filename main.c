#include "raylib.h"

typedef struct Player
{
    Vector2 position;
    float speed;
    bool can_jump;
} Player;

typedef struct Env_element
{
    Rectangle env_rect;

    // Blocking determine whether this environment element is a decorative element
    // OR it's a solid element that the player can hit
    // Background : blocking = 0
    // Ground or Platforms : blocking = 1
    int blocking;

    Color Env_element_color;
} Env_element;

#define MAX_ENV_ELEMENT 4
#define GRAVITY 400
#define HOR_SPD 200
#define JMP_SPD 350

int main()
{
    InitWindow(600, 600, "Platformer Game");
    SetTargetFPS(60);

    // Set player
    Player player = {(Vector2){275, 350}, 0, false};

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
        float delta_time = GetFrameTime();

        // Collision Logic
        int hit_element = 0;
        for (int i = 0; i < MAX_ENV_ELEMENT; i++)
        {
            Env_element *element = &enviroment[i];
            Vector2 *plyr = &(player.position);

            // To check these conditions, consider you are at the top of the platform
            //  50 is the height of the player
            if (
                (element->blocking) &&
                (element->env_rect.x <= plyr->x) &&
                (element->env_rect.x + element->env_rect.width >= plyr->x) &&
                (element->env_rect.y >= plyr->y + 50) &&
                (element->env_rect.y <= plyr->y + player.speed * delta_time + 50))
            {
                hit_element = 1;
                plyr->y = element->env_rect.y - 50;
                player.speed = 0;
            }
        }

        if (!hit_element)
        {
            // The player didn't hit a platform :
            //   - Then he's falling due to gravity
            //   - the position of the player keeps getting updated by its speed
            //   - and the speed keeps getting updated by the gravity
            player.position.y += player.speed * delta_time;
            player.speed += GRAVITY * delta_time;

            // here player can't jump because he's already in the air , he's not sitting
            player.can_jump = false;
        }
        else
        {
            // the player is sitting on the platform , now it can jump
            player.can_jump = true;
        }

        // Make player Move with keys
        if (IsKeyDown(KEY_LEFT))
            player.position.x -= HOR_SPD * delta_time;
        if (IsKeyDown(KEY_RIGHT))
            player.position.x += HOR_SPD * delta_time;

        //if we press SPACE and the player is sitting
        if (IsKeyDown(KEY_SPACE) && player.can_jump)
        {
            player.speed = -JMP_SPD; // negative, to move up

            // here player can't jump because he's already in the air , he's not sitting
            player.can_jump = false;
        }

        // Drawing
        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        for (int i = 0; i < MAX_ENV_ELEMENT; i++)
        {
            DrawRectangleRec(enviroment[i].env_rect, enviroment[i].Env_element_color);
        }

        // The player MUST be drawn after the environment
        // because in environment , we draw the background as well
        DrawRectangleRec((Rectangle){player.position.x, player.position.y, 50, 50}, RED);

        EndDrawing();
    }

    CloseWindow();
}