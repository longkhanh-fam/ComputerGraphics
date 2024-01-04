#pragma once

#include "Shape/Oval.h"
#include "Shape/MathSign.h"
#include "../Filling/Filling.h"

int Shape::nextId = 0;
class ShapeStorage {
private:
    vector<Shape*> shapes;
    Shape* selectedShape;
public:
    ShapeStorage() {
        selectedShape = nullptr;
    }


    ~ShapeStorage() {
        clearAllShapes();
    }

    void addShape(Shape* shape) {
        shapes.push_back(shape);
    }

    void Clear() {
        for (auto it : shapes)
        {
            delete it;
            it = NULL;
        }
        shapes.empty();
    }
    Shape* selectShape(int mouseX, int mouseY) {
        // Iterate through shapes and check if the mouse coordinates intersect with any shape's bounding box
        for (Shape* shape : shapes) {
            // Implement logic to check for intersection with the shape's bounding box
            // If intersection is found, return the shape
        }
        return nullptr; // If no shape is found
    }

    void removeShape(Shape* shape) {
        auto it = std::find(shapes.begin(), shapes.end(), shape);
        if (it != shapes.end()) {
            delete* it; // Free memory for the removed shape
            shapes.erase(it); // Remove the shape from the vector
        }
    }
    int getIndexOfSelectedShape(int x, int y)
    {
        int i = 0;
        for (Shape* shape : shapes) {
            if (shape->isPointInside(x, y))
            {
                cout << i << endl;
                
                return i;
            }
            i++;
        }
        cout << i << endl;
        return -1;
    }
    Shape* selectShapeAtIndex(int index) {
        // Iterate through shapes and check if the mouse coordinates intersect with any shape's bounding box
        shapes[index]->setSelected(true);
        return shapes[index];
    }
    Shape* selectShapeByPosition(int x, int y)
    {
        if (getIndexOfSelectedShape(x, y) == -1)
            return NULL;


        Shape* newSelectedShape = selectShapeAtIndex(getIndexOfSelectedShape(x, y));

            if (newSelectedShape != nullptr) {
                if (selectedShape != nullptr) {
                    selectedShape->setSelected(false); // Deselect the previous shape
                }
                selectedShape = newSelectedShape; // Update the selected shape
                selectedShape->setSelected(true); // Set the new shape as selected
            }

        return selectedShape;
    }

    void clearAllShapes() {
        for (Shape* shape : shapes) {
            delete shape; // Free memory for all shapes
        }
        shapes.clear(); // Clear the vector
    }
public:
    void drawAllShapes(RGBColor borderColor) {
        for (Shape* shape : shapes) {
            if (shape->isSelected()) {
                glColor3f(0.0, 1.0, 1.0); // Set highlight color
                glLineWidth(3.0f); // Set border width
                shape->draw(); // Draw the shape's outline first
               
            }
            glLineWidth(1.0f); // Set border width
            glColor3f(borderColor.r(), borderColor.g(), borderColor.b());
            shape->draw(); // Draw the shape's body
            shape->filling();
        }
    }


public:
    enum ShapeType {
        LINE, RECTANGLE, TRIANGLE, EQUIL_TRIANGLE, ISOSCELES_TRIANGLE,
        SQUARE, CIRCLE, ELLIPSE, PENTAGON, HEXAGON, ARROW, PLUS, STAR, MINUS, DIVIDE, MULTIPLY
    };

    static Shape* createShapeType(ShapeType type, int x, int y) {

        switch (type) {
        case LINE:
            return new Line(Point(x, y), Point(x, y), Colors::BLUE);


        case ISOSCELES_TRIANGLE:
            return new IsoRightTriangle(Point(x, y), Point(x, y), Colors::BLUE);
        case EQUIL_TRIANGLE:
            return new EquilTriangle(Point(x, y), Point(x, y), Colors::BLUE);
        case RECTANGLE:
            return new Rectangle(Point(x, y), Point(x, y), Colors::BLUE);
        case SQUARE:
            return new Square(Point(x, y), Point(x, y), Colors::BLUE);
        case HEXAGON:
            return new Hexagon(Point(x, y), Point(x, y), Colors::BLUE);
        case PENTAGON:
            return new Pentagon(Point(x, y), Point(x, y), Colors::BLUE);
        case ARROW:
            return new Arrow(Point(x, y), Point(x, y), Colors::BLUE);
        case STAR:
            return new Star(Point(x, y), Point(x, y), Colors::BLUE);
        case PLUS:
            return new Plus(Point(x, y), Point(x, y), Colors::BLUE);
        case MINUS:
            return new Minus(Point(x, y), Point(x, y), Colors::BLUE);
        case MULTIPLY:
            return new Multiply(Point(x, y), Point(x, y), Colors::BLUE);
        case DIVIDE:
            return new Divide(Point(x, y), Point(x, y), Colors::BLUE);
        case CIRCLE:
            return new Circle(Point(x, y), Point(x, y), Colors::BLUE);
        case ELLIPSE:
            return new Ellipse(Point(x, y), Point(x, y), Colors::BLUE);


        }
    }

      

};

ShapeStorage::ShapeType createdShape = ShapeStorage::LINE;