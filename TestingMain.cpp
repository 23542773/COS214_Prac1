#include "OpenCanvas.h"
#include <iostream>
#include <memory>

//test factory to strings
void testFactoryToString() {
    std::cout << "\n=== TESTING FACTORY TOSTRING METHODS ===\n";
    
    RectangleFactory rectFactory;
    SquareFactory squareFactory;
    TextboxFactory textboxFactory;
    
    std::cout << "Rectangle Factory: " << rectFactory.toString() << std::endl;
    std::cout << "Square Factory: " << squareFactory.toString() << std::endl;
    std::cout << "Textbox Factory: " << textboxFactory.toString() << std::endl;
}

// Test ExportCanvas with null canvas
void testExportCanvasNull() {
    std::cout << "\n=== TESTING EXPORT CANVAS WITH NULL ===\n";
    
    PNGExporter pngExporter(nullptr);
    pngExporter.exportCanvas();
    
    PDFExporter pdfExporter(nullptr);
    pdfExporter.exportCanvas(); 
}

// Test destructors explicitly 
void testDestructors() {
    std::cout << "\n=== TESTING DESTRUCTORS ===\n";
    
    // Test CareTaker destructor with mementos
    {
        CareTaker* caretaker = new CareTaker();
        Canvas canvas;
        canvas.addShape(new Rectangle(10, 20, "blue", 0, 0));
        
        // Add multiple mementos to test cleanup
        caretaker->addMemento(canvas.captureCurrent());
        caretaker->addMemento(canvas.captureCurrent());
        
        delete caretaker; // This should trigger destructor cleanup
        std::cout << "CareTaker destructor tested\n";
    }
    
    // Test Canvas destructor
    {
        Canvas* canvas = new Canvas();
        canvas->addShape(new Rectangle(10, 20, "red", 0, 0));
        canvas->addShape(new Square(15, "blue", 5, 5));
        delete canvas; // This should clean up all shapes
        std::cout << "Canvas destructor tested\n";
    }
}

// Test default constructors thorough
void testDefaultConstructors() {
    std::cout << "\n=== TESTING DEFAULT CONSTRUCTORS ===\n";
    
    Rectangle rect;
    std::cout << "Default Rectangle: " << rect.getLength() << "x" << rect.getWidth() 
              << " color:" << rect.getColour() << " at (" << rect.getPositionX() 
              << "," << rect.getPositionY() << ")\n";
    
    Square square;
    std::cout << "Default Square: " << square.getLength() << "x" << square.getWidth() 
              << " color:" << square.getColour() << " at (" << square.getPositionX() 
              << "," << square.getPositionY() << ")\n";
              
    Textbox textbox;
    std::cout << "Default Textbox: " << textbox.getLength() << "x" << textbox.getWidth() 
              << " color:" << textbox.getColour() << " text:'" << textbox.getText() 
              << "' at (" << textbox.getPositionX() << "," << textbox.getPositionY() << ")\n";
}

// Test more Canvas addShape null cases
void testCanvasAddShapeNull() {
    std::cout << "\n=== TESTING CANVAS ADD SHAPE NULL ===\n";
    
    Canvas canvas;
    
    // Add some valid shapes first
    canvas.addShape(new Rectangle(10, 20, "blue", 0, 0));
    std::cout << "Canvas has " << canvas.getShapes().size() << " shapes after adding rectangle\n";
    
    // Try to add null shape
    canvas.addShape(nullptr);
    std::cout << "Canvas has " << canvas.getShapes().size() << " shapes after adding null\n";
}

// Test empty memento operations
void testEmptyMementoOperations() {
    std::cout << "\n=== TESTING EMPTY MEMENTO OPERATIONS ===\n";
    
    // Test memento with empty canvas
    Canvas emptyCanvas;
    Memento* emptyMemento = emptyCanvas.captureCurrent();
    std::cout << "Created memento from empty canvas\n";
    
    // Test restoring empty state
    Canvas canvas;
    canvas.addShape(new Rectangle(10, 20, "blue", 0, 0));
    std::cout << "Canvas before restore: " << canvas.getShapes().size() << " shapes\n";
    
    canvas.undoAction(emptyMemento);
    std::cout << "Canvas after restoring empty state: " << canvas.getShapes().size() << " shapes\n";
    
    delete emptyMemento;
}

