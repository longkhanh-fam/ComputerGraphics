#pragma once
#include "ShapeStorage.h"
#include "../Filling/Filling.h"
const int SELECTION_MODE = 100; // Choose a suitable value

class Moderator
{
public:
	

	static bool isColorMode;
	static bool isSelectionMode;
	static Shape* newShape;
	static Shape* selectedShape;
	static bool isDragging;
	static ShapeStorage shapeStorage;
	static CanvasState canvasState;
	static RGBColor fillColor;
	static RGBColor borderColor;
	static void display() {
		glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(1.0, 0.0, 0.0);

		shapeStorage.drawAllShapes(borderColor);
		//canvasState.reFillPixel();

		glutSwapBuffers();
		glFlush();

	}
	static void menuColorCallback(int value) {
		isColorMode = true;
		selectedShape = NULL;
		switch (value) {
		case RED:
			fillColor = { 1.0, 0.0, 0.0 };
			break;
		case GREEN:
			fillColor = { 0.0, 1.0, 0.0 };
			break;
		case BLUE:
			fillColor = { 0.0, 0.0, 1.0 };
			break;
		case YELLOW:
			fillColor = { 1.0, 1.0, 0.0 };
			break;
		case BLACK:
			fillColor = { 0.0, 0.0, 0.0 };
			break;
		case WHITE:
			fillColor = { 1.0, 1.0, 1.0 };
			break;
		}
	}
	static void menuCallBack(int value) {
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
				if (isColorMode) {
					selectedShape = nullptr;
					int xi = x;
					int yi = y;
					Shape* selectedShape = shapeStorage.selectShapeByPosition(x, y);

					changeMouseCursor(301);
					long long duration = measureTime(bind(boundaryFill, xi, yi, fillColor, borderColor, selectedShape));
					cout << "Time taken by boundaryFill: " << duration << " microseconds" << endl;
					changeMouseCursor(300);
				}
				else if (isSelectionMode)
				{
					int xi = x;
					int yi = y;
					selectedShape = shapeStorage.selectShapeByPosition(x, y);
					glutPostRedisplay();
				}
				else
				{
					selectedShape = nullptr;
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
	static void keyboard(unsigned char key, int x, int y) {
		double angle = 0.0;
		double ds = 1.0;
		if (isSelectionMode && selectedShape)
			{
				switch (key) {
					case 'l': // Clockwise rotation
						angle = 1.0;
						break;
					case 'r':
						angle = -1.0;  // Counterclockwise rotation
						break;
					case '+':
						ds = 1.1;
						break;
					case '-':
						ds = 0.9;
						break;
				}
				if (angle != 0.0)
					selectedShape->rotate(angle);
				else
					selectedShape->scale(ds, ds);
				glutPostRedisplay();
			}
	}

	static void specialKeyboard(int key, int x, int y) {
		 double dx = 0.0, dy = 0.0;
		if (isSelectionMode && selectedShape)
			{
				switch (key) {
					case GLUT_KEY_RIGHT:  
						dx = 1.0;
						break;
					case GLUT_KEY_LEFT: 
						dx = -1.0;   
						break;
					case GLUT_KEY_DOWN:  
						dy = 1.0;
						break;
					case GLUT_KEY_UP: 
						dy = -1.0;   
						break;
				}
				selectedShape->translate(dx, dy); 
				glutPostRedisplay();
			}
	}
	

	
};
Shape* Moderator::newShape = new Line(Point(100, 100), Point(400, 400));
Shape* Moderator::selectedShape = NULL;
bool Moderator::isColorMode = false;
bool Moderator::isSelectionMode = false;
ShapeStorage Moderator::shapeStorage = ShapeStorage();
CanvasState Moderator::canvasState = CanvasState();
bool Moderator::isDragging = false;
RGBColor Moderator::fillColor = Colors::RED;
RGBColor Moderator::borderColor = Colors::WHITE;