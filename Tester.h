#ifndef __Random_Forest__Tester__
#define __Random_Forest__Tester__

#include "Constants.h"
#include "DecisionTree.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class Tester
{
private:
    short *testData;
    string testFilePath;
    Node *root;
    
    
public:
    int cateCount[NUM_CATEGORIES];
    
    Tester(Node *root = NULL);
    void pointToData(short *dataSet);
    void changeRoot(Node *newRoot);
    int testResult(int rowNum);
    
    void logCalculate();
    void clearCateCount();
};

#endif /* defined(__Random_Forest__Tester__) */