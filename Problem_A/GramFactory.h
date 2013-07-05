/**
 * @file  GramFactory.h
 * @brief Definition & Implemention of the class GramFactory. The Factory product only GramNode
 *        object
 */

#ifndef GRAMFACTORY_H
#define	GRAMFACTORY_H

#include <assert.h>
#include <stdlib.h>
#include "GramDefs.h"
/**
 * class GramFactory
 * @brief A GramNode Factory.
 */
class GramFactory{
public:
    /**
     * @brief static method for creating a Gloable GramFactory object
     */
    static void createFactory();
    /**
     * @brief static method for getting the Gloable GramFactory object reference
     */
    static GramFactory& Instance();
    /**
     * @brief static method for destroying the Gloable GramFactory object
     */
    static void destroyFactory();
public:
    /**
     * @brief create a new GramNode object
     */
    inline GramNode* create();
    
    /**
     * @brief destroy a old GramNode object
     * @param data      a GramNode object pointer to be released
     */
    inline void  destroy (GramNode* data);
private:
    /**
     * @brief The constructor of GramFactory
     */
    GramFactory();
    
    /**
     * @brief The destructor of GramFactory
     */
    virtual ~GramFactory();
    
    /**
     * @brief prealloc dest size GramNode objects
     * @param sz        prealloc objects size
     */
    void grow(int sz = GROW_SIZE);
private:
    /** freelist storing all free GramNode objects. */
    GramNode* _freelist;
    
    enum {
        GROW_SIZE = 32/** prealloc default size */
    };
    
    /** Gloable GramFactory object pointer*/
    static GramFactory* _instance;
};

GramFactory* GramFactory::_instance = NULL;

void GramFactory::createFactory()
{
    if(!_instance) _instance = new GramFactory();
}

GramFactory& GramFactory::Instance()
{
    createFactory();
    assert(_instance);
    return *_instance;
}
void GramFactory::destroyFactory()
{
    if(_instance) delete _instance;
    _instance = NULL;
}

GramFactory::GramFactory():_freelist(0)
{}

GramFactory::~GramFactory()
{
   GramNode* p = _freelist;
   for(p = _freelist; p != 0; p= _freelist)
   {
       _freelist = _freelist->next;
       free(p);
   }
}

GramNode* GramFactory::create()
{
    if(!_freelist) grow(GROW_SIZE);
    GramNode* head = _freelist;
    memset(head->key, 0, MAX_NGRAM_SZ + 1);
    _freelist = head->next;
    return head;
}

void GramFactory::destroy(GramNode* data)
{
    if(data)
    {
        data->next = _freelist;
        _freelist = data;
    }
}

void GramFactory::grow(int sz)
{
    GramNode* tail = (GramNode*)malloc(sizeof(GramNode));
    assert(tail);
    _freelist = tail;
    for(int i = 0; i < sz; i++)
    {
        tail->next = (GramNode*)malloc(sizeof(GramNode));
        assert(tail->next);
        tail = tail->next;
    }
    tail->next = 0;
}

#endif	/* GRAMFACTORY_H */

