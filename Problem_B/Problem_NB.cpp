/**
 * @file  Problem_NB.cpp
 * @brief Problem_NB main implemention
 */

#include <cstdlib>
#include <iostream>
using namespace std;

#include "NBClassifier.h"

/*
 * 
 */
int main(int argc, char** argv) {

    if(argc != 4)
    {
        std::cout<<"[Error] Usage: Problem_NB <TrainFiles> <TestInputFile> <TestOutputFile>"<<std::endl;
        return -1;
    }
    std::string trainFile = argv[1];
    std::string testInput = argv[2];
    std::string testOutput = argv[3];
    
    DocSet docSet;
    if(!DocSet::readFromFile(trainFile, docSet))
    {
        std::cout<<"[Error] Problem_NB read file failed:"<<trainFile<<std::endl;
        return -1;
    }
    
    DocSet testDocSet;
    if(!DocSet::readFromFile(testInput, testDocSet))
    {
        std::cout<<"[Error] Problem_NB read file failed:"<<testInput<<std::endl;
        return -1;
    }
    
    std::set<ClassID> allClasses = testDocSet.getAllClasses();
    if(allClasses.size() != 2)
    {
        std::cout<<"[Error] Problem_NB only do binary Classify, "
                   "test file maybe classes to "<<allClasses.size()<<std::endl;
        return -1;
    }
    std::vector<ClassID> classIDArray(allClasses.begin(), allClasses.end());
    
    NBClassifier nbClassifier(classIDArray[0], classIDArray[1]);
    nbClassifier.train(docSet);
    
    DocSet outputDocSet;
    outputDocSet.addClass(classIDArray[0]);
    outputDocSet.addClass(classIDArray[1]);
    
    for(int i = 0; i < testDocSet.getDocCount(); i++)
    {
        ClassID classID = nbClassifier.predict(testDocSet.getDoc(i));
        DocVector docVector = testDocSet.getDocA(i);
        docVector.setClassID(classID);
        outputDocSet.addDoc(docVector);
    }
    if(!DocSet::writeToFile(testOutput, outputDocSet))
    {
        std::cout<<"[Error] Problem_DAGNB write file failed:"<<testOutput<<std::endl;
        return -1;
    }
    return 0;
}

