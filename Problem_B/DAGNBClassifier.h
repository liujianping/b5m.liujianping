/**
 * @file  DAGNBClassifier.h
 * @brief Definition of the class DAGNBClassifier.
 */

#ifndef DAGNBCLASSIFIER_H
#define	DAGNBCLASSIFIER_H

#include "NBClassifier.h"

/**
 * class DAGNBClassifier
 * @brief A DAG classifier based on Naive Bayes for multi-classificaton problem.
 */
class DAGNBClassifier {
public:
    /**
     * @brief the constructor for the DAGNBClassifier
     */
    DAGNBClassifier();
    
    /**
     * @brief the destructor for the DAGNBClassifier
     */
    virtual ~DAGNBClassifier();
    
    /**
     * @brief set the DAGNBClassifier training DocSet
     * @param docSet training DocSet object reference
     */
    void setTrain(DocSet& docSet);
    
    /**
     * @brief the constructor for the DAGNBClassifier
     * @param docVector DocVector object to be predict
     */
    ClassID predict(const DocVector& docVector);
private:
    DAGNBClassifier(const DAGNBClassifier& orig);
    DAGNBClassifier& operator=(const DAGNBClassifier& orig);
private:
    /** training DocSet*/
    DocSet _trainDocSet;
    /** the map storing the NBClassifier used*/
    std::map<std::pair<ClassID, ClassID>, NBClassifier*> _nbClassifiers;
};

#endif	/* DAGNBCLASSIFIER_H */

