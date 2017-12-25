#pragma once
#include "ReactionServer.h"

extern ReactionServer server;
extern int PAGE_HEIGHT;
extern int PAGE_WIDTH;

void Display();
void PromptInteraction(unsigned char key, int x, int y);