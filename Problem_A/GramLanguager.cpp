/**
 * @file  GramLanguager.cpp
 * @brief Implementation to the class GramLanguager.
 */


#include "GramLanguager.h"
#include <math.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>

#ifdef _DEBUG
#include <iostream>
#endif

GramLanguager::GramLanguager(std::string& lang)
        :_lang(lang),_gramRanker(MAX_OUTOFPLACE)
{}
GramLanguager::~GramLanguager()
{}

std::string& GramLanguager::language()
{
    return _lang;
}

bool GramLanguager::load(std::string& filePath)
{
    std::ifstream inFile;
    inFile.open(filePath.c_str());
    if (!inFile.is_open())
        return false;

    std::string lineBuffer;
    int rank = 0;
    while (getline(inFile, lineBuffer))
    {
        size_t pos = lineBuffer.find(' ');
        if(pos == std::string::npos) 
            continue;
        
        _gramRanker.insert(lineBuffer.substr(0, pos).c_str(), pos, rank);
        rank++;
    }
    return true;
}

void GramLanguager::addRanker(const char* key, int sz, int rank)
{
    _gramRanker.insert(key, sz, rank);
}

int  GramLanguager::distance(std::string& unknown)
{
    GramHash gramHash(1024);
    const char* p = unknown.c_str();
    size_t size = unknown.length(); 
            
    char n[MAX_NGRAM_SZ+1] = {0};	
    char c;
    int len = 0;
    
    while(size)
    {
        c = *p++;size--;
        if(::isspace((int)c) || ::isdigit((int)c)) c = '_';
        
        if(len < MAX_NGRAM_SZ)
            n[len++] = c;
        
        if(len == MAX_NGRAM_SZ)
        {
            gramHash.freqGram(n, 1);
            for(int i = 2; i <= MAX_NGRAM_SZ; i++)
            {
                gramHash.freqGram(n, i);
            }
            for(int i = 1; i < MAX_NGRAM_SZ; i++)
            {
                n[i-1] = n[i];
            }
            len--;
            n[len] = '\0';
        }
    }
   
    while(len)
    {
        gramHash.freqGram(n, 1);
        for(int j = 2; j <= len; j++)
        {
            gramHash.freqGram(n, j);
        }
        for(int j = 1; j < len; j++)
        {
            n[j-1] = n[j];
        }
        len--;
        n[len] = '\0';
    }

    GramHeap gramHeap(MAX_OUTOFPLACE);
    gramHash.sortHeap(gramHeap);
    
    int total = gramHeap.used();
#ifdef _DEBUG
    std::cout<<"unknow heap used:"<<total<<std::endl;
#endif
    int r = 0;
    int k = 0;
    GramNode* node;
    while((node = gramHeap.pop()))
    {
        r += distance(node->key, strlen(node->key), total - k);
#ifdef _DEBUG
        std::cout<<"key:"<<node->key<<" rank:"<<total - k <<" distance:"<<r<<std::endl;
#endif
        k++;
    }
        
    return r;
}

int  GramLanguager::distance(const char* key, int sz, int rank)
{
    int d = MAX_OUTOFPLACE;
    GramNode* g = _gramRanker.locate(key, sz);
    if(g) d = abs(g->value - rank);
    
    return d;
}