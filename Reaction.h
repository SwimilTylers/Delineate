#pragma once
#include "ReactionServer.h"
#include "GLPlayer.h"

extern ReactionServer server;
extern GLPlayer Player;
extern int PAGE_HEIGHT;
extern int PAGE_WIDTH;

void Display();
void PromptInteraction(int key, int x, int y);