#pragma once

#include "Filling/CanvasState.h"
#include "Utils/Utils.h"

class Matrix {
private:
    static const int MAX = 3;
    double elements[MAX][MAX];
public:
    // Initialize as an identity matrix
    Matrix() {
        for (int i = 0; i < MAX; i++)
            for (int j = 0; j < MAX; j++)
                elements[i][j] = (i == j) ? 1.0f : 0.0f;
        
    }

    Matrix(double a, double b, double c, double d, double e, double f) {
        elements[0][0] = a; elements[0][1] = b; elements[0][2] = c;
        elements[1][0] = d; elements[1][1] = e; elements[1][2] = f;
        elements[2][0] = 0; elements[2][1] = 0; elements[2][2] = 1;
    }
public:
    //Operators
   


    Point operator*(const Point& p) const {
        Point result;
        result.setX(elements[0][0] * p.getx() + elements[0][1] * p.gety() );
        result.setY(elements[1][0] * p.getx() + elements[1][1] * p.gety() );
        return result;
    }

    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            for (int i = 0; i < MAX; i++)
                for (int j = 0; j < MAX; j++)
                    elements[i][j] = other.elements[i][j];
        }
        return *this;
    }
    // Matrix multiplication
    void Multiply( Matrix other)  {
        Matrix temp = other * *this;
        *this = temp;
    }



public:
    Matrix& reset() {
        for (int i = 0; i < MAX; i++)
            for (int j = 0; j < MAX; j++)
                elements[i][j] = (i == j);
        return *this;
    }

public:

    // Rotate the matrix around the origin

    Matrix operator*(const Matrix& other) {
        Matrix result;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                result.elements[i][j] = 0.0f;  // Initialize to zero
                for (int k = 0; k < 3; k++) {
                    result.elements[i][j] += ( elements[i][k] * other.elements[k][j] );
                }
            }
        }
        return result;
    }
    void rotate(float angle) {
        float c = cos(angle);
        float s = sin(angle);

        Matrix rotationMatrix;
        rotationMatrix.elements[0][0] = c;
        rotationMatrix.elements[0][1] = s;
        rotationMatrix.elements[1][0] = -s;
        rotationMatrix.elements[1][1] = c;
        Multiply(rotationMatrix);
        
    }
    void translate (double offsetX, double offsetY) {
        Matrix newMatrix = Matrix();
        newMatrix.elements[0][2] = offsetX;
        newMatrix.elements[1][2] = offsetY;

        Multiply(newMatrix);
    }


    //Scale
    void scale(double sx, double sy) {
        Matrix newMatrix = Matrix();
        newMatrix.elements[0][0] = sx;
        newMatrix.elements[1][1] = sy;

        //*this = newMatrix * *this; 
        Multiply(newMatrix);
    }
    //Transform point
    Point TransformPoint(Point point) {
        double transformedX = this->elements[0][0] * point.getx() + this->elements[0][1] * point.gety() + elements[0][2];
        double transformedY = this->elements[1][0] * point.getx() + this->elements[1][1] * point.gety() + elements[1][2];
        return  {transformedX, transformedY};
    }

    //Transform vector of Points
    vector<Point> TransformPoints(vector<Point> points){
        vector<Point> newPoints;
        for (Point point : points) {
            newPoints.push_back(TransformPoint(point));
        }
        return newPoints;
    }


    //Transform vector of Points
    vector<Pixel> TransformPixels(vector<Pixel> pixels) {
        vector<Pixel> newPixels;
        for (Pixel pixel : pixels) {
            Point newpoint(pixel.getX(), pixel.getY());
            newpoint = TransformPoint(newpoint);
            newPixels.push_back(Pixel{newpoint.getx(), newpoint.gety(), pixel.getColor() });
        }
        return newPixels;
    }


    

    

};
