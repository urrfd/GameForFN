#include "shared.h"
#include "quiz.h"
#include "collect.h"
#include "dodge.h"

int main(void) {
    InitWindow(800, 600, "Quiz + Minigames");
    SetTargetFPS(60);

    GameScreen currentScreen = MENU;
    const char* victoryMsg = "YOU WIN!";

    while (!WindowShouldClose()) {
        // --- UPDATE ---
        switch (currentScreen) {
            case MENU:
                if (IsKeyPressed(KEY_ONE)) currentScreen = QUIZ;
                if (IsKeyPressed(KEY_TWO)) currentScreen = DODGE;
                if (IsKeyPressed(KEY_THREE)) currentScreen = COLLECT;
                break;
            case QUIZ:    UpdateQuiz(&currentScreen, &victoryMsg); break;
            case DODGE:   UpdateDodge(&currentScreen, &victoryMsg); break;
            case COLLECT: UpdateCollect(&currentScreen, &victoryMsg); break;
            case VICTORY:
                if (IsKeyPressed(KEY_M)) currentScreen = MENU;
                break;
        }

        // --- DRAW ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentScreen) {
            case MENU:
                DrawText("== MAIN MENU ==", 260, 100, 40, DARKBLUE);
                DrawText("Press [1] Quiz", 260, 200, 30, DARKGRAY);
                DrawText("Press [2] Dodge", 260, 250, 30, DARKGRAY);
                DrawText("Press [3] Collect", 260, 300, 30, DARKGRAY);
                break;
            case QUIZ:    DrawQuiz(); break;
            case DODGE:   DrawDodge(); break;
            case COLLECT: DrawCollect(); break;
            case VICTORY:
                DrawText(victoryMsg, 200, 200, 40, GREEN);
                DrawText("Press [M] to return to Menu", 200, 300, 30, DARKGRAY);
                break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
