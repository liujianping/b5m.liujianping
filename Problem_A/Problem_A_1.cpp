/**
 * @file  Problem_A_1.cpp
 * @brief Problem_A_1 main implemention
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

#include "GramClassifier.h"
#include "strutil.h"
/*
 * Usage: Problem_A_1 <configure>
 */
int main(int argc, char** argv) {

    if(argc != 2)
    {
        std::cout<<"[Error] Usage: Problem_A_1 <configurePath>"<<std::endl;
        return -1;
    }
    
    GramClassifier gramClassifier;
    
    std::ifstream in;
    in.open(argv[1]);
    if(!in.is_open()) 
    {
        std::cout<<"[Error] Problem_A_1 open file failed:"<<argv[1]<<std::endl;
        return -1;    
    }
    
    std::string lineBuffer;
    int count = 0;
    while(getline(in, lineBuffer))
    {
        std::vector<std::string> inputs;
        strutil::split(lineBuffer, inputs, " ");
        if(inputs.size() != 3)
        {
            std::cout<<"[Warn] Problem_A_1 parse line failed:"<<lineBuffer<<std::endl;
            continue;
        }
        
        if(!gramClassifier.train(inputs[2], inputs[0], inputs[1]))
        {
            std::cout<<"[Warn] Problem_A_1 train line failed:"<<lineBuffer<<std::endl;
            continue;
        }
        count++;
    }
    
    std::cout<<"[Info] Problem_A_1 succeed trained:"<< count<<std::endl;
    return 0;
}

