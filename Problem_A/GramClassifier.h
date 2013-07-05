/**
 * @file  GramClassifier.h
 * @brief Definition of the class DocSet.
 */

#ifndef GRAMCLASSIFIER_H
#define	GRAMCLASSIFIER_H
#include <string>
#include <map>
#include "GramHash.h"
#include "GramLanguager.h"

/**
 * class GramClassifier
 * @brief A NGram classifier for a language-classificaton problem.
 */
class GramClassifier {
public:
    /**
     * @brief The constructor of GramClassifier
     */
    GramClassifier();
    
    /**
     * @brief The destructor of GramClassifier
     */
    virtual ~GramClassifier();
    
    /**
     * @brief train the dest language document, write the trained results into profile
     * @param language  dest document language type
     * @param doc       file path to be trained document
     * @param profile   file path to be write the trained results
     */
    bool train(std::string& language,
               std::string& doc, 
               std::string& profile);
    
    /**
     * @brief train the dest language document, write the trained results into GramLanguager object.
     * @param language  dest document language type
     * @param doc       file path to be trained document
     * @param GL        GramLanguager object pointer to be write the trained results
     */
    bool train(std::string& language,
               std::string& doc, 
               GramLanguager** GL);
    
    /**
     * @brief add a GramLanguager to the GramClassifier
     * @param GL        a GramLanguager object pointer
     */
    void addLanguager(GramLanguager* GL);
    
    /**
     * @brief predict an unknown line belong to right language type
     * @param unknown   an unknown line string
     * @param language  an string reference to be store the predict language
     */
    bool predict(std::string& unknown, std::string& language);
protected:
    /**
     * @brief parse the dest document to GramHash object
     * @param doc       file path to be parsed
     * @param GH        GramHash object reference to store the GramNode's Frequence
     */
    bool parse(std::string& doc, GramHash& GH);
private:
    GramClassifier(const GramClassifier& orig);
    GramClassifier& operator=(const GramClassifier& orig);

private:
    /** the map object to store the GramLanguager objects */
    std::map<std::string, GramLanguager*> _gramLanguagers;
};

#endif	/* GRAMCLASSIFIER_H */

