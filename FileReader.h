#ifndef __Random_Forest__FileReader__
#define __Random_Forest__FileReader__

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <functional>
#include <thread>
#include <mutex>
#include <limits>
#include "Constants.h"
using namespace std;

class FileReader
{
private:
	void split(const string& src, const string& delim, int rowNum);
    mutex io_mutex;
    int row_eachfile; // 应该读多少行
    int rowCnt, colCnt;
public:
    FileReader(int rowCnt = 0, int colCnt = 0);
    short *dataSet;
	void readSingleFile(string filePath); // parallel called by readFileList
    void readFileList(string dirPath, int thresold); // 唯一的对外接口
    /* -1 for reading the whole file*/
};

#endif /* defined(__Random_Forest__FileReader__) */
