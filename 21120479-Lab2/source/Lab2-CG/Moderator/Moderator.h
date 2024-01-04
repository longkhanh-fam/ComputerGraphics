#pragma once
#include "ShapeStorage.h"
#include "../Utils/Utils.h"

const int SELECTION_MODE = 100; // Choose a suitable value
class Moderator
{
private:
	static bool isColorMode;
	static bool isSelectionMode;
	static Shape* newShape;
	static Shape* selectedShape;
	static bool isDragging;
	static ShapeStorage shapeStorage;
	static RGBColor fillColor;
	static RGBColor borderColor;
public:
	~Moderator()
	{
		delete Moderator::newShape;
	}
public:

	static void display() {
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0, 1.0, 1.0);
		shapeStorage.drawAllShapes(borderColor);
		glutSwapBuffers();
		glFlush();
	}
	static void menuColorCallback(int value) {
		isColorMode = true;
		selectedShape = NULL;
		switch (value) {
		case RED:
			fillColor = Colors::RED;
			break;
		case GREEN:
			fillColor = Colors::GREEN;
			break;
		case BLUE:
			fillColor = Colors::BLUE;
			break;
		case YELLOW:
			fillColor = Colors::YELLOW;
			break;
		case BLACK:
			fillColor = Colors::BLACK;
			break;
		case WHITE:
			fillColor = Colors::WHITE;
			break;
		case MAGENTA:
			fillColor = Colors::MAGENTA;
			break;
		}
	}
	static void menuCallBack(int value) {
		if(selectedShape)
			selectedShape->setSelected(false);
		selectedShape = NULL;
		isColorMode = false;  // Ensure color mode is off
		if (value == SELECTION_MODE) {
			isSelectionMode = true;
		}
		else {
			isSelectionMode = false;
			createdShape = static_cast<ShapeStorage::ShapeType>(value);
		}
	}

	static void createMenu(void) {

		int colorSubMenu = glutCreateMenu(menuColorCallback);
		glutSetMenu(colorSubMenu); // Set the current menu to the triangle submenu
		glutAddMenuEntry("Red", RED);
		glutAddMenuEntry("Green", GREEN);
		glutAddMenuEntry("Blue", BLUE);
		glutAddMenuEntry("Yellow", YELLOW);
		glutAddMenuEntry("Black", BLACK);
		glutAddMenuEntry("White", WHITE);
		glutAddMenuEntry("Magenta", MAGENTA);


		int triangleSubMenu = glutCreateMenu(menuCallBack); // Submenu for triangles
		glutSetMenu(triangleSubMenu); // Set the current menu to the triangle submenu
		glutAddMenuEntry("Equilateral Triangle", ShapeStorage::EQUIL_TRIANGLE);
		glutAddMenuEntry("Isosceles Triangle", ShapeStorage::ISOSCELES_TRIANGLE);


		int quadrilateralSubmenu = glutCreateMenu(menuCallBack);
		glutSetMenu(quadrilateralSubmenu); // Set the current menu to the quadrilateralSubmenu
		glutAddMenuEntry("Rectangle", ShapeStorage::RECTANGLE);
		glutAddMenuEntry("Square", ShapeStorage::SQUARE);

		int ovalSubMenu = glutCreateMenu(menuCallBack);
		glutSetMenu(ovalSubMenu); // Set the current menu to the ovalSubMenu
		glutAddMenuEntry("Circle", ShapeStorage::CIRCLE);
		glutAddMenuEntry("Ellipse", ShapeStorage::ELLIPSE);


		int polygonSubMenu = glutCreateMenu(menuCallBack);
		glutSetMenu(polygonSubMenu); // Set the current menu to the polygonSubMenu
		glutAddMenuEntry("Pentagon", ShapeStorage::PENTAGON);
		glutAddMenuEntry("Hexagon", ShapeStorage::HEXAGON);

		int otherSubMenu = glutCreateMenu(menuCallBack);
		glutSetMenu(otherSubMenu); // Set the current menu to the otherSubMenu
		glutAddMenuEntry("Arrow", ShapeStorage::ARROW);
		glutAddMenuEntry("Star", ShapeStorage::STAR);

		int signSubMenu = glutCreateMenu(menuCallBack);
		glutSetMenu(signSubMenu); // Set the current menu to the signSubMenu
		glutAddMenuEntry("Plus", ShapeStorage::PLUS);
		glutAddMenuEntry("Minus", ShapeStorage::MINUS);
		glutAddMenuEntry("Multiply", ShapeStorage::MULTIPLY);
		glutAddMenuEntry("Divide", ShapeStorage::DIVIDE);


		int menu_id = glutCreateMenu(menuCallBack);
		glutAddSubMenu("Color", colorSubMenu);
		glutAddMenuEntry("Line", ShapeStorage::LINE);
		glutAddSubMenu("Triangle", triangleSubMenu);
		glutAddSubMenu("Quadrilateral", quadrilateralSubmenu);
		glutAddSubMenu("Oval", ovalSubMenu);
		glutAddSubMenu("Polygon", polygonSubMenu);
		glutAddSubMenu("Other", otherSubMenu);
		glutAddSubMenu("MathSign", signSubMenu);
		glutAddMenuEntry("Selection Mode", SELECTION_MODE);
		glutAttachMenu(GLUT_RIGHT_BUTTON);
	}

	static void mouse(int button, int state, int x, int y) {
		if (button == GLUT_LEFT_BUTTON) {
			if (state == GLUT_DOWN) {
				if (isColorMode) {//Color Mode
					int xi = x;
					int yi = y;
					newShape->setFillColor(fillColor);
					newShape->setFillPoint(xi, yi);
					changeMouseCursor(FILLING);
					long long duration = measureTime(bind(boundaryFill, xi, yi, fillColor, borderColor, newShape));
					cout << "Time taken by boundaryFill: " << duration << " microseconds" << endl;
					changeMouseCursor(DRAWING);
				}
				else if (isSelectionMode) // Selection Mode
				{
					int xi = x;
					int yi = y;
					selectedShape = shapeStorage.selectShapeByPosition(x, y);
					glutPostRedisplay();
					

				}
				else //Drawing Mode
				{
					glColor3f(borderColor.r(), borderColor.g(), borderColor.b());
					isDragging = true;
					newShape = ShapeStorage::createShapeType(createdShape, x, y);
					shapeStorage.addShape(newShape);
					//glutPostRedisplay();
				}

			}
			else if (state == GLUT_UP && isDragging) {
				isDragging = false; // Set dragging to false here
				// Remove resetting of newShape to nullptr
				// newShape = nullptr;
				glutPostRedisplay();
			}
		}
	}
	static void mouseMotion(int x, int y) {
		if (newShape && isDragging)
		{
			newShape->setEnd(x, y);
			glutPostRedisplay();
		}
	}



};
Shape* Moderator::newShape = new Line(Point(100, 100), Point(400, 400));
Shape* Moderator::selectedShape = NULL;
bool Moderator::isColorMode = false;
bool Moderator::isSelectionMode = false;
ShapeStorage Moderator::shapeStorage = ShapeStorage();
bool Moderator::isDragging = false;
RGBColor Moderator::fillColor = Colors::RED;
RGBColor Moderator::borderColor = Colors::WHITE;