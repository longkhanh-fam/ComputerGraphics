#pragma once
#include "./Polygon.h"
class Arrow : public Polygon {
public:
    Arrow(Point start, Point end, RGBColor fillColor) : Polygon(start, end, fillColor)
    {}

public:
    void locateBoundingBox() {
        Polygon::locateBoundingBox();
        addVertices();
    }
    void addVertices() {
        vertices.clear();
        int x1 = topLeft.getx();
        int y1 = topLeft.gety();
        int x2 = bottomRight.getx();
        int y2 = bottomRight.gety();

        int width = abs(x1 - x2);
        int height = abs(y1 - y2);

        Point p1(x2, y1 + height / 2);
        Point p2(x1 + 2 * width / 3, y1);
        Point p3(p2.getx(), y1 + height / 4);
        Point p4(x1, p3.gety());
        Point p5(x1, y1 + 3 * height / 4);
        Point p6(p2.getx(), p5.gety());
        Point p7(p2.getx(), y2);


        vertices = { p1, p2, p3, p4, p5, p6, p7 };
    }


};

class Star : public Polygon {
public:
    Star(Point start, Point end, RGBColor fillColor) : Polygon(start, end, fillColor)
    {}

public:
    void locateBoundingBox() {
        Polygon::locateBoundingBox();
        addVertices();
    }
    void addVertices() {
        vertices.clear();
        int x1 = topLeft.getx();
        int y1 = topLeft.gety();
        int x2 = bottomRight.getx();
        int y2 = bottomRight.gety();

        int width = abs(x1 - x2);
        int height = abs(y1 - y2);

        Point m1(x1 + width / 2, y1);
        Point m2(x1, y1 + height * 2 / 5);
        Point m3(x1 + width * 1 / 5, y2);
        Point m4(x1 + width * 4 / 5, y2);
        Point m5(x2, y1 + height * 2 / 5);

        Point i12 = Line::findIntersection(Line(m1, m3), Line(m2, m5));
        Point i23 = Line::findIntersection(Line(m2, m4), Line(m1, m3));
        Point i34 = Line::findIntersection(Line(m3, m5), Line(m2, m4));
        Point i45 = Line::findIntersection(Line(m4, m1), Line(m3, m5));
        Point i51 = Line::findIntersection(Line(m5, m2), Line(m4, m1));

        if (i12.getx() == -1 || i12.gety() == -1) {
            vertices = { m1 };
            return;
        }

        vertices = { m1, i12, m2, i23, m3, i34, m4, i45, m5, i51 };


    }
};