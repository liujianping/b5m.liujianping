/**
 * @file  DAGNBClassifier.cpp
 * @brief Implementation to the class DAGNBClassifier.
 */


#include "DAGNBClassifier.h"
#include <assert.h>

DAGNBClassifier::DAGNBClassifier() {
}

DAGNBClassifier::DAGNBClassifier(const DAGNBClassifier& orig) {
}

DAGNBClassifier::~DAGNBClassifier() {
}

void DAGNBClassifier::setTrain(DocSet& docSet)
{
    _trainDocSet = docSet;
}

ClassID DAGNBClassifier::predict(const DocVector& docVector)
{
    std::set<ClassID> classIDs = _trainDocSet.getAllClasses();
    assert(classIDs.size() >= 2);
    
    
    std::map<std::pair<ClassID, ClassID>, NBClassifier* >::iterator itNB;
    
    NBClassifier* nbClassifier = NULL;
    
    ClassID startClassID = *classIDs.begin();
    std::set<ClassID>::iterator it = classIDs.begin()++;
    for(;it != classIDs.end(); it++)
    {
        itNB = _nbClassifiers.find(std::make_pair(startClassID, *it)); 
        if(itNB != _nbClassifiers.end())
        {
            nbClassifier = itNB->second;
        }
        else
        {
            nbClassifier = new NBClassifier(startClassID, *it);
            assert(nbClassifier);
            nbClassifier->train(_trainDocSet);
            _nbClassifiers.insert(std::make_pair(
                                  std::make_pair(startClassID, *it),
                                  nbClassifier));
        }
        
        startClassID = nbClassifier->predict(docVector);
    }
    
    return startClassID;
}
