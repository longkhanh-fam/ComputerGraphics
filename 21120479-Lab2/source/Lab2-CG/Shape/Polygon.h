#pragma once
#include "Shape.h"

class Polygon : public Shape {
protected:
	vector<Point> vertices;
public:
	Polygon(Point start, Point end, RGBColor fillColor) :Shape(start, end, fillColor) {
	}
public:
	virtual void findFillPoint() {
		int x = 0, y = 0;
		if (vertices.size() > 0) {
			for (int i = 0; i < vertices.size(); i++) {
				x += vertices[i].getx();
				y += vertices[i].gety();
			}
			x /= vertices.size();
			y /= vertices.size();
		}
		else {
			int x1 = topLeft.getx();
			int y1 = topLeft.gety();
			int x2 = bottomRight.getx();
			int y2 = bottomRight.gety();
			x = (x1 + x2) / 2;
			y = (y1 + y2) / 2;
		}

		fillPoint = Point(clip(x, 0, WINDOW_WIDTH - 1), clip(y, 0, WINDOW_HEIGHT - 1));
	}
	virtual void addVertices()
	{

	}
	void locateBoundingBox()
	{
		int x1 = start.getx();
		int x2 = end.getx();
		int y1 = start.gety();
		int y2 = end.gety();

		if (x1 > x2)
		{
			swap(x1, x2);
		}
		if (y1 > y2)
			swap(y1, y2);
		topLeft = Point(x1, y1);
		bottomRight = Point(x2, y2);
		addVertices();
	}
	//void filling() {
	//	if (isAlign(start, end) || isAlign(topLeft, bottomRight))
	//		return;
	//	findFillPoint();
	//	//boundaryFill1(fillPoint.getx(), fillPoint.gety(), fillingColor, Colors::RED);
	//}

	void drawing()
	{
		int n = vertices.size();
		for (int i = 0; i < n; i++)
		{
			Point p1 = vertices[i];
			Point p2 = vertices[(i + 1) % n];
			Line(p1, p2, Colors::BLUE).drawing();
		}
		fillingColor = Colors::BLUE;
		findFillPoint();
		//filling();

	}


public:
	virtual bool isPointInside(int x, int y) {
		int n = vertices.size();
		int i, j = n - 1;
		bool oddNodes = false;

		for (i = 0; i < n; i++) {
			if ((vertices[i].gety() < y && vertices[j].gety() >= y || vertices[j].gety() < y && vertices[i].gety() >= y) &&
				(vertices[i].getx() + (y - vertices[i].gety()) / (vertices[j].gety() - vertices[i].gety()) * (vertices[j].getx() - vertices[i].getx()) < x)) {
				oddNodes = !oddNodes;
			}
			j = i;
		}

		return oddNodes;
	}
};


//TRIANGLE------------------------------------------


class Triangle : public Polygon {
public:
	Triangle(Point start, Point end, RGBColor fillColor) : Polygon(start, end, fillColor)
	{}

public:
	virtual void locateBoundingBox() {
		Polygon::locateBoundingBox();
	}

	void addVertices()
	{
		Polygon::addVertices();
	}

};

class EquilTriangle : public Triangle {
public:
	EquilTriangle(Point start, Point end, RGBColor fillColor) : Triangle(start, end, fillColor)
	{}

public:
	void locateBoundingBox() {
		Triangle::locateBoundingBox();

	}
	virtual void addVertices() {
		vertices.clear();

		int x1 = topLeft.getx();
		int y1 = topLeft.gety();
		int x2 = bottomRight.getx();
		int y2 = bottomRight.gety();

		int side = min(abs(x1 - x2), abs(y1 - y2));

		x2 = x1 + side;
		int x3 = (x1 + x2) / 2;
		int y3 = round(1.0 * y2 - 1.0 * side * sqrt(3) / 2);

		vertices.push_back(Point(x2, y2));
		vertices.push_back(Point(x3, y3));
		vertices.push_back(Point(x1, y2));
		Triangle::addVertices();
	}

};

