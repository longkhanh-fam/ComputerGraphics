#ifndef __SHAPE_H
#define __SHAPE_H
#include "../Filling/CanvasState.h"
#include "../Utils/Utils.h"
using namespace std;
class Shape {
public:
	static int nextId;
protected:
	vector<Pixel> filledPixels;
	RGBColor fillingColor;
	Point start, end;
	Point topLeft, bottomRight;
	int id;
	Point fillPoint;
	bool selected ;
public:
	Shape(Point start, Point end)
	{
		this->start = start;
		this->end = end;
		selected = false;
	}
	Shape(Point start, Point end, RGBColor fillColor) : start(start), end(end), fillingColor(fillColor)
	{
		id = nextId++;
		selected = false;
		locateBoundingBox();
	}
public:
	virtual void setEnd(int x, int y)
	{

		x = clip(x, 0, WINDOW_WIDTH);
		y = clip(y, 0, WINDOW_HEIGHT);

		this->end = Point(x, y);
		locateBoundingBox();
	}
public:
	virtual void locateBoundingBox()
	{
		topLeft = start;
		bottomRight = end;
	}
	virtual void findFillPoint() {}

	void setFillPoint(int x, int y) {
		fillPoint.setX(x);
		fillPoint.setY(y);
	}

	void setFillColor(const RGBColor& color) {
		fillingColor = color;
	}

	RGBColor getFillColor() const {
		return fillingColor;
	}
	void filling(float saturation = 1.0) {
		
		for (Pixel pixel : filledPixels) {

			glColor3f(pixel.getr()*saturation, pixel.getg() * saturation, pixel.getb() * saturation);
			glBegin(GL_POINTS);
			glVertex2i(pixel.getX(), pixel.getY());
			glEnd();
		}
	}
	virtual void drawing() {}
	void draw()
	{
		drawing();
		
	}

public:

	int getId() const {
		return id;
	}
	bool isSelected() {
		return selected == true;
	}
	void setSelected(bool isSeletect) {
		selected = isSeletect;
	}

public:
	void addFilledPixel(const Pixel& pixel) {
		filledPixels.push_back(pixel);
	}

	const std::vector<Pixel>& getFilledPixels() const {
		return filledPixels;
	}
public:
	virtual bool isPointInside(int x, int y) {
		return false;
	};
};
#endif 