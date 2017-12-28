#include "MouseClickServer.h"
#include "Polygon.h"


MouseClickServer::MouseClickServer(Delegate* delegater)
{
	this->delegater = delegater;
	idle = true;

	auto factory = Polygons();
	pencolor_t pen(3, 0);
	cgeneratorlist_t cglist;

	std::string list[] = { "Line", "Ellipse", "Rect", "Poly", 
		"Select", "Rotate", "Scale", "Move", "Cut", 
		"black", "white", "red", "yellow", "blue", "green", "purple", "cyan" ,"grey" ,
		"@relax", " >: ___" };
	auto listlen = sizeof(list) / sizeof(std::string);

	colorlist.resize(listlen);
	colorlist[9].resize(3, 0);
	colorlist[10].resize(3, 1);
	colorlist[11].resize(3, 0);	colorlist[11][0] = 1;
	colorlist[12].resize(3, 0);	colorlist[12][0] = 1; colorlist[12][1] = 1;
	colorlist[13].resize(3, 0);	colorlist[13][2] = 1;
	colorlist[14].resize(3, 0);	colorlist[14][1] = 1;
	colorlist[15].resize(3, 0);	colorlist[15][0] = 1; colorlist[15][2] = 1;
	colorlist[16].resize(3, 0);	colorlist[16][1] = 1; colorlist[16][2] = 1;
	colorlist[17].resize(3, 0.5);

	for (int i = 0; i < listlen - 1; i++) {
		auto stat = 2 * PAGE_HEIGHT - 10 - 80 * i;
		cglist.clear();
		if (!colorlist[i].empty()) { cglist.push_back(std::pair<std::pair<int, int>, pencolor_t>(std::pair<int, int>(20, stat - 40), colorlist[i])); }
		buttom.push_back(new Polygon(factory.getNewPolygon(pen, cglist,
			{ std::pair<int, int>(10, stat - 60), std::pair<int, int>(145, stat - 60),
			std::pair<int, int>(145, stat), std::pair<int, int>(10, stat) })));
		buttomText.push_back(std::pair<std::string, std::pair<int, int>>(list[i], std::pair<int, int>(20, stat - 40)));
	}

	cglist.clear();

	// Prompt
	buttom.push_back(new Polygon(factory.getNewPolygon(pen, cglist,
		{ std::pair<int, int>(10, 10), std::pair<int, int>(145, 10),
		std::pair<int, int>(145, 70), std::pair<int, int>(10, 70) })));
	buttomText.push_back(std::pair<std::string, std::pair<int, int>>(list[listlen - 1], std::pair<int, int>(20, 30)));
}


void MouseClickServer::getCurrent(bool isDown, int raw_x, int raw_y) {
	if (isDown) { 
		current = std::pair<int, int>(raw_x * 2, (PAGE_HEIGHT - raw_y) * 2);
		if (current.first < 150)	idle = false;
		else	idle = true;
//		std::clog << current.first << ' ' << current.second << std::endl;
	}
	else if(!idle){
		auto now = std::pair<int, int>(raw_x, (PAGE_HEIGHT - raw_y) * 2);
//		std::clog << now.first << ' ' << now.second << std::endl;
		if (abs(now.first - current.first) < 15 || abs(now.second - current.second) < 15) {
			int service_num = 0;
			for each (auto&& service in buttom)
			{
				if (service->getUttermost().isIn(current)) {
					break;
				}
				++service_num;
			}
			switch (service_num)
			{
			case 0: delegater->invoked(reaction::Buttom::Line); break;
			case 1: delegater->invoked(reaction::Buttom::Ellipse); break;
			case 2: delegater->invoked(reaction::Buttom::Rectangle); break;
			case 3: delegater->invoked(reaction::Buttom::Polygon); break;
			case 4: delegater->invoked(reaction::Buttom::SELECT); break;
			case 5: delegater->invoked(reaction::Buttom::ROTATE); break;
			case 6: delegater->invoked(reaction::Buttom::SCALE); break;
			case 7: delegater->invoked(reaction::Buttom::MOVE); break;
			case 8: delegater->invoked(reaction::Buttom::CUT); break;
			case 9: delegater->invoked(reaction::Buttom::BLACK); break;
			case 10: delegater->invoked(reaction::Buttom::WHITE); break;
			case 11: delegater->invoked(reaction::Buttom::RED); break;
			case 12: delegater->invoked(reaction::Buttom::YELLOW); break;
			case 13: delegater->invoked(reaction::Buttom::BLUE); break;
			case 14: delegater->invoked(reaction::Buttom::GREEN); break;
			case 15: delegater->invoked(reaction::Buttom::PURPLE); break;
			case 16: delegater->invoked(reaction::Buttom::CYAN); break;
			case 17: delegater->invoked(reaction::Buttom::GREY); break;
			case 18: delegater->invoked(reaction::Buttom::IDLE); break;
			case 19: delegater->invoked(reaction::Buttom::PROMPT); break;
			default:
				break;
			}
		}
		idle = true;
	}
}


MouseClickServer::~MouseClickServer()
{
}
