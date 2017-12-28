#pragma once
#include "Window.h"
#include "CGeneratorBarrier.h"
#include <vector>

class Graphic;
class Outline;

class GLPlayer
{
public:
	GLPlayer(Window InitWindow);
	void TextWords(std::string name, std::pair<int, int> position);
	void DrawOutline(Outline &outline);
	void FillGraphic(Graphic &graphic);
	Window& getWindow();
	void setWindow(Window& Now);
	~GLPlayer();

private:
	Window WindowNow;

	static std::vector<std::vector<std::pair<int, int>>> CGenerationKernel(std::pair<int, int>& CGenerator, int baseY,
		std::vector<std::vector<CGeneratorBarrier*>>& CGeneratorList, Window& window);

	static std::vector<std::pair<int, int>> CGenerationRecursionStartPoint(std::vector<CGeneratorBarrier*>& StartLine, 
		std::pair<int, int>& ClosedRange, int CommonY);
};

