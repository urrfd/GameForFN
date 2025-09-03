#include "raylib.h"

typedef enum GameScreen { MENU, QUIZ } GameScreen;

int main(void) {
    // Window setup
    InitWindow(800, 600, "Quiz Game");
    SetTargetFPS(60);

    GameScreen currentScreen = MENU;

    // Main loop
    while (!WindowShouldClose()) {
        // Update
        if (currentScreen == MENU) {
            if (IsKeyPressed(KEY_ONE)) currentScreen = QUIZ;  // Press 1 to start
            if (IsKeyPressed(KEY_TWO)) break;                 // Press 2 to exit
        }
        else if (currentScreen == QUIZ) {
            if (IsKeyPressed(KEY_ESCAPE)) currentScreen = MENU; // Go back to menu
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (currentScreen == MENU) {
            DrawText("== QUIZ GAME ==", 260, 100, 40, DARKBLUE);
            DrawText("Press [1] Start Quiz", 260, 200, 30, DARKGRAY);
            DrawText("Press [2] Exit",       260, 250, 30, DARKGRAY);
        }
        else if (currentScreen == QUIZ) {
            DrawText("QUIZ SCREEN!", 280, 200, 40, RED);
            DrawText("Press [ESC] to go back", 250, 300, 30, DARKGRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
