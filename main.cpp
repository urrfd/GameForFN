#include "shared.h"
#include "quiz.h"
#include "collect.h"
#include "dodge.h"
#include "raylib.h"


int main(void) {
    InitWindow(800, 600, "Quiz + Minigames");
    InitAudioDevice(); 
    SetTargetFPS(60);

    GameScreen currentScreen = MENU;
    const char* victoryMsg = "YOU WIN!";

    Music musicShallows = LoadMusicStream("assets/sounds/music/shallows.mp3");
    Music musicBeach = LoadMusicStream("assets/sounds/music/beach.mp3");
    PlayMusicStream(musicShallows);
    Music* currentMusic = &musicShallows;
    bool isBeachPlaying = false;

    

    while (!WindowShouldClose()) {
        UpdateMusicStream(*currentMusic);

        // Switch music only when needed
        if (currentScreen == VICTORY && !isBeachPlaying) {
            currentMusic = &musicBeach;
            PlayMusicStream(musicBeach);
            isBeachPlaying = true;
        } else if (currentScreen != VICTORY && isBeachPlaying) {
            currentMusic = &musicShallows;
            PlayMusicStream(musicShallows);
            isBeachPlaying = false;
        }

        switch (currentScreen) {
            case MENU:
                if (IsKeyPressed(KEY_ONE)) currentScreen = QUIZ;
                if (IsKeyPressed(KEY_TWO)) {
                    currentScreen = DODGE;
                    InitDodge(); 
                }
                if (IsKeyPressed(KEY_THREE)) currentScreen = COLLECT;
                break;
            case QUIZ:    UpdateQuiz(&currentScreen, &victoryMsg); break;
            case DODGE:   UpdateDodge(&currentScreen, &victoryMsg); break;
            case COLLECT: UpdateCollect(&currentScreen, &victoryMsg); break;
            case VICTORY:
                if (IsKeyPressed(KEY_M)) currentScreen = MENU;
                break;
        }

       
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

    // Unload assets
    UnloadMusicStream(musicShallows);
    UnloadMusicStream(musicBeach);
    CloseAudioDevice();
    UnloadDodge();
    CloseWindow();
    return 0;
}