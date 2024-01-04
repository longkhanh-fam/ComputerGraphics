#pragma once

#include <vector>
#define M_PI 3.14159265358979323846
#include <cmath>
#include "RGBColor.h"
class Pixel {
private:
    double x, y;
    RGBColor color;
public:
    Pixel()
    {
        x = 0;
        y = 0;
    }
    Pixel(double x , double y, RGBColor color ) : x(x), y(y), color(color) {}
public:
    void setX(double x)
    {
        this->x = x;
    }
    void setY(double y)
    {
        this->y = y;
    }
    void setColor(RGBColor color)
    {
        this->color = color;
    }
    RGBColor getColor()
    {
        return color;
    }

    double getX() {
        return x;
    }
    double getY()
    {
        return y;
    }
    float getr() {
        return color.r();
    }

    float getg() {
        return color.g();
    }

    float getb() {
        return color.b();
    }
};

class CanvasState {
private:
    std::vector<Pixel> filledPixels;

public:
    void addFilledPixel(const Pixel& pixel) {
        filledPixels.push_back(pixel);
    }

    const std::vector<Pixel>& getFilledPixels() const {
        return filledPixels;
    }

    void reFillPixel()
    {
        for (Pixel pixel : filledPixels) {

            glColor3f(pixel.getr(), pixel.getg(), pixel.getb());
            glBegin(GL_POINTS);
            glVertex2i(pixel.getX(), pixel.getY());
            glEnd();
        }
    }
};