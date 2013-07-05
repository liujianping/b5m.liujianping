/**
 * @file  GramLanguager.h
 * @brief Definition of the class GramLanguager.
 */

#ifndef GRAMLANGUAGER_H
#define	GRAMLANGUAGER_H

#include <string>

#include "GramDefs.h"
#include "GramHash.h"

/**
 * class GramLanguager
 * @brief A NGram luanguager distant accumulator for a dest language.
 */
class GramLanguager{
public:
    /**
    * @brief The constructor of GramLanguager
    * @param lang       a language description
    */
    GramLanguager(std::string& lang);

    /**
    * @brief The destructor of GramLanguager
    */
    virtual ~GramLanguager();
    
    /**
    * @brief load GramLanguager from a trained language profile
    * @param filePath   the trained language profile path
    */
    bool load(std::string& filePath);
    
    /**
    * @brief add a new ngram ranker node to the GramLanguager
    * @param key        new ngram key start pointer
    * @param sz         new ngram key length
    * @param rank       new ngram rank value 
    * 
    */
    void addRanker(const char* key, int sz, int rank);
    
    /**
    * @brief get the GramLanguager's language description
    */
    std::string& language();
    
    /**
    * @brief caculate distance of the unknown string compair by the GramLanguager
    * @param unknown        an unknown language string
    */
    int  distance(std::string& unknown);
    
    /**
    * @brief caculate distance of the test ngram element compair by the GramLanguager
    * @param key        a test ngram key
    * @param sz         a test ngram key length
    * @param rank       a test ngram rank value
    */
    int  distance(const char* key, int sz, int rank);
private:
    std::string _lang;/** language description */
    GramHash    _gramRanker;/** language rankers hashtable */
};

#endif	/* GRAMLANGUAGER_H */

