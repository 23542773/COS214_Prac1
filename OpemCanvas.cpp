#include "OpenCanvas.h"
#include <iostream>
#include <algorithm>

//vector containing
Memento::Memento(const std::vector<Shape*>& elements){
   std::cout << "Creating memento with " << elements.size() << " shapes...\n";
    // Create deep copies of all shapes using their clone() method

     for (int i = 0; i < elements.size(); ++i) {
        Shape* shape = elements[i];
        if (shape != NULL) {
            shapesSnapshot.push_back(shape->clone());
        }
    }

    std::cout << "Memento created successfully with " << shapesSnapshot.size() << " shapes\n";
   
}

std::vector<Shape*> Memento::getSavedState() const {

     std::cout << "Retrieving saved state with " << shapesSnapshot.size() << " shapes\n";
    return shapesSnapshot;
}

CareTaker::~CareTaker() {
    std::cout << "CareTaker destructor: Cleaning up " << history.size() << " mementos\n";
    
    for (int i = 0; i < history.size(); ++i) {
        Memento* memento = history[i];
        if (memento != NULL) {
            // Clean up the shapes in each memento
            std::vector<Shape*> shapes = memento->getSavedState();
            for (int j = 0; j < shapes.size(); ++j) {
                delete shapes[j];
            }
            delete memento;
        }
    }
    history.clear();

}


void CareTaker::addMemento(Memento* m) {

    if (m != NULL) {
        history.push_back(m);
        std::cout << "Memento added to history. Total mementos: " << history.size() << "\n";
    } else {
        std::cout << "Warning: Attempted to add null memento\n";
    }
}

Memento* CareTaker::getLastMemento() {

if (!history.empty()) {
        Memento* lastMemento = history.back();
        history.pop_back();
        std::cout << "Retrieved last memento. Remaining mementos: " << history.size() << "\n";
        return lastMemento;
    }
    
    std::cout << "No mementos available for retrieval\n";
    return NULL;

}


//canvas destrucotor

Canvas::~Canvas() {
for (int i = 0; i < shapes.size(); ++i) {
        delete shapes[i];
    }
    shapes.clear();

}

void Canvas::addShape(Shape* shape) {
 if (shape != NULL) {
        shapes.push_back(shape);
        std::cout << "Shape added to canvas. Total shapes: " << shapes.size() << "\n";
    } else {
        std::cout << "Warning: Attempted to add null shape to canvas\n";
    }
}

std::vector<Shape*> Canvas::getShapes() const {
       return shapes;
}

Memento* Canvas::captureCurrent() const{
 std::cout << "Capturing current canvas state...\n";
std::cout << "Current canvas has " << shapes.size() << " shapes\n";
    
    // Create and return a new memento with the current shapes
    return new Memento(shapes);

}

void Canvas::undoAction(Memento* prev) {
      if (prev == NULL) {
        std::cout << "Cannot undo: No memento provided\n";
        return;
    }
    
    std::cout << "Restoring canvas state from memento...\n";
    std::cout << "Current canvas has " << shapes.size() << " shapes\n";
    
    // Clear current shapes
    for (int i = 0; i < shapes.size(); ++i) {
        delete shapes[i];
    }
    shapes.clear();
    
    // Restore shapes from memento (create new copies using clone)
    std::vector<Shape*> savedShapes = prev->getSavedState();
    for (int i = 0; i < savedShapes.size(); ++i) {
        Shape* shape = savedShapes[i];
        if (shape != NULL) {
            shapes.push_back(shape->clone());
        }
    }
    
    std::cout << "Canvas state restored. New canvas has " << shapes.size() << " shapes\n";
}


//template method

ExportCanvas::ExportCanvas(Canvas* c) : canvas(c) {
       std::cout << "ExportCanvas created for canvas with " 
              << (canvas ? canvas->getShapes().size() : 0) << " shapes\n";
}

//Template method
void ExportCanvas::exportCanvas() {

     std::cout << "\n=== STARTING EXPORT PROCESS ===\n";
    
    if (canvas == NULL) {
        std::cout << "Error: No canvas to export\n";
        return;
    }
    
    std::cout << "Exporting canvas with " << canvas->getShapes().size() << " shapes\n";
    
    // Template method algorithm - calls abstract methods in specific order
    prepareCanvas();     // Step 1: Prepare the canvas for export
    renderElements();    // Step 2: Render all elements
    saveToFile();        // Step 3: Save to specific file format
    
    std::cout << "=== EXPORT PROCESS COMPLETED ===\n\n";
}


PNGExporter::PNGExporter(Canvas* c) : ExportCanvas(c) {
     std::cout << "PNGExporter initialized";
     
}

PDFExporter::PDFExporter(Canvas* c) : ExportCanvas(c) {
    std::cout << "PDFExporter initialized" << std::endl;
}

void PNGExporter::prepareCanvas() {
    std::cout << "PNG: Preparing canvas for PNG export" << std::endl;
}

void PNGExporter::renderElements() {
    std::cout << "PNG: Rendering elements for PNG format" << std::endl;
}

void PNGExporter::saveToFile() {
    std::cout << "PNG: Saving file as PNG format" << std::endl;
}


void PDFExporter::prepareCanvas() {
    std::cout << "PDF: Preparing canvas for PDF export" << std::endl;
}

void PDFExporter::renderElements() {
    std::cout << "PDF: Rendering elements for PDF format" << std::endl;
}

void PDFExporter::saveToFile() {
    std::cout << "PDF: Saving file as PDF format" << std::endl;
}



void PDFExporter::saveToFile() {
    std::cout << "File saved";


}