class IsoRightTriangle : public Triangle {
public:
	IsoRightTriangle(Point start, Point end, RGBColor fillColor) : Triangle(start, end, fillColor)
	{}

public:
	void locateBoundingBox() {
		Triangle::locateBoundingBox();

	}
	void addVertices() {
		vertices.clear();

		int x1 = topLeft.getx();
		int y1 = topLeft.gety();
		int x2 = bottomRight.getx();
		int y2 = bottomRight.gety();

		int side = min(abs(x1 - x2), abs(y1 - y2));
		x2 = x1 + side;
		y2 = y1 + side;

		vertices.push_back(Point(x2, y2));
		vertices.push_back(Point(x1, y1));
		vertices.push_back(Point(x1, y2));

	}
};


//QUADRILATERAL--------------------------------------


class Rectangle : public Polygon {
public:
	Rectangle(Point start, Point end, RGBColor fillColor) : Polygon(start, end, fillColor)
	{}

public:
	void locateBoundingBox() {
		Polygon::locateBoundingBox();
	}
	void addVertices() {
        vertices.clear();

        double x1 = topLeft.getx();
        double y1 = topLeft.gety();
        double x2 = bottomRight.getx();
        double y2 = bottomRight.gety();

        double width = abs(x1 - x2);
        double height = abs(y1 - y2);

        Point p1(x1, y1 + height / 3);
        Point p2(x1, y1 + 2 * height / 3);
        Point p3(x2, y1 + 2 * height / 3);
        Point p4(x2, y1 + height / 3);

        vertices = { p1, p2, p3, p4 };

    }
};

class Square : public Polygon {
public:
	Square(Point start, Point end, RGBColor fillColor) : Polygon(start, end, fillColor)
	{}

public:
	void locateBoundingBox() {
		Polygon::locateBoundingBox();
	}

	void addVertices() {
		vertices.clear();

		int x1 = topLeft.getx();
		int y1 = topLeft.gety();
		int x2 = bottomRight.getx();
		int y2 = bottomRight.gety();

		int side = min(abs(x1 - x2), abs(y1 - y2));
		x2 = x1 + side;
		y2 = y1 + side;

		vertices.push_back(Point(x2, y2));
		vertices.push_back(Point(x2, y1));
		vertices.push_back(Point(x1, y1));
		vertices.push_back(Point(x1, y2));
	}


};


//POLYGON--------------------------------------


class Pentagon : public Polygon {
public:
	Pentagon(Point start, Point end, RGBColor fillColor) : Polygon(start, end, fillColor)
	{}

public:
	void locateBoundingBox() {
		topLeft = start;
		bottomRight = end;
		addVertices();
	}
	void addVertices() {
		vertices.clear();
		int x1 = topLeft.getx();
		int y1 = topLeft.gety();
		int x2 = bottomRight.getx();
		int y2 = bottomRight.gety();

		int side = min(abs(x1 - x2), abs(y1 - y2));
		x2 = x1 + side;
		y2 = y1 + side;

		Point p1(x1 + side / 2, y1);
		Point p2(x1, round(tan(36 * M_PI / 180) * side / 2 + y1));
		Point p3(round(tan(18.0 * M_PI / 180) * (y2 - p2.gety()) + x1), y2);
		Point p4(round(1.0 * x2 - tan(18.0 * M_PI / 180) * (y2 - p2.gety())), y2);
		Point p5(x2, p2.gety());

		vertices = { p1, p2, p3, p4, p5 };

	}


};

class Hexagon : public Polygon {
public:
	Hexagon(Point start, Point end, RGBColor fillColor) : Polygon(start, end, fillColor)
	{
	}

public:
	void locateBoundingBox() {
		topLeft = start;
		bottomRight = end;
		addVertices();
	}
	void addVertices() {
		vertices.clear();
		int x1 = topLeft.getx();
		int y1 = topLeft.gety();
		int x2 = bottomRight.getx();
		int y2 = bottomRight.gety();

		int side = min(abs(x1 - x2), abs(y1 - y2));
		x2 = x1 + side;
		y2 = y1 + side;

		Point p1(x1 + side / 2, y1);
		Point p2(x1, round(tan(30 * M_PI / 180) * side / 2 + y1));
		Point p3(x1, round(1.0 * y2 - tan(30 * M_PI / 180) * side / 2));
		Point p4(x1 + side / 2, y2);
		Point p5(x2, p3.gety());
		Point p6(x2, p2.gety());

		vertices = { p1, p2, p3, p4, p5, p6 };
	}


};