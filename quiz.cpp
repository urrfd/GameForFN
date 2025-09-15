#include "quiz.h"

void UpdateQuiz(GameScreen* currentScreen, const char** victoryMsg) {
    if (IsKeyPressed(KEY_SPACE)) {
        *currentScreen = VICTORY;
        *victoryMsg = "You beat the QUIZ!";
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        *currentScreen = MENU;
    }
}

void DrawQuiz() {
    DrawText("QUIZ SCREEN!", 280, 200, 40, RED);
    DrawText("Press [SPACE] to WIN", 250, 300, 30, DARKGRAY);
}
