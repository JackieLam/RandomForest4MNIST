#ifndef __Random_Forest__FileWriter__
#define __Random_Forest__FileWriter__

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Constants.h"
#include <vector>
#include <time.h>
using namespace std;

class FileWriter
{  
public:
    FileWriter();
    void writeResult(int *votes, string resultFilePath);
};

#endif /* defined(__Random_Forest__FileWriter__) */