#pragma once
#ifndef __RGBCOLOR_H
#define __RGBCOLOR_H
#include <GL/glut.h>


#include <unordered_map>

#include <iostream>
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800
using namespace std;
class RGBColor {
private:
    float mR, mG, mB;


public:
    RGBColor() {
        mR = mG = mB = 0.0;

    }
    RGBColor(float r, float g, float b) {
        mR = r;
        mG = g;
        mB = b;

    }


public:
    void setColor(float r, float g, float b) {
        mR = r;
        mG = g;
        mB = b;
    }

    float r() {
        return mR;
    }

    float g() {
        return mG;
    }

    float b() {
        return mB;
    }
    bool operator==(RGBColor other) {

        return mR == other.mR && mG == other.mG && mB == other.mB;
    }

    bool operator!=(RGBColor other) {
        return !(*this == other);
    }
};

class Colors {
public:
    static RGBColor BLACK, WHITE, RED, GREEN, BLUE, YELLOW, MAGENTA;

    static RGBColor SELECTED;
    static RGBColor BOUNDARY;

public:
    static unordered_map<int, RGBColor> colorMap;
};

RGBColor Colors::BLACK = RGBColor(0.0, 0.0, 0.0);
RGBColor Colors::WHITE = RGBColor(1.0, 1.0, 1.0);
RGBColor Colors::RED = RGBColor(1.0, 0.0, 0.0);
RGBColor Colors::GREEN = RGBColor(0.0, 1.0, 0.0);
RGBColor Colors::BLUE = RGBColor(0.0, 0.0, 1.0);
RGBColor Colors::YELLOW = RGBColor(1.0, 1.0, 0.0);
RGBColor Colors::MAGENTA = RGBColor(1.0, 0.0, 1.0);


enum ColorType {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    BLACK,
    WHITE,
    MAGENTA
};
#endif // !__RGBCOLOR_H