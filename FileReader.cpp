#include "FileReader.h"
#include <cmath>

#define NUM_INFILE 4

// Private methods

void FileReader::split(const string& src, const string& delim, int rowNum)
{
    if (src == "") return;
    
    // int rowNum;
    string str = src;
    string::size_type start = 0, index;
    string id_num, user_id, item_id, rating;
    string valueStr;
    /*
    index = str.find_first_of(delim, start);
    id_num = str.substr(start, index-start);
    rowNum = atoi(id_num.c_str()) - 1;
    start = str.find_first_not_of(delim, index);*/
    
	int cnt = 0;
    for (int cnt = 0; cnt < colCnt-1; cnt++) {
        index = str.find_first_of(delim, start);
		if (index > 1000000) cout << "index " << index << endl;
        valueStr = str.substr(start, index-start);
        short value = (short)atoi(valueStr.c_str());
        dataSet[rowNum * colCnt + cnt] = value;
        start = str.find_first_not_of(delim, index);
    }
    
    index = str.find_first_of("\r", start);
    valueStr = str.substr(start, index-start);
    short value = (short)atoi(valueStr.c_str());
    dataSet[rowNum * colCnt + colCnt-1] = value;
}

void FileReader::readSingleFile(string filePath)
{
    int rowCnt = 0;
    ifstream infile(filePath);
    string word;
    string delim(",");
    string textline;
    if(infile.good())
    {
		
        while(getline(infile, textline))
        {
            split(textline, delim, rowCnt);
            rowCnt++;
            if (rowCnt >= row_eachfile) {
                infile.close();
                return;
            }
        }
    }
    else {
        cout << "FILE OPEN ERROR" << endl;
    }
	cout << endl;
    infile.close();
}

// Public methods

FileReader::FileReader(int rowCnt, int colCnt)
{
    this->rowCnt = rowCnt;
    this->colCnt = colCnt;
	this->row_eachfile = std::numeric_limits<int>::max();
    
    size_t nSize = rowCnt * colCnt * sizeof(short);
    
    char *pBuf = new char[nSize]; // 1 Byte for char
    dataSet = (short *)pBuf; // 2 Bytes for short
}


void FileReader::readFileList(string dirPath, int thresold)
{
	if (thresold != -1)
		this->row_eachfile = thresold;
	else
		this->row_eachfile = std::numeric_limits<int>::max();
    
	thread thrd[NUM_THREAD];
    for (int cnt = 1; cnt <= NUM_THREAD; cnt++) {
        ostringstream convert;
        convert << cnt;
        convert.str(); // convert the int count into string
        string fileName = dirPath + convert.str() + ".csv";
        cout << "Read file: " << fileName << endl;
        thrd[cnt-1] = thread(bind(&FileReader::readSingleFile, this, fileName));
    }
    
    for (int cnt = 1; cnt <= NUM_THREAD; cnt++)
        thrd[cnt-1].join();
}
