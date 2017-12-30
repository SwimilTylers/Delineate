#pragma once
#include "ReactionServer.h"
#include "ButtomServer.h"
#include "Delegate.h"
#include "GLPlayer.h"

extern ReactionServer server;
extern ButtomServer clickserver;
extern Delegate delegater;
extern GLPlayer Player;
extern int PAGE_HEIGHT;
extern int PAGE_WIDTH;

void Display();
void MouseClick(int button, int state, int x, int y);
void PromptInteraction(int key, int x, int y);

