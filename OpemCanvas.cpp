#include "OpenCanvas.h"
//////////////////////////////////////////////////////////////////////////////////////////////////
// Shape constructors
//We use shape as part of the Factory Method and the Prototype


//default
Shape::Shape() : length(0), width(0), colour("black"), positionX(0), positionY(0) {}

//normal
Shape::Shape(int length, int width, std::string colour, int posX, int posY) :
    length(length), width(width), colour(colour), positionX(posX), positionY(posY) {}
/////////////////////////////////////////////////////////////////////////////////////////////////







/////////////////////////////////////////////////////////////////////////////////////////////////
// Getters, we added this it wasn't apart of the specs
int Shape::getLength() const { return length; }
int Shape::getWidth() const { return width; }
std::string Shape::getColour() const { return colour; }
int Shape::getPositionX() const { return positionX; }
int Shape::getPositionY() const { return positionY; }

// Setters, same here
void Shape::setLength(int length) { this->length = length; }
void Shape::setWidth(int width) { this->width = width; }
void Shape::setColour(const std::string& colour) { this->colour = colour; }
void Shape::setPositionX(int x) { this->positionX = x; }
void Shape::setPositionY(int y) { this->positionY = y; }
///////////////////////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////////////////////////
// Rectangle Implementation, which is a concrete product

Rectangle::Rectangle() : Shape() {}

Rectangle::Rectangle(int length, int width, std::string colour, int posX, int posY) :
    Shape(length, width, colour, posX, posY) {}

Shape* Rectangle::clone() const {
    return new Rectangle(*this); // Creates a new Rectangle with same attributes
}

// Square Implementation, which is a concrete product

Square::Square() : Shape() {}

Square::Square(int size, std::string colour, int posX, int posY) :
    Shape(size, size, colour, posX, posY) {} // Note: length = width for square

Shape* Square::clone() const {
    return new Square(*this); // Creates a new Square with same attributes
}


// Textbox Implementation which is a concrete product
Textbox::Textbox() : Shape(), text("") {}

Textbox::Textbox(int length, int width, std::string colour, int posX, int posY, std::string text) :
    Shape(length, width, colour, posX, posY), text(text) {}

Shape* Textbox::clone() const {
    return new Textbox(*this); // Creates a new Textbox with same attributes
}

std::string Textbox::getText() const { return text; }
void Textbox::setText(const std::string& t) { text = t; }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Factory Implementations

Shape* RectangleFactory::createShape() const {
    return new Rectangle(); // Creates a default Rectangle
}

std::string RectangleFactory::toString() const {
    return "Rectangle Factory";
}

Shape* SquareFactory::createShape() const {
    return new Square(); // Creates a default Square
}

std::string SquareFactory::toString() const {
    return "Square Factory";
}

Shape* TextboxFactory::createShape() const {
    return new Textbox(); // Creates a default Textbox
}

std::string TextboxFactory::toString() const {
    return "Textbox Factory";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Extra
Canvas::~Canvas() {
    for (Shape* shape : shapes) {
        delete shape;
    }
}

void Canvas::addShape(Shape* shape) {
    shapes.push_back(shape);
}

std::vector<Shape*> Canvas::getShapes() const {
    return shapes;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////