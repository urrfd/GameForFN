#include "raylib.h"

typedef enum GameScreen { MENU, QUIZ, DODGE, COLLECT, VICTORY } GameScreen;

int main(void) {
    InitWindow(800, 600, "Quiz + Minigames");
    SetTargetFPS(60);

    // Things to collect
    Rectangle trash[3] = {
        { -50, 150, 40, 40 },
        { -100, 300, 50, 50 },
        { -200, 450, 30, 30 }
    };
    Vector2 velocity[3] = {
        { 3, 0 },
        { 2, 0 },
        { 4, 0 }
    };

    // Track collected state
    bool collected[3] = { false, false, false };

    // Player for the dodge game
    Vector2 player = {400, 300};

    GameScreen currentScreen = MENU;
    bool shouldExit = false;

    // Victory message
    const char *victoryMsg = "YOU WIN!";

    while (!WindowShouldClose() && !shouldExit) {
        // --- UPDATE ---
        switch (currentScreen) {
            case MENU:
                if (IsKeyPressed(KEY_ONE)) {
                    currentScreen = QUIZ;
                }
                if (IsKeyPressed(KEY_TWO)) {
                    currentScreen = DODGE;
                    player = (Vector2){400, 300}; // reset player
                }
                if (IsKeyPressed(KEY_THREE)) {
                    currentScreen = COLLECT;
                }
                break;

            case QUIZ:
                if (IsKeyPressed(KEY_SPACE)) {
                    currentScreen = VICTORY;
                    victoryMsg = "You beat the QUIZ!";
                }
                if (IsKeyPressed(KEY_ESCAPE)) {
                    currentScreen = MENU;
                }
                break;

            case DODGE:
                if (IsKeyDown(KEY_RIGHT)) player.x += 4;
                if (IsKeyDown(KEY_LEFT))  player.x -= 4;
                if (IsKeyDown(KEY_UP))    player.y -= 4;
                if (IsKeyDown(KEY_DOWN))  player.y += 4;

                if (player.x > 760) {
                    currentScreen = VICTORY;
                    victoryMsg = "You won the DODGE game!";
                }

                if (IsKeyPressed(KEY_ESCAPE)) {
                    currentScreen = MENU;
                }
                break;

            case COLLECT: {
                // Update mouse hitbox
                Vector2 mouse = GetMousePosition();
                Rectangle mousehitbox = {mouse.x, mouse.y, 10, 10};

                for (int i = 0; i < 3; i++) {
                    // Move trash if not collected
                    if (!collected[i]) {
                        trash[i].x += velocity[i].x;

                        // Wrap around when off screen
                        if (trash[i].x > GetScreenWidth()) {
                            trash[i].x = -trash[i].width;
                        }

                        // Check collection
                        if (CheckCollisionRecs(mousehitbox, trash[i]) &&
                            IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                            collected[i] = true;

                            // Respawn at left side, random y position
                            trash[i].x = -trash[i].width;
                            trash[i].y = GetRandomValue(100, 500);
                            collected[i] = false;
                        }
                    }
                }

                if (IsKeyPressed(KEY_ESCAPE)) {
                    currentScreen = MENU;
                }
            } break;

            case VICTORY:
                if (IsKeyPressed(KEY_M)) {
                    currentScreen = MENU;
                }
                break;
        }

        // --- DRAW ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentScreen) {
            case MENU:
                DrawText("== MAIN MENU ==", 260, 100, 40, DARKBLUE);
                DrawText("Press [1] Quiz",        260, 200, 30, DARKGRAY);
                DrawText("Press [2] Dodge Game",  260, 250, 30, DARKGRAY);
                DrawText("Press [3] Collect Game",260, 300, 30, DARKGRAY);
                break;

            case QUIZ:
                DrawText("QUIZ SCREEN!", 280, 200, 40, RED);
                DrawText("Press [SPACE] to WIN", 250, 300, 30, DARKGRAY);
                DrawText("Press [ESC] to return", 250, 350, 30, DARKGRAY);
                break;

            case DODGE:
                DrawText("DODGE GAME!", 280, 50, 40, RED);
                DrawText("Reach the right side to win!", 200, 100, 20, DARKGRAY);
                DrawText("Press [ESC] to return", 250, 140, 20, DARKGRAY);

                DrawRectangleV(player, (Vector2){40, 40}, BLUE);
                break;

            case COLLECT: {
                DrawText("Click the flying red squares to collect them!", 120, 40, 20, DARKGRAY);

                Vector2 mouse = GetMousePosition();
                Rectangle mousehitbox = {mouse.x, mouse.y, 10, 10};

                for (int i = 0; i < 3; i++) {
                    DrawRectangleRec(trash[i], RED);
                }

                DrawRectangleRec(mousehitbox, BLUE); // Mouse hitbox
            } break;

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
