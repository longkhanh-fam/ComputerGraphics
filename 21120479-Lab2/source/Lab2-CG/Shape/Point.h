#pragma once


class Point {
private:
    double mX, mY;

public:
    Point(double x = 0, double y = 0) : mX(x), mY(y) {}

public:
    double  getx() const {
        return mX;
    }

    double  gety() const {
        return mY;
    }

    void setX(double x) {
        mX = x;
    }

    void setY(double y) {
        mY = y;
    }

public:
    Point operator+(const Point& p) {
        return Point(mX + p.mX, mY + p.mY);
    }

    Point operator/(const int& n) {
        return Point(mX / n, mY / n);
    }

    bool operator==(const Point& p) {
        return mX == p.mX && mY == p.mY;
    }
};