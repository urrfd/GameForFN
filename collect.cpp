#include "collect.h"

static Rectangle trash = { -50, 300, 40, 40 };
static Vector2 velocity = { 3, 0 };

void UpdateCollect(GameScreen* currentScreen, const char** victoryMsg) {
    Vector2 mouse = GetMousePosition();
    Rectangle mousehitbox = { mouse.x, mouse.y, 10, 10 };

    trash.x += velocity.x;
    if (trash.x > GetScreenWidth()) {
        trash.x = -trash.width;
    }

    if (CheckCollisionRecs(mousehitbox, trash) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        *currentScreen = VICTORY;
        *victoryMsg = "You won the COLLECT game!";
    }

    if (IsKeyPressed(KEY_ESCAPE)) {
        *currentScreen = MENU;
    }
}

void DrawCollect() {
    DrawText("Click the red square to win!", 200, 40, 20, DARKGRAY);
    DrawRectangleRec(trash, RED);

    Vector2 mouse = GetMousePosition();
    Rectangle mousehitbox = { mouse.x, mouse.y, 10, 10 };
    DrawRectangleRec(mousehitbox, BLUE);
}
