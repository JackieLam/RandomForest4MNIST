#include "Tester.h"

// Public methods

Tester::Tester(Node *root)
{
    this->root = root;
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        cateCount[i] = 0;
    }
    
    size_t nSize = NUM_TEST_ROW * (NUM_COLUMN-1) * sizeof(short);
    char *pBuf = new char[nSize];
    testData = (short *)pBuf;
}

void Tester::pointToData(short *dataSet)
{
    this->testData = dataSet;
}

void Tester::changeRoot(Node *newRoot)
{
    this->root = NULL;
    this->root = newRoot;
}

int Tester::testResult(int rowNum)
{
    int category_out = 0;
    Node *rootMark = this->root;
    Node *cur = this->root;
    int spIndex = 0;
    short spValue = 0;
    
//    cout << "===========RUN LEFT RIGHT============== " << rowNum << endl;
//    cout << "Root " << " (" << cur->spInd << "," << cur->spVal << ")--";
    while ((cur->left != NULL) || (cur->right != NULL)) {
        spIndex = cur->spInd;
        spValue = cur->spVal;
        short pix = testData[rowNum * (NUM_COLUMN-1) + spIndex-1];
        if (pix <= spValue) {
            cur = cur->left;
//            cout << " L " << " (" << cur->spInd << "," << cur->spVal << ")";
        }
        else {
            cur = cur->right;
//            cout << " R " << " (" << cur->spInd << "," << cur->spVal << ")";
        }
    }
    category_out = cur->spVal;
//    cout << endl;
//    cout << "+++++[CATE RESULT] "<< category_out << endl;
    
    cateCount[category_out]++;
    this->root = rootMark;
    
    return category_out;
}

void Tester::logCalculate()
{
    cout << "==========Single Tree Test Result=========" << endl;
    int total_case = 0;
    for (int cnt = 0; cnt < NUM_CATEGORIES; cnt++) {
        cout << "[" << cnt << "] " << cateCount[cnt]
             << " --- " << (float)cateCount[cnt] / (float)NUM_TEST_ROW * 100
             << "%" << endl;
        total_case += cateCount[cnt];
    }
    cout << "[Cases count] " << total_case << endl;
}

void Tester::clearCateCount()
{
    for (int i = 0; i < NUM_CATEGORIES; i++)
        cateCount[i] = 0;
}