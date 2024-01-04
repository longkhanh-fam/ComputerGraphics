#pragma once
#include "Line.h"
class Circle : public Shape {
protected:
    Point center;
    int radius;

public:
    Circle(Point start, Point end, RGBColor fillColor) : Shape(start, end, fillColor) {
        locatedBoundingBox();
    }

protected:
    void locatedBoundingBox() {
        center = start;

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
    }



protected:
    void drawing() {
        int x1 = topLeft.getx();
        int y1 = topLeft.gety();
        int x2 = bottomRight.getx();
        int y2 = bottomRight.gety();

        radius = min(abs(x1 - x2), abs(y1 - y2));


        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 360; ++i) {
            float angle = i * M_PI / 180; // Convert degrees to radians
            glVertex2f(center.getx() + radius * cos(angle), center.gety() + radius * sin(angle));
        }
        glEnd();
    }
    bool isPointInside(int x, int y) {
        int dx = x - center.getx();
        int dy = y - center.gety();
        int distanceSquared = dx * dx + dy * dy;  // Calculate squared distance for efficiency
        return distanceSquared <= radius * radius;
    }
};


class Ellipse : public Shape {
private:
    Point center;
    int majorAxis, minorAxis;

public:
    Ellipse(Point start, Point end, RGBColor fillColor) : Shape(start, end, fillColor) {
        locatedBoundingBox();
    }

protected:
    void locatedBoundingBox() {
        center = start;

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
    }



protected:
    void drawing() {
        double x1 = topLeft.getx();
        double y1 = topLeft.gety();
        double x2 = bottomRight.getx();
        double y2 = bottomRight.gety();

        majorAxis = abs(x1 - x2);
        minorAxis = abs(y1 - y2);


        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 360; ++i) {
            float angle = i * M_PI / 180; // Convert degrees to radians
            glVertex2f(center.getx() + majorAxis * cos(angle), center.gety() + minorAxis * sin(angle));
        }
        glEnd();
    }
    bool isPointInside(int x, int y) {
        int dx = x - center.getx();
        int dy = y - center.gety();

        // Calculate the normalized distance from the center to the point
        double normalizedDistance = (dx * dx) / (majorAxis * majorAxis) + (dy * dy) / (minorAxis * minorAxis);

        return normalizedDistance <= 1.0;
    }

};