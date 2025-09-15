#include "dodge.h"

static Vector2 player = { 400, 300 };

void UpdateDodge(GameScreen* currentScreen, const char** victoryMsg) {
    if (IsKeyDown(KEY_RIGHT)) player.x += 4;
    if (IsKeyDown(KEY_LEFT))  player.x -= 4;
    if (IsKeyDown(KEY_UP))    player.y -= 4;
    if (IsKeyDown(KEY_DOWN))  player.y += 4;

    if (player.x > 760) {
        *currentScreen = VICTORY;
        *victoryMsg = "You won the DODGE game!";
    }

    if (IsKeyPressed(KEY_ESCAPE)) {
        *currentScreen = MENU;
    }
}

void DrawDodge() {
    DrawText("DODGE GAME!", 280, 50, 40, RED);
    DrawText("Reach the right side to win!", 200, 100, 20, DARKGRAY);

    DrawRectangleV(player, (Vector2){40, 40}, BLUE);
}
