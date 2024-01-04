#include "Filling.h"
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
        Pixel filledPixel;
        filledPixel.setX(x);
        filledPixel.setY(y);
        filledPixel.setColor(fillColor);
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