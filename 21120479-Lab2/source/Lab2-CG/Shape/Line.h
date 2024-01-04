#pragma once
#include "Shape.h"
class Line : public Shape
{
private:
	bool isEdge;
	Point startLine, endLine;
public:
	Line(Point start, Point end) : Shape(start, end) {
		startLine = start;
		endLine = end;
	}
	Line(Point start, Point end, RGBColor fillColor) : Shape(start, end, fillColor)
	{
		startLine = start;
		endLine = end;
	}
public:
	Point getStartLine()
	{
		return startLine;
	}
	Point getEndLine()
	{
		return endLine;
	}
public:
	void locateBoundingBox() {
		Shape::locateBoundingBox();
		locatePoints();
	}

	void locatePoints() {
		startLine = start;
		endLine = end;
	}
	void filling() {}
	void drawing()
	{
		glBegin(GL_LINES);
		int x1 = startLine.getx();
		int y1 = startLine.gety();
		int x2 = endLine.getx();
		int y2 = endLine.gety();
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glEnd();

		
	}
public:


	static Point findIntersection(Line line1, Line line2) {
		int x1 = line1.startLine.getx();
		int y1 = line1.startLine.gety();
		int x2 = line1.endLine.getx();
		int y2 = line1.endLine.gety();

		int x3 = line2.startLine.getx();
		int y3 = line2.startLine.gety();
		int x4 = line2.endLine.getx();
		int y4 = line2.endLine.gety();

		float m1 = (x1 == x2) ? 0 : (float)(y2 - y1) / (x2 - x1);
		float b1 = y1 - m1 * x1;

		float m2 = (x3 == x4) ? 0 : (float)(y4 - y3) / (x4 - x3);
		float b2 = y3 - m2 * x3;

		if (m1 == m2) {
			return Point(-1, -1);  // Parallel lines
		}

		float x = (b2 - b1) / (m1 - m2);
		float y = m1 * x + b1;

		return Point(round(x), round(y));
	}


};