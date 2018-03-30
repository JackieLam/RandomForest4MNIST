#include "FileReader.h"
#include "DecisionTree.h"
#include "Constants.h"
#include "Tester.h"
#include "FileWriter.h"
#include <functional>
#include <thread>
#include <mutex>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int *votes;
mutex io_mutex;
int treeCounter;
int cateCnt[NUM_CATEGORIES];

void forest_per_thread(short *trainDataSet, short *testDataSet)
{
    Tester tester;
    tester.pointToData(testDataSet);
    
    for (int i = 0; i < NUM_TREES; i++)
    {
		cout << "Begin creating the " << i << " th tree" << endl; 
        DecisionTree dtree(trainDataSet, 5);
        dtree.createTree();
        tester.changeRoot(dtree.getRoot());
        
        for (int row = 0; row < NUM_TEST_ROW; row++) {
            int row_result = tester.testResult(row);
            votes[row * NUM_CATEGORIES + row_result] += 1;
            cateCnt[row_result] += 1;
        }
        
        io_mutex.lock();
        cout << "Tree " << treeCounter++ << " finished testing!" << endl;
        cout << "=============50 Ex Case==============" << endl;
        for (int i = 0; i < 10; i++) {
            cout << "[" << i << "] ";
        }
        cout << endl;
        for (int i = 0; i < 50; i++) {
            cout << " ";
            for (int j = 0; j < NUM_CATEGORIES; j++) {
                cout << votes[i*NUM_CATEGORIES+j] << "  ";
            }
			cout << "max count : " << distance(votes+i*NUM_CATEGORIES, max_element(votes+i*NUM_CATEGORIES, votes+i*NUM_CATEGORIES+10));
            cout << endl;
        }
        cout << endl;
 
        io_mutex.unlock();
        
        dtree.clearData();
        tester.clearCateCount();
    }
}

int main(int argc, const char * argv[])
{
	// Initialize the [votes] for final calculation
    size_t nSize = NUM_TEST_ROW * NUM_CATEGORIES * sizeof(int);
    char *pBuf = new char[nSize];
    votes = (int *)pBuf;
    
    for (int cat = 0; cat < NUM_CATEGORIES; cat++) {
        cateCnt[cat] = 0;
    }

    // Reading with multithreading under the hood
    FileReader trainreader(NUM_ROW, NUM_COLUMN);
    trainreader.readSingleFile("C:/Users/I310276/Desktop/MNIST/train.csv");
    FileReader testreader(NUM_TEST_ROW, NUM_COLUMN-1);
    testreader.readSingleFile("C:/Users/I310276/Desktop/MNIST/test.csv");
	cout << "Finished reading the training and testing data" << endl; 

    // Multithreading calculation
	
    treeCounter = 0;
    thread thrd[NUM_THREAD];
    for (int cnt = 0; cnt < NUM_THREAD; cnt++)
        thrd[cnt] = thread(bind(&forest_per_thread, trainreader.dataSet, testreader.dataSet));
    
    for (int cnt = 0; cnt < NUM_THREAD; cnt++)
        thrd[cnt].join();
    
    FileWriter writer;
    writer.writeResult(votes, "D:/data/out.csv");
    
	getchar();
    return 0;
}
