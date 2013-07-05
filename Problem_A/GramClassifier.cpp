/**
 * @file  GramClassifier.cpp
 * @brief Implementation to the class GramClassifier.
 */

#include "GramClassifier.h"
#include <assert.h>
#include <fstream>
#include <list>
#include <string.h>
#ifdef _DEBUG
#include <iostream>
#endif
GramClassifier::GramClassifier() {
}

GramClassifier::~GramClassifier() {
}

bool GramClassifier::parse(std::string& doc, GramHash& gramHash)
{
    //! parse document to ngrams
    std::ifstream in;
    in.open(doc.c_str());
    if(!in.is_open()) return false;
    
    char c;
    char block[MAX_NGRAM_SZ] = {0};
    int  blen = 0;
    while(in.get(c))
    {
        if(::isspace((int)c) || ::isdigit((int)c)) c = '_';
        
        if(blen < MAX_NGRAM_SZ)
            block[blen++] = c;
        
        if(blen == MAX_NGRAM_SZ)
        {
            gramHash.freqGram(block, 1);
            for(int i = 2; i <= MAX_NGRAM_SZ; i++)
            {
                gramHash.freqGram(block, i);
            }
            for(int i = 1; i < MAX_NGRAM_SZ; i++)
            {
                block[i-1] = block[i];
            }
            blen--;
            block[blen] = '\0';
        }
    }
   
    while(blen)
    {
        gramHash.freqGram(block, 1);
        for(int i = 2; i <= blen; i++)
        {
            gramHash.freqGram(block, i);
        }
        for(int i = 1; i < blen; i++)
        {
            block[i-1] = block[i];
        }
        blen--;
        block[blen] = '\0';
    }
    in.close();
    
    return true;
}

bool GramClassifier::train(std::string& language,
               std::string& doc, 
               GramLanguager** GL)
{
    GramHash gramHash(TABLESIZE);
    if(!parse(doc, gramHash)) return false;
    
    //! sort top 400 by heap
    GramHeap gramHeap(MAX_OUTOFPLACE);
    gramHash.sortHeap(gramHeap);
    
    //! GL malloc
    GramLanguager* gramLanguager = *GL;
    if(gramLanguager == NULL)
    {
        gramLanguager = new GramLanguager(language);
        if(gramLanguager == NULL) return false;
    }
    
    //! sorted ngram to the GramLanguager
    int total = gramHeap.used();
    std::list<GramNode*> lst;
    GramNode* node;
    while((node = gramHeap.pop()))
    {
        gramLanguager->addRanker(node->key, strlen(node->key), total--);
    }
 
    return true;
}

bool GramClassifier::train(std::string& language,
               std::string& doc, 
               std::string& profile)
{
    GramHash gramHash(TABLESIZE);
    if(!parse(doc, gramHash)) return false;
    
    //! sort top 400 by heap
    GramHeap gramHeap(MAX_OUTOFPLACE);
    gramHash.sortHeap(gramHeap);

    //! write sorted ngram to the profile
    std::list<GramNode*> lst;
    GramNode* gram;
    while((gram = gramHeap.pop()))
    {
        lst.push_front(gram);
    }
 
    std::ofstream out;
    out.open(profile.c_str());
    if(!out.is_open()) return false;
    
    for(std::list<GramNode*>::iterator it = lst.begin(); 
        it != lst.end();
        it++)
    {
        out<<(*it)->key<<" "<<(*it)->value<<std::endl;
    }    
    out.close();
    
    return true;
}

void GramClassifier::addLanguager(GramLanguager* GL)
{
    assert(GL);
    this->_gramLanguagers.insert(std::make_pair(GL->language(), GL));
}

bool GramClassifier::predict(std::string& unknown, std::string& language)
{
    language = "unknown";
    if(this->_gramLanguagers.empty()) return false;
    
    int minDistance = MAXSCORE;
#ifdef _DEBUG    
    std::cout<<"predict:"<<unknown<<std::endl;
#endif
    std::map<std::string, GramLanguager*>::iterator it;
    for(it = _gramLanguagers.begin(); it != _gramLanguagers.end(); it++)
    {
        int d = it->second->distance(unknown);
#ifdef _DEBUG
        std::cout<<it->first<<" distance:"<<d<<std::endl;
#endif
        if(d < minDistance)
        {
            minDistance = d;
            language = it->first;
        }
    }
    
    return true;
}