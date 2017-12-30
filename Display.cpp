#include <GL\glut.h>
#include <utility>
#include "GLPlayer.h"
#include "GeometricLine.h"
#include "StraightLine.h"
#include "GeometricCircle.h"
#include "CircleRim.h"
#include "GeometricEllipse.h"
#include "EllipseRim.h"
#include "Reaction.h"
#include "RectangleRim.h"
#include "RectangleWindowRim.h"
#include "Polygon.h"
#include "Typedef.h"
#include "Reaction.h"
#include "Liang_Barsky_Algorithm.h"
#include "Weiler_Atherton_Algorithm.h"

using namespace std;

Window GLWindow(pair<int, int>(PAGE_WIDTH, PAGE_HEIGHT));
GLPlayer Player(GLWindow);

#define DEBUG true
#undef DEBUG

void Display()
{
#if DEBUG
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	static Window window(pair<int, int>(PAGE_WIDTH, PAGE_HEIGHT));
	static GLPlayer Player(window);
	static GeometricLine geometric_line(pair<int, int>(100, 800), pair<int, int>(1900, 400));
	static GeometricLine geometric_line_2(pair<int, int>(200, 300), pair<int, int>(1200, 1300));
	static GeometricLine geometric_line_3(pair<int, int>(100, 1000), pair<int, int>(1000, 100));
	static GeometricCircle geometric_circle(pair<int, int>(1000, 800), 400);
	static GeometricEllipse geometric_ellipse(pair<int, int>(800, 1000), 500, 300);
	static StraightLine line(geometric_line);
	static StraightLine line_2(geometric_line_2);
	static StraightLine line_3(geometric_line_3);
	static CircleRim circle_rim(geometric_circle);
	static EllipseRim ellipse_rim(geometric_ellipse);
	static RectangleRim rectangle_rim(pair<int, int>(1100, 400), pair<int, int>(1800, 1400));
	static RectangleRim colorful_rectangle_rim(pair<int, int>(100, 400), pair<int, int>(300, 800));
	static RectangleWindowRim rectangle_window_rim(pair<int, int>(650, 300), pair<int, int>(750, 400), new Liang_Barsky_Algorithm(), new Weiler_Atherton_Algorithm());
	static pencolor_t pencolor(3);
	pencolor[0] = 0.1;
	pencolor[1] = 0.6;
	pencolor[2] = 0.8;
	static cgeneratorlist_t cgenerators;
	cgenerators.push_back(pair<pair<int, int>, pencolor_t>(pair<int, int>(200, 500), pencolor));
	static Polygon rectangle(colorful_rectangle_rim, pencolor, cgenerators);

	const pair<int, int> point_1(500, 700), point_2(800, 800), point_3(800, 100), point_4(650, 200);

	/*
	vector<pair<pair<int, int>, pair<int, int>>> perimeter;
	perimeter.push_back(pair<pair<int, int>, pair<int, int>>(point_1, point_2));
	perimeter.push_back(pair<pair<int, int>, pair<int, int>>(point_2, point_3));
	perimeter.push_back(pair<pair<int, int>, pair<int, int>>(point_3, point_1));
	static PolygonRim polygon_rim(perimeter);
	*/
	cgenerators.clear();
	cgenerators.push_back(pair<pair<int, int>, pencolor_t>(pair<int, int>(600, 700), pencolor));
	// static Polygon polygon(polygon_rim, pencolor, cgenerators);
	static Polygon polygon = Polygons().getNewPolygon(pencolor, cgenerators, { point_1, point_2, point_3, point_4 });
	static RectangleRim polygon_sketchout = polygon.getUttermost();
	static Polygon polygon_disp = Polygons().getRelocatedNewPolygon(polygon, pair<int, int>(800, 1200));
	static Polygon polygon_rotate = Polygons().getRotatedNewPolygon(polygon, 0.3);
	static Polygon polygon_scale = Polygons().getScaledNewPolygon(polygon, pair<double, double>(0.5, 0.5));
	static Polygon polygon_manip = Polygons().getManipulatedNewPolygon(polygon, pair<int, int>(500, 500), pair<double, double>(1.2, 0.8), 0.4);
//	static std::vector<PolygonRim> polygon_rim_aftercut = rectangle_window_rim.PolygonCut(rectangle_rim);
	static auto polygon_aftercut = Polygons().getCutNewPolygon(polygon, rectangle_window_rim);
	Player.DrawOutline(line);
	Player.DrawOutline(line_2);
	Player.DrawOutline(line_3);
	Player.DrawOutline(circle_rim);
	Player.DrawOutline(ellipse_rim);
//	Player.DrawOutline(rectangle_rim);
//	Player.DrawOutline(rectangle_window_rim);
	Player.FillGraphic(rectangle);
//	Player.FillGraphic(polygon);
//	for (int i = 0; i < polygon_rim_aftercut.size(); ++i)
//		Player.DrawOutline(polygon_rim_aftercut[i]);
//	Player.FillGraphic(polygon_disp);
//	Player.FillGraphic(polygon_rotate);
//	Player.FillGraphic(polygon_scale);
//	Player.FillGraphic(polygon_manip);
	for (int i = 0; i < polygon_aftercut.size(); ++i)
		Player.FillGraphic(polygon_aftercut[i]);
	glutSwapBuffers();
#else
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	for (auto&& text : clickserver.TextifyButtom())
		Player.TextWords(text.first, text.second);

	for (auto&& buttom : clickserver.VisualizeButtom())
		Player.FillGraphic(*buttom);
	for (auto&& outline : server.serializeOutline())
		Player.DrawOutline(*outline);
	for (auto&& graphic : server.serializeGraphic())
		Player.FillGraphic(*graphic);
	glutSwapBuffers();
#endif
}
