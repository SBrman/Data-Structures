#include "../include/QuadTree.h"
#include "raylib.h"

int main() {
    InitWindow(800, 600, "My Raylib Game");
    SetTargetFPS(60);

    Custom::Rectangle r{ 0.0f, 0.0f, 800.0f, 600.0f };
    QuadTree qtree{ r, 4 };

    while (!WindowShouldClose())
    {


        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 mouse = GetMousePosition();
            Custom::Point p{ mouse.x, mouse.y };
            qtree.insert(p);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        qtree.draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}