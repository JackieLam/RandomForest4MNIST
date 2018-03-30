#include "FileWriter.h"

FileWriter::FileWriter()
{
    
}

void FileWriter::writeResult(int *votes, string resultFilePath)
{
    ofstream outfile(resultFilePath);
    outfile << "id,label" << "\r";
    for (int row = 0; row < NUM_TEST_ROW; row++) {
        ostringstream convert;
        convert << row+1;
        outfile << convert.str() << ",";
        
        // Count out the label according to the votes
        int maxCount = 0;
        int final_decision = 0;
        vector<int> maxVector;
        for (int cate = 0; cate < NUM_CATEGORIES; cate++)
            if (votes[row * NUM_CATEGORIES + cate] >= maxCount) {
                maxCount = votes[row * NUM_CATEGORIES + cate];
                final_decision = cate;
            }
        
        for (int cate = 0; cate < NUM_CATEGORIES; cate++)
            if (votes[row * NUM_CATEGORIES + cate] == maxCount)
                maxVector.push_back(cate);
        
        if (maxVector.size() > 1) {
            srand(unsigned(time(NULL)));
            final_decision = maxVector.at(rand() % (maxVector.size()-1));
        }
        ostringstream convert_label;
        convert_label << final_decision;
        outfile << convert_label.str() << "\r";
    }
    
    outfile.close();
}