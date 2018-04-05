## Implementation Steps
* Decision Tree
    * Tree-based Regression
    * CART Algorithm
    * Gini Coefficient
* Random Forest
* Multithreading
## To Run the Project
* Note that you should adjust the 3 absolute directory paths in main.cpp according to your own computer environment to run the program.
* The original data file, test.csv and train.csv is equally seperated into 4 pieces. With file name test1.csvtest4.csv and train1.csvtrain4.csv. You should split the data before running it!

## Classes & Tech Details 
The general logic of the whole program could be inspected within the main.cpp.
1. DecisionTree - THE CORE PART OF THE PROGRAM. Use CART algorithm to implement the tree-based regression. I used Gini coefficient to decide the bestIndex and bestValue for splitting. Prepuning is implemented, while postpuning is neglected under the circumstances of random forest.
    * Prepuning 1: If (originGINI - newGINI < tolS), it means splitting under the current (bestIndex, bestValue) situation has minor influence on the dataSet. So just set the current node as a leaf node.
    * Prepuning 2: If the number of samples within either of the splitted dataSets < tolN, set it to leaf, for the reason that small set of samples is not persuasive during classification.

2. FileReader - Be responsible for reading the data in the .csv file, including both the train and the test data. I use 4 threads to read the data simultaneously using file input/output stream. So in the directory, I split the train.csv into train1.csv ~ train4.csv, each of which include 5000. The science is the same for the test.csv, seperated into 4 shares, each of which containing 10000 samples.
3. Tester - Run each sample way through a tree down to the leaf and return a classification result accordingly.
4. FileWriter - In charge of writing the results to out.csv after training and testing.

## Keynotes: Some Intriguing Markdowns 
### 1.Optimization measures
* (Unfinished)Use char to store the data matrix and process bitwise operation when doing calculation. While I currently use "short" to store the matrix, which is taking up twice the size of memory use.
* Use STL set to avoid duplicated value split operation.
* (Unfinished)Use non-recursive method (Heap) to build up the tree.
* Parallelization operation(Unfinished), multithreading when operating prediction in both one single tree and the whole forest.
### 2.Mathematical ideas
* When reducing the number of training features from p to vp, the number of rows for training should also be shrank to 2/3 of the original amount, so as to avoid high variances in the leaf nodes of the tree.
### 3.Adjustment
* Choose MODE instead of MEAN when creating leaf nodes. MEAN appears to be meaningless in this specific case.
