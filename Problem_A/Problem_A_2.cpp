/**
 * @file  Problem_A_2.cpp
 * @brief Problem_A_2 main implemention
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

#include "GramClassifier.h"
#include "strutil.h"
/*
 * Usage: Problem_A_2 <ProfileConfigure> <TestInputFile> <TestOutputFile>
 */
int main(int argc, char** argv) {

    if(argc != 4)
    {
        std::cout<<"[Error] Usage: Problem_A_2 <ProfileConfigure> <TestInputFile> <TestOutputFile>"<<std::endl;
        return -1;
    }
    
    GramClassifier gramClassifier;
    
    std::ifstream profile;
    profile.open(argv[1]);
    if(!profile.is_open()) 
    {
        std::cout<<"[Error] Problem_A_2 open file failed:"<<argv[1]<<std::endl;
        return -1;    
    }
    
    std::string lineBuffer;
    //! load GramClassifier GramLanguagers
    GramLanguager* gramLanguager = NULL;
    while(getline(profile, lineBuffer))
    {
        std::vector<std::string> inputs;
        strutil::split(lineBuffer, inputs, " ");
        std::string& doc = inputs[0];
        std::string& profile = inputs[1];
        std::string& language = inputs[2];
        if(inputs.size() != 3)
        {
            std::cout<<"[Warn] Problem_A_2 parse line failed:"<<lineBuffer<<std::endl;
            continue;
        }
        
        //! load languager profile
        gramLanguager = new GramLanguager(language);
        if(!gramLanguager)
        {
            std::cout<<"[Error] Problem_A_2 new GramLanguager failed for no memory."<<std::endl;
            return -1;
        }
        
        if(!gramLanguager->load(profile))
        {
            if(!gramClassifier.train(language, doc, &gramLanguager))
            {
                std::cout<<"[Error] Problem_A_2 new GramLanguager failed for no memory."<<std::endl;
                return -1;
            }
        }
        
        gramClassifier.addLanguager(gramLanguager);
    }
    
    std::ifstream testInputFile;
    testInputFile.open(argv[2]);
    if(!testInputFile.is_open()) 
    {
        std::cout<<"[Error] Problem_A_2 open file failed:"<<argv[2]<<std::endl;
        return -1;    
    }
    
    std::ofstream testOutputFile;
    testOutputFile.open(argv[3]);
    if(!testOutputFile.is_open()) 
    {
        std::cout<<"[Error] Problem_A_2 open file failed:"<<argv[3]<<std::endl;
        return -1;   
    }
    
    while(getline(testInputFile, lineBuffer))
    {
        std::string lang;
        gramClassifier.predict(lineBuffer, lang);
        testOutputFile << lang << std::endl;
    }
    testOutputFile.close();
    testInputFile.close();
    
    return 0;
}


