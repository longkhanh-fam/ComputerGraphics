#pragma once
#ifndef __FILLING_H__
#define __FILLING_H__
#include "CanvasState.h"
#include <stack>
bool isInScreen(int x, int y) {
    return x > 0 && y > 0 && x < WINDOW_WIDTH && y < WINDOW_HEIGHT;
}
RGBColor GetPixel(int x, int y)
{
    float pixels[3];
    glReadPixels(x, WINDOW_HEIGHT - y, 1.0, 1.0, GL_RGB, GL_FLOAT, pixels);
    RGBColor current = { pixels[0] ,pixels[1] , pixels[2] };
    return current;
}
void PutPixel(int x, int y, RGBColor fillColor)
{
    float f[3] = { fillColor.r(), fillColor.g(), fillColor.b() };
    glBegin(GL_POINTS);
    glColor3f(fillColor.r(), fillColor.g(), fillColor.b());
    glVertex2i(x, y);
    glEnd();
    glFlush();
    
}
void boundaryFill(int x, int y, RGBColor fillColor, RGBColor borderColor, Shape* newShape) {
    // Non-recursive implementation
    stack<pair<int, int>> s;
    s.push(make_pair(x, y));
    while (!s.empty()) {
        pair<int, int> it = s.top();
        s.pop();

        int x = it.first, y = it.second;
        RGBColor currentColor = GetPixel(x, y);


        if (!isInScreen(x, y) || currentColor == borderColor || currentColor == fillColor)
        {
            continue;
        }

        PutPixel(x, y, fillColor);
        Pixel filledPixel(x, y, fillColor);
        newShape->addFilledPixel(filledPixel);


        if (isInScreen(x + 1, y))
            s.push(make_pair(x + 1, y));
        if (isInScreen(x - 1, y))
            s.push(make_pair(x - 1, y));
        if (isInScreen(x, y + 1))
            s.push(make_pair(x, y + 1));
        if (isInScreen(x, y - 1))
            s.push(make_pair(x, y - 1));        
    }

}
#endif