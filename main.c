#include "raylib.h"

int main()
{

    InitWindow(600, 600, "Test App");
    SetTargetFPS(60);
    Rectangle main_Rect = {150, 200, 300, 200};
    Rectangle small_Rect = {0, 0, 80, 80};
    Rectangle temp_rect = {0, 0, 80, 80};
    Rectangle collision_Rect = {0};
    int collision = 0;

    while (!WindowShouldClose())
    {
        // Updating

        // temp_rect is a transparent temporary rect that has the same dimensions as small_rect.
        // we synced it with the mouse movement to detect the collision with the main_Rect.
        temp_rect.x = GetMouseX() - temp_rect.width / 2;
        temp_rect.y = GetMouseY() - temp_rect.height / 2; 

        // we check for the collision, if there's no collision we update small_rect position
        collision = CheckCollisionRecs(temp_rect, main_Rect);
        if(!collision){
         
            small_Rect.x = GetMouseX() - small_Rect.width / 2;
            small_Rect.y = GetMouseY() - small_Rect.height / 2;
        }

        //keep small_rect within the borders of the window
        if (small_Rect.x + small_Rect.width >= 600)
            small_Rect.x = 600 - small_Rect.width;
        else if (small_Rect.x <= 0)
            small_Rect.x = 0;

        if (small_Rect.y + small_Rect.height >= 600)
            small_Rect.y = 600 - small_Rect.height;
        else if (small_Rect.y <= 0)
            small_Rect.y = 0;

       
        
        

        // Drawing
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        DrawRectangleRec(main_Rect, BEIGE);
        DrawRectangleRec(small_Rect, BROWN);
        DrawRectangleRec(temp_rect, BLANK); // blank means transparent

        EndDrawing();
    }

    CloseWindow();
}