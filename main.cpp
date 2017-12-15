#include <iostream>
#include <GL/glut.h>
#include "GLPlayer.h"
#include "GeometricLine.h"
#include "StraightLine.h"
#include "GeometricCircle.h"
#include "CircleRim.h"
#include "GeometricEllipse.h"
#include "EllipseRim.h"
#include "RectangleRim.h"
#include "Polygon.h"
#include "Typedef.h"

using namespace std;

#define DEBUG true

static int PAGE_HEIGHT = 800;
static int PAGE_WIDTH = 1000;

#if DEBUG
  void Display()
{
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
	static Polygon polygon_disp = Polygons().getRelocatedNewPolygon(polygon, pair<int,int>(800, 1200));
	static Polygon polygon_rotate = Polygons().getRotatedNewPolygon(polygon, 0.3);
	static Polygon polygon_scale = Polygons().getScaledNewPolygon(polygon, pair<double, double>(0.5, 0.5));
	Player.DrawOutline(line);
	Player.DrawOutline(line_2);
	Player.DrawOutline(line_3);
	Player.DrawOutline(circle_rim);
	Player.DrawOutline(ellipse_rim);
	Player.DrawOutline(rectangle_rim);
	Player.FillGraphic(rectangle);
//	Player.FillGraphic(polygon);
	Player.DrawOutline(polygon_sketchout);
	Player.FillGraphic(polygon_disp);
	Player.FillGraphic(polygon_rotate);
	Player.FillGraphic(polygon_scale);
	glFlush();
}
#elif TEST_ONE
void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(10);
	
	glBegin(GL_POINTS);
	glVertex2d(1, 1);
	glVertex2d(2, 2);
	glVertex2d(3, 3);
	glVertex2d(4, 4);
	glVertex2d(5, 5);
	glVertex2d(6, 6);
	glVertex2d(7, 7);
	glVertex2d(8, 8);
	glVertex2d(9, 9);
	glEnd();

	glPointSize(1);

	glRectd(2.2, 3.1, 12.2, 13.1);
}
#else
void TEST()
  {
	glPointSize(10);
  	glBegin(GL_POINTS);
	

	glVertex3f(0.25, 0.25, 0.0);
	glVertex3f(0.75, 0.25, 0.0);
	glVertex3f(0.75, 0.75, 0.0);
	glVertex3f(0.25, 0.75, 0.0);
	glEnd();

	glFlush();
  }

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	TEST();
	glFlush();
}
#endif


int main(int argc, char** argv)
{
	glutInit(&argc, argv);                           //初始化GLUT并处理命令行参数  
	glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);      //指定模式：单缓存OR双缓存；RGBA模式OR颜色索引模式  
	glutInitWindowSize(PAGE_WIDTH, PAGE_HEIGHT);                    //指定窗口大小（像素）  
	glutInitWindowPosition(0, 0);                //指定窗口左上角在屏幕上的位置  
	glutCreateWindow("Delineate");                      //使用OpenGL场景创建一个窗口，参数为窗口名称  
	glClearColor(1.0, 1.0, 1.0, 1.0);
//	glShadeModel(GL_FLAT);
	
	glutDisplayFunc(&Display);

	glutMainLoop();
	return 0;
}