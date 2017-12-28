#include <GL/glut.h>
#include <iostream>
#include "Reaction.h"

Delegate delegater;
MouseClickServer clickserver(&delegater);

void MouseClick(int button, int state, int x, int y)
{
	switch(button)
	{
	case GLUT_LEFT_BUTTON: 
		if (state == GLUT_DOWN) {
			clickserver.getCurrent(true, x, y);
			delegater.invoked(true, x, y);
		}
		else if (state == GLUT_UP) {
			clickserver.getCurrent(false, x, y);
			delegater.invoked(false, x, y);
		}
		break;
	case GLUT_RIGHT_BUTTON: break;
	case GLUT_MIDDLE_BUTTON: break;
	default: break;
	}

	
	if (delegater.ifReadyPrompt()) {
		auto prompt = delegater.sendPrompt();
		std::clog << prompt << std::endl;
		server(prompt);
		if (server.isReadyToExport())	Display();
	}
	else if (delegater.ifAwakeKeyborad())
		PromptInteraction(GLUT_KEY_INSERT, 0, 0);
}
