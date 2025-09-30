#include "dodge.h"
#include "raymath.h"
#include <stdio.h>

// Static variables for the animated background
static Texture2D background_sheet;
static int frame_width = 32;
static int frame_height = 32;
static int total_frames;
static int current_frame = 0;
static float animation_timer = 0.0f;
static float frame_time = 0.1f; // frames per second

// Static variable for the player
static Vector2 player = { 400, 300 };

// Function to initialize the dodge game assets
void InitDodge() {
    background_sheet = LoadTexture("assets/backgrounds/deep-water.png");
    if (background_sheet.id == 0) {
        printf("Failed to load animated background!\n");
    }
    total_frames = background_sheet.width / frame_width;

    // Reset player position and animation state
    player = (Vector2){400, 300};
    current_frame = 0;
    animation_timer = 0.0f;
}

// Function to unload the dodge screen assets
void UnloadDodge() {
    UnloadTexture(background_sheet);
}


void UpdateDodge(GameScreen* currentScreen, const char** victoryMsg) {
    if (IsKeyDown(KEY_RIGHT)) player.x += 4;
    if (IsKeyDown(KEY_LEFT))  player.x -= 4;
    if (IsKeyDown(KEY_UP))    player.y -= 4;
    if (IsKeyDown(KEY_DOWN))  player.y += 4;

    player.x = Clamp(player.x, 0.0f, 800.0f - 40.0f);
    player.y = Clamp(player.y, 0.0f, 600.0f - 40.0f);
    
    // Animate the background by advancing the frame
    animation_timer += GetFrameTime();
    if (animation_timer >= frame_time) {
        animation_timer = 0.0f;
        current_frame++;
        if (current_frame >= total_frames) {
            current_frame = 0; // Loop the animation
        }
    }

    // Win/Lose conditions
    if (player.x >= 760) {
        *currentScreen = VICTORY;
        *victoryMsg = "You won the DODGE game!";
    }

    // Return to menu
    if (IsKeyPressed(KEY_ESCAPE)) {
        *currentScreen = MENU;
    }
}

// Draw the dodge screen
void DrawDodge() {
    // 1. Draw the animated, tiled background
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();
    
    // Define the source rectangle for the current animation frame
    Rectangle source_rec = {
        (float)current_frame * frame_width, // X position on the sprite sheet
        0.0f,
        (float)frame_width,
        (float)frame_height
    };

    // Use a nested loop to tile the background
    for (int y = 0; y < screen_height; y += frame_height) {
        for (int x = 0; x < screen_width; x += frame_width) {
            Vector2 position = { (float)x, (float)y };
            
            // Draw the current frame as a tile
            DrawTextureRec(background_sheet, source_rec, position, WHITE);
        }
    }
    
    // 2. Draw the player and other game elements on top
    DrawRectangleV(player, (Vector2){40, 40}, BLUE);
    
  
}