// Test CareTaker with multiple operations
void testCareTakerMultipleOperations() {
    std::cout << "\n=== TESTING CARETAKER MULTIPLE OPERATIONS ===\n";
    
    CareTaker caretaker;
    Canvas canvas;
    
    // Create multiple states
    canvas.addShape(new Rectangle(10, 20, "blue", 0, 0));
    caretaker.addMemento(canvas.captureCurrent());
    
    canvas.addShape(new Square(15, "red", 5, 5));
    caretaker.addMemento(canvas.captureCurrent());
    
    canvas.addShape(new Textbox(30, 10, "green", 10, 10, "test"));
    caretaker.addMemento(canvas.captureCurrent());
    
    // Retrieve all mementos to test getLastMemento thoroughly
    while (true) {
        Memento* m = caretaker.getLastMemento();
        if (!m) {
            std::cout << "No more mementos available\n";
            break;
        }
        std::cout << "Retrieved memento with " << m->getSavedState().size() << " shapes\n";
        delete m;
    }
    
    // Try to get memento from empty caretaker again
    Memento* shouldBeNull = caretaker.getLastMemento();
    if (!shouldBeNull) {
        std::cout << "Correctly returned null from empty caretaker\n";
    }
}

// Test clone operations more thoroughly
void testCloneEdgeCases() {
    std::cout << "\n=== TESTING CLONE EDGE CASES ===\n";
    
    // Test cloning shapes with extreme values
    Rectangle extremeRect(-10, 0, "", -100, -100);
    Shape* clonedExtreme = extremeRect.clone();
    std::cout << "Cloned extreme rectangle: " << clonedExtreme->getLength() 
              << "x" << clonedExtreme->getWidth() << " at (" 
              << clonedExtreme->getPositionX() << "," << clonedExtreme->getPositionY() << ")\n";
    delete clonedExtreme;
    
    // Test cloning textbox with empty text
    Textbox emptyTextbox(0, 0, "", 0, 0, "");
    Shape* clonedEmpty = emptyTextbox.clone();
    std::cout << "Cloned empty textbox text: '" 
              << dynamic_cast<Textbox*>(clonedEmpty)->getText() << "'\n";
    delete clonedEmpty;
}

//TESTING shape  setters
void testShapeSetters() {
    std::cout << "\n=== TESTING SHAPE SETTERS ===\n";
    Rectangle rect;
    rect.setLength(100);
    rect.setWidth(50);
    rect.setColour("purple");
    rect.setPositionX(10);
    rect.setPositionY(20);
    
    std::cout << "Modified rectangle: " 
              << rect.getLength() << "x" << rect.getWidth()
              << " color:" << rect.getColour()
              << " at (" << rect.getPositionX() << "," << rect.getPositionY() << ")\n";
}

//test construcgtor with parameter
void testTextboxWithText() {
    std::cout << "\n=== TESTING TEXTBOX WITH TEXT ===\n";
    Textbox tb(100, 50, "blue", 0, 0, "Initial text");
    std::cout << "Textbox text: " << tb.getText() << "\n";
    tb.setText("Updated text");
    std::cout << "After update: " << tb.getText() << "\n";
}

//test null calse
void testNullCases() {
    std::cout << "\n=== TESTING NULL CASES ===\n";
    Canvas canvas;
    // Test adding null shape
    canvas.addShape(nullptr);
    
    // Test undo with null memento
    canvas.undoAction(nullptr);
    
    // Test empty caretaker
    CareTaker ct;
    Memento* m = ct.getLastMemento();
    if (!m) {
        std::cout << "Correctly got null from empty caretaker\n";
    }
}

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

   
    testShapeSetters();
    testTextboxWithText();
    testNullCases();
    testFactoryToString();
    testExportCanvasNull();
    testDestructors();
    testDefaultConstructors();
    testCanvasAddShapeNull();
    testEmptyMementoOperations();
    testCareTakerMultipleOperations();
    testCloneEdgeCases();
    
    return 0;
}