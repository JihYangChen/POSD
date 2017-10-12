#include "include/Sort.h"
#include <iostream>

void Sort::sortByIncreasingPerimeter(std::list<Shape *> * shapeList) {
    
    auto perimeterSmaller = [](Shape * a, Shape * b) { return a->perimeter() < b->perimeter(); };
    shapeList->sort (perimeterSmaller);
    
}

void Sort::sortByDecreasingPerimeter(std::list<Shape *> * shapeList) {
    
    auto perimeterLarger = [](Shape * a, Shape * b) { return a->perimeter() > b->perimeter(); };
    shapeList->sort (perimeterLarger);
    
}

void Sort::sortByIncreasingArea(std::list<Shape *> * shapeList) {
    
    auto areaSmaller = [](Shape * a, Shape * b) { return a->area() < b->area(); };
    shapeList->sort (areaSmaller);
    
}

void Sort::sortByDecreasingArea(std::list<Shape *> * shapeList) {
    
    auto areaLarger = [](Shape * a, Shape * b) { return a->area() > b->area(); };
    shapeList->sort (areaLarger);
    
}

void Sort::sortByIncreasingCompactness(std::list<Shape *> * shapeList) {
    
    auto compactnessSmaller = [](Shape * a, Shape * b) {
        double polsbyPopper_A, polsbyPopper_B;
        polsbyPopper_A = (4 * M_PI * a->area()) / (a-> perimeter() * a -> perimeter());
        polsbyPopper_B = (4 * M_PI * b->area()) / (b-> perimeter() * b -> perimeter());
        return polsbyPopper_A < polsbyPopper_B;
    };
    shapeList->sort (compactnessSmaller);
    
}
