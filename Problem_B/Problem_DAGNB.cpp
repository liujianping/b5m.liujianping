/**
 * @file  Problem_DAGNB.cpp
 * @brief Problem_DAGNB main implemention
 */

#include <cstdlib>
#include <iostream>

using namespace std;

#include "DAGNBClassifier.h"

/*
 * 
 */
int main(int argc, char** argv) {

    if(argc != 4)
    {
        std::cout<<"[Error] Usage: Problem_DAGNB <TrainFiles> <TestInputFile> <TestOutputFile>"<<std::endl;
        return -1;
    }
    std::string trainFile = argv[1];
    std::string testInput = argv[2];
    std::string testOutput = argv[3];
    
    DocSet docSet;
    if(!DocSet::readFromFile(trainFile, docSet))
    {
        std::cout<<"[Error] Problem_DAGNB read file failed:"<<trainFile<<std::endl;
        return -1;
    }
    
    
    DocSet testDocSet;
    if(!DocSet::readFromFile(testInput, testDocSet))
    {
        std::cout<<"[Error] Problem_DAGNB read file failed:"<<testInput<<std::endl;
        return -1;
    }
    
    DocSet outputDocSet;
    std::set<ClassID> allClasses = testDocSet.getAllClasses();
    for(std::set<ClassID>::iterator it = allClasses.begin(); 
        it != allClasses.end(); 
        it++)
    {
        outputDocSet.addClass(*it);
    }
    
    DAGNBClassifier dagnbClassifier;
    dagnbClassifier.setTrain(docSet);
    
    for(int i = 0; i < testDocSet.getDocCount(); i++)
    {
        ClassID classID = dagnbClassifier.predict(testDocSet.getDoc(i));
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


