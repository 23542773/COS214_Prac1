#ifndef OPENCANVAS_H
#define OPENCANVAS_H

#include <string>
#include <vector>
#include <map>
#include <list>
#include <iostream>


class Shape;
class Memento;
class Canvas;


// =========================
// Factory Method + Prototype
// =========================
class Shape {


public:
    Shape();
    Shape(int length, int width, std::string colour, int posX, int posY);
    virtual ~Shape() = default;

    // Prototype
    virtual Shape* clone() const = 0;

    // Getters and Setters
    int getLength() const;
    int getWidth() const;
    std::string getColour() const;
    int getPositionX() const;
    int getPositionY() const;

    void setLength(int length);
    void setWidth(int width);
    void setColour(const std::string& colour);
    void setPositionX(int x);
    void setPositionY(int y);

    private:
    int length;
    int width;
    std::string colour;
    int positionX;
    int positionY;
};

// =========================
// Concrete Products
// =========================
class Rectangle : public Shape {
public:
    Rectangle();
    Rectangle(int length, int width, std::string colour, int posX, int posY);
    Shape* clone() const override;
};

class Square : public Shape {
public:
    Square();
    Square(int size, std::string colour, int posX, int posY);
    Shape* clone() const override;
};

class Textbox : public Shape {
private:
    std::string text;
public:
    Textbox();
    Textbox(int length, int width, std::string colour, int posX, int posY, std::string text);
    Shape* clone() const override;

    std::string getText() const;
    void setText(const std::string& t);
};

// =========================
// Factory Base Class
// =========================
class ShapeFactory {
public:
    virtual ~ShapeFactory() = default;
protected:
    virtual Shape* createShape() const = 0;
    virtual std::string toString() const = 0;
};

// =========================
// Concrete Factories
// =========================
class RectangleFactory : public ShapeFactory {
public:
    Shape* createShape() const override;
    std::string toString() const override;
};

class SquareFactory : public ShapeFactory {
public:
    Shape* createShape() const override;
    std::string toString() const override;
};

class TextboxFactory : public ShapeFactory {
public:
    Shape* createShape() const override;
    std::string toString() const override;
};

// =========================
// Memento Pattern
// =========================
class Memento {
private:
    std::vector<Shape*> shapesSnapshot;

public:
    Memento(const std::vector<Shape*>& elements);
    std::vector<Shape*> getSavedState() const;
};

class CareTaker {
private:
    std::vector<Memento*> history;

public:
    ~CareTaker();
    void addMemento(Memento* m);
    Memento* getLastMemento();
};

// =========================
// Canvas (Factory + Memento)
// =========================
class Canvas {
private:
    std::vector<Shape*> shapes;

public:
    ~Canvas();

    void addShape(Shape* shape);
    std::vector<Shape*> getShapes() const;

    // Memento
    Memento* captureCurrent() const;
    void undoAction(Memento* prev);
};

// =========================
// Template Method
// =========================
class ExportCanvas {
protected:
    Canvas* canvas;

public:
    ExportCanvas(Canvas* c);
    virtual ~ExportCanvas() = default;

    void exportCanvas(); // Template method

    virtual void prepareCanvas() = 0;
    virtual void renderElements() = 0;
    virtual void saveToFile() = 0;
};

class PNGExporter : public ExportCanvas {
public:
    PNGExporter(Canvas* c);
    void prepareCanvas() override;
    void renderElements() override;
    void saveToFile() override;
};

class PDFExporter : public ExportCanvas {
public:
    PDFExporter(Canvas* c);
    void prepareCanvas() override;
    void renderElements() override;
    void saveToFile() override;
};

#endif // OPENCANVAS_H