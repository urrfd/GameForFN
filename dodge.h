#ifndef DODGE_H
#define DODGE_H

#include "shared.h"

void InitDodge(void);
void UnloadDodge(void);

void UpdateDodge(GameScreen* currentScreen, const char** victoryMsg);
void DrawDodge();

#endif