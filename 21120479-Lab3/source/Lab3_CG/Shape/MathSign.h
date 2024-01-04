#pragma once
#include "Other.h"

class Plus : public Polygon {
public:
    Plus(Point start, Point end, RGBColor fillColor) : Polygon(start, end, fillColor) {
    }

private:
    void addVertices() {
        vertices.clear();

        double x1 = topLeft.getx();
        double y1 = topLeft.gety();
        double x2 = bottomRight.getx();
        double y2 = bottomRight.gety();

        double width = abs(x1 - x2);
        double height = abs(y1 - y2);

        Point p1(x1 + width / 3, y1);
        Point p2(x1 + width / 3, y1 + height / 3);
        Point p3(x1, y1 + height / 3);
        Point p4(x1, y1 + 2 * height / 3);
        Point p5(x1 + width / 3, y1 + 2 * height / 3);
        Point p6(x1 + width / 3, y2);
        Point p7(x1 + 2 * width / 3, y2);
        Point p8(x1 + 2 * width / 3, y1 + 2 * height / 3);
        Point p9(x2, y1 + 2 * height / 3);
        Point p10(x2, y1 + height / 3);
        Point p11(x1 + 2 * width / 3, y1 + height / 3);
        Point p12(x1 + 2 * width / 3, y1);

        vertices = { p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 };
        
       
    }
};


class Minus : public Polygon {
public:
    Minus(Point start, Point end, RGBColor fillColor) : Polygon(start, end, fillColor) {
        
    }

private:
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


class Multiply : public Polygon {
public:
    Multiply(Point start, Point end, RGBColor fillColor) : Polygon(start, end, fillColor) {
    }
private:
    void addVertices() {
        vertices.clear();

        double x1 = topLeft.getx();
        double y1 = topLeft.gety();
        double x2 = bottomRight.getx();
        double y2 = bottomRight.gety();

        if (x1 == x2 || y1 == y2)
            return;

        double width = abs(x1 - x2);
        double height = abs(y1 - y2);

        Point m1(x1 + width / 5, y1);
        Point m2(x1, y1 + height / 5);
        Point m3(x1, y1 + 4 * height / 5);
        Point m4(x1 + width / 5, y2);
        Point m5(x1 + 4 * width / 5, y2);
        Point m6(x2, y1 + 4 * height / 5);
        Point m7(x2, y1 + height / 5);
        Point m8(x1 + 4 * width / 5, y1);

        Point i23 = Line::findIntersection(Line(m2, m5), Line(m3, m8));
        if (i23 == Point(-1, -1))
            return;

        Point i45 = Line::findIntersection(Line(m4, m7), Line(m5, m2));
        if (i45 == Point(-1, -1))
            return;

        Point i67 = Line::findIntersection(Line(m6, m1), Line(m7, m4));
        if (i67 == Point(-1, -1))
            return;

        Point i81 = Line::findIntersection(Line(m8, m3), Line(m1, m6));
        if (i81 == Point(-1, -1))
            return;

        vertices = { m1, m2, i23, m3, m4, i45, m5, m6, i67, m7, m8, i81 };
    }
};



class Divide : public Polygon {
public:
    Divide(Point start, Point end, RGBColor fillColor) : Polygon(start, end, fillColor) {

    }

protected:
    void addVertices() {
        vertices.clear();

        double x1 = topLeft.getx();
        double y1 = topLeft.gety();
        double x2 = bottomRight.getx();
        double y2 = bottomRight.gety();

        double width = abs(x1 - x2);
        double height = abs(y1 - y2);

        Point p1(x1 + 4 * width / 5, y1);
        Point p2(x1, y2);
        Point p3(x1 + width / 5, y2);
        Point p4(x2, y1);

        vertices = { p1, p2, p3, p4 };

    }
};