#include "OpenCanvas.h"
#include <iostream>
#include <memory>

void testFactoryMethod() {
    std::cout << "\n=== TESTING FACTORY METHOD PATTERN ===\n";
    
    // Create factories
    RectangleFactory rectFactory;
    SquareFactory squareFactory;
    TextboxFactory textboxFactory;
    
    // Create shapes using factories
    Shape* rectangle = rectFactory.createShape();
    Shape* square = squareFactory.createShape();
    Shape* textbox = textboxFactory.createShape();
    
    // Verify creation
    std::cout << "Rectangle created: " << rectangle->getLength() << "x" << rectangle->getWidth() << std::endl;
    std::cout << "Square created: " << square->getLength() << "x" << square->getWidth() << std::endl;
    std::cout << "Textbox created with text: " << dynamic_cast<Textbox*>(textbox)->getText() << std::endl;
    
    // Clean up
    delete rectangle;
    delete square;
    delete textbox;
}

void testPrototypePattern() {
    std::cout << "\n=== TESTING PROTOTYPE PATTERN ===\n";
    
    // Create prototype objects
    Rectangle originalRect(10, 20, "blue", 5, 5);
    Square originalSquare(15, "red", 10, 10);
    Textbox originalTextbox(30, 10, "green", 0, 0, "Hello World");
    
    // Clone them
    Shape* rectClone = originalRect.clone();
    Shape* squareClone = originalSquare.clone();
    Shape* textboxClone = originalTextbox.clone();
    
    // Verify cloning
    std::cout << "Original Rectangle: " << originalRect.getLength() << "x" << originalRect.getWidth() 
              << ", Clone: " << rectClone->getLength() << "x" << rectClone->getWidth() << std::endl;
              
    std::cout << "Original Square: " << originalSquare.getLength() << "x" << originalSquare.getWidth() 
              << ", Clone: " << squareClone->getLength() << "x" << squareClone->getWidth() << std::endl;
              
    std::cout << "Original Textbox text: " << originalTextbox.getText() 
              << ", Clone text: " << dynamic_cast<Textbox*>(textboxClone)->getText() << std::endl;
    
    // Modify clones to verify deep copy
    rectClone->setLength(100);
    dynamic_cast<Textbox*>(textboxClone)->setText("Modified text");
    
    std::cout << "After modification - Original Rectangle width: " << originalRect.getLength() 
              << ", Clone width: " << rectClone->getLength() << std::endl;
    std::cout << "After modification - Original Textbox text: " << originalTextbox.getText() 
              << ", Clone text: " << dynamic_cast<Textbox*>(textboxClone)->getText() << std::endl;
    
    // Clean up
    delete rectClone;
    delete squareClone;
    delete textboxClone;
}

void testMementoPattern() {
    std::cout << "\n=== TESTING MEMENTO PATTERN ===\n";
    
    Canvas canvas;
    CareTaker caretaker;
    
    // Add some shapes to canvas
    canvas.addShape(new Rectangle(10, 20, "blue", 0, 0));
    canvas.addShape(new Square(15, "red", 5, 5));
    
    // Save state
    Memento* m1 = canvas.captureCurrent();
    caretaker.addMemento(m1);
    std::cout << "Canvas state 1 saved with " << canvas.getShapes().size() << " shapes\n";
    
    // Modify canvas
    canvas.addShape(new Textbox(30, 10, "green", 10, 10, "First text"));
    std::cout << "Canvas modified. Now has " << canvas.getShapes().size() << " shapes\n";
    
    // Save state again
    Memento* m2 = canvas.captureCurrent();
    caretaker.addMemento(m2);
    std::cout << "Canvas state 2 saved with " << canvas.getShapes().size() << " shapes\n";
    
    // Modify canvas further
    canvas.addShape(new Rectangle(50, 30, "yellow", 20, 20));
    dynamic_cast<Textbox*>(canvas.getShapes()[2])->setText("Updated text");
    std::cout << "Canvas modified again. Now has " << canvas.getShapes().size() << " shapes\n";
    
    // Undo to previous state
    Memento* lastState = caretaker.getLastMemento();
    if (lastState) {
        canvas.undoAction(lastState);
        std::cout << "After undo, canvas has " << canvas.getShapes().size() << " shapes\n";
        std::cout << "Textbox text: " << dynamic_cast<Textbox*>(canvas.getShapes()[2])->getText() << std::endl;
        delete lastState;
    }
    
    // Undo again to initial state
    lastState = caretaker.getLastMemento();
    if (lastState) {
        canvas.undoAction(lastState);
        std::cout << "After second undo, canvas has " << canvas.getShapes().size() << " shapes\n";
        delete lastState;
    }
}

void testTemplateMethodPattern() {
    std::cout << "\n=== TESTING TEMPLATE METHOD PATTERN ===\n";
    
    Canvas canvas;
    canvas.addShape(new Rectangle(10, 20, "blue", 0, 0));
    canvas.addShape(new Square(15, "red", 5, 5));
    canvas.addShape(new Textbox(30, 10, "green", 10, 10, "Export this"));
    
    // Test PNG export
    std::cout << "\nTesting PNG Export:\n";
    PNGExporter pngExporter(&canvas);
    pngExporter.exportCanvas();
    
    // Test PDF export
    std::cout << "\nTesting PDF Export:\n";
    PDFExporter pdfExporter(&canvas);
    pdfExporter.exportCanvas();
}

void testIntegration() {
    std::cout << "\n=== TESTING INTEGRATION OF ALL PATTERNS ===\n";
    
    // Create canvas and caretaker
    Canvas canvas;
    CareTaker caretaker;
    
    // Use factory to create shapes
    RectangleFactory rectFactory;
    SquareFactory squareFactory;
    TextboxFactory textboxFactory;
    
    // Add shapes to canvas
    canvas.addShape(rectFactory.createShape());
    canvas.addShape(squareFactory.createShape());
    canvas.addShape(textboxFactory.createShape());
    
    // Save state
    caretaker.addMemento(canvas.captureCurrent());
    
    // Clone a shape and add to canvas
    Shape* original = canvas.getShapes()[0];
    Shape* clone = original->clone();
    canvas.addShape(clone);
    
    // Export current state
    PNGExporter exporter(&canvas);
    exporter.exportCanvas();
    
    // Undo to previous state
    Memento* lastState = caretaker.getLastMemento();
    if (lastState) {
        canvas.undoAction(lastState);
        std::cout << "After undo, canvas has " << canvas.getShapes().size() << " shapes\n";
        delete lastState;
    }
}

int main() {
    testFactoryMethod();
    testPrototypePattern();
    testMementoPattern();
    testTemplateMethodPattern();
    testIntegration();
    
    return 0;
}