#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"

using namespace std;

TEST (Sort, sortByIncreasingPerimeter) {
    
    Rectangle rec1(0, 0, 2, 6, "rec1");             // rec1's perimeter = 16
    Circle cir1(0, 0, 1, "cir1");                   // cir1's perimeter = 6.28
    Circle cir2(0, 0, 2, "cir2");                   // cir2's perimeter = 12.56
    vertex v1 = {0, 0}, v2 = {4, 0}, v3 = {2, 2};
    Triangle tri1(v1, v2, v3, "tri1");              // tri1's perimeter = 9.64
    
    list<Shape * > shapesList ;
    
    shapesList.push_back (&rec1);
    shapesList.push_back (&cir1);
    shapesList.push_back (&cir2);
    shapesList.push_back (&tri1);
    
    Sort::sortByIncreasingPerimeter(&shapesList);
    list<Shape * >::iterator it = shapesList.begin();
    
    ASSERT_EQ(cir1.getShapeName(), (*it)->getShapeName());  // compare shape's name
    ++it;
    ASSERT_EQ(tri1.getShapeName(), (*it)->getShapeName());
    ++it;
    ASSERT_EQ(cir2.getShapeName(), (*it)->getShapeName());
    ++it;
    ASSERT_EQ(rec1.getShapeName(), (*it)->getShapeName());
    
}

TEST (Sort, sortByDecreasingPerimeter) {

    Rectangle rec1(0, 0, 2, 6, "rec1");             // rec1's perimeter = 16
    Circle cir1(0, 0, 1, "cir1");                   // cir1's perimeter = 6.28
    Circle cir2(0, 0, 2, "cir2");                   // cir2's perimeter = 12.56
    vertex v1 = {0, 0}, v2 = {4, 0}, v3 = {2, 2};
    Triangle tri1(v1, v2, v3, "tri1");              // tri1's perimeter = 9.64
    
    list<Shape * > shapesList ;
    
    shapesList.push_back (&rec1);
    shapesList.push_back (&cir1);
    shapesList.push_back (&cir2);
    shapesList.push_back (&tri1);
    
    Sort::sortByDecreasingPerimeter(&shapesList);
    list<Shape * >::iterator it = shapesList.begin();
    
    ASSERT_EQ(rec1.getShapeName(), (*it)->getShapeName());  // compare shape's name
    ++it;
    ASSERT_EQ(cir2.getShapeName(), (*it)->getShapeName());
    ++it;
    ASSERT_EQ(tri1.getShapeName(), (*it)->getShapeName());
    ++it;
    ASSERT_EQ(cir1.getShapeName(), (*it)->getShapeName());
    
}

TEST (Sort, sortByIncreasingArea) {
    
    Rectangle rec1(0, 0, 2, 6, "rec1");             // rec1's area = 12
    Circle cir1(0, 0, 1, "cir1");                   // cir1's area = 3.14
    Circle cir2(0, 0, 2, "cir2");                   // cir2's area = 12.56
    vertex v1 = {0, 0}, v2 = {4, 0}, v3 = {2, 2};
    Triangle tri1(v1, v2, v3, "tri1");              // tri1's area = 4

    list<Shape * > shapesList ;
    
    shapesList.push_back (&rec1);
    shapesList.push_back (&cir1);
    shapesList.push_back (&cir2);
    shapesList.push_back (&tri1);
    
    Sort::sortByIncreasingArea(&shapesList);
    list<Shape * >::iterator it = shapesList.begin();
    
    ASSERT_EQ(cir1.getShapeName(), (*it)->getShapeName());  // compare shape's name
    ++it;
    ASSERT_EQ(tri1.getShapeName(), (*it)->getShapeName());
    ++it;
    ASSERT_EQ(rec1.getShapeName(), (*it)->getShapeName());
    ++it;
    ASSERT_EQ(cir2.getShapeName(), (*it)->getShapeName());
    
}

TEST (Sort, sortByDecreasingArea) {

    Rectangle rec1(0, 0, 2, 6, "rec1");             // rec1's area = 12
    Circle cir1(0, 0, 1, "cir1");                   // cir1's area = 3.14
    Circle cir2(0, 0, 2, "cir2");                   // cir2's area = 12.56
    vertex v1 = {0, 0}, v2 = {4, 0}, v3 = {2, 2};
    Triangle tri1(v1, v2, v3, "tri1");              // tri1's area = 4
    
    list<Shape * > shapesList ;
    
    shapesList.push_back (&rec1);
    shapesList.push_back (&cir1);
    shapesList.push_back (&cir2);
    shapesList.push_back (&tri1);
    
    Sort::sortByDecreasingArea(&shapesList);
    list<Shape * >::iterator it = shapesList.begin();
    
    ASSERT_EQ(cir2.getShapeName(), (*it)->getShapeName());  // compare shape's name
    ++it;
    ASSERT_EQ(rec1.getShapeName(), (*it)->getShapeName());
    ++it;
    ASSERT_EQ(tri1.getShapeName(), (*it)->getShapeName());
    ++it;
    ASSERT_EQ(cir1.getShapeName(), (*it)->getShapeName());

}

TEST (Sort, sortByIncreasingCompactness) {

    Rectangle rec1(0, 0, 2, 6, "rec1");             // rec1's compactness = 0.75
    Circle cir1(0, 0, 1, "cir1");                   // cir1's compactness = 0.5
    Circle cir2(0, 0, 2, "cir2");                   // cir2's compactness = 1
    vertex v1 = {0, 0}, v2 = {4, 0}, v3 = {2, 2};
    Triangle tri1(v1, v2, v3, "tri1");              // tri1's compactness = 0.41
    
    list<Shape * > shapesList ;
    
    shapesList.push_back (&rec1);
    shapesList.push_back (&cir1);
    shapesList.push_back (&cir2);
    shapesList.push_back (&tri1);
    
    Sort::sortByIncreasingCompactness(&shapesList);
    list<Shape * >::iterator it = shapesList.begin();
    
    ASSERT_EQ(tri1.getShapeName(), (*it)->getShapeName());  // compare shape's name
    ++it;
    ASSERT_EQ(cir1.getShapeName(), (*it)->getShapeName());
    ++it;
    ASSERT_EQ(rec1.getShapeName(), (*it)->getShapeName());
    ++it;
    ASSERT_EQ(cir2.getShapeName(), (*it)->getShapeName());
    
}

#endif
