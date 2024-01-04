#pragma once
#include "../Shape/Point.h"
#include <functional>
#include <chrono>

#define DRAWING 300
#define FILLING 301

long long measureTime(std::function<void()> func) {
    auto start = std::chrono::high_resolution_clock::now();

    func(); // Call the bound function

    auto stop = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
}

int clip(int value, int min, int max) {
    if (value < min)
        return min;

    if (value > max)
        return max;

    return value;
}

bool isAlign(Point start, Point end) {
    return (start.getx() == end.getx() || start.gety() == end.gety());
}
void changeMouseCursor(int cursorType) {
    switch (cursorType) {
    case DRAWING:
        glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        break;
    case FILLING:
        glutSetCursor(GLUT_CURSOR_CROSSHAIR);
        break;
    default:
        glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        break;
    }
}
