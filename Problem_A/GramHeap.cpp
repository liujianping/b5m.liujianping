/**
 * @file  GramHeap.cpp
 * @brief Implementation to the class GramHeap.
 */

#include "GramHeap.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
/*---------- GramHeap Implemention Begin -----------------*/

GramHeap::GramHeap(int size)
        :_size(0), _used(0)
{
    resize(size);
}

GramHeap::~GramHeap()
{
    clear();
}

void   GramHeap::resize(int size)
{
    GramNode **h;

    if(size)
    {    
        _data = h = (GramNode **) malloc(size * sizeof(GramNode *));
        _size = size;
        _used = 0;
    }    
    while (size-- > 0)
	*h++ = 0;
}
void   GramHeap::clear()
{
    free(_data);
    _size = 0;
    _used = 0;
}

int    GramHeap::gramNodeCmp(GramNode* node1,GramNode* node2)
{
    return ((node1->value - node2->value) != 0) ? (node1->value - node2->value) : 
           -strcmp(node1->key, node2->key);
}

void   GramHeap::heapUp(int child)
{
    int parent = (child - 1)/2;
    
    while ( child > 0 ) {
        if (gramNodeCmp(_data[parent], _data[child]) <= 0) 
            break;

        GramNode* t = _data[child];
        _data[child] =  _data[parent];
        _data[parent] = t;
        
        child = parent;
        parent = (child - 1)/2;
    }
}

void   GramHeap::heapDown(int parent)
{
    int child = 2*parent + 1;
    while(child < _used)
    {
        if((child + 1 < _used) && 
           gramNodeCmp(_data[child], _data[child + 1]) > 0)
            child++;
        
        if(gramNodeCmp(_data[parent], _data[child]) <= 0)
            break;
        
        GramNode* t = _data[child];
        _data[child] = _data[parent];
        _data[parent] = t;
        
        parent = child;
        child = 2*parent + 1;
    }
}

void   GramHeap::insert(GramNode* node)
{
    
    if(_used < _size)
    {    
        _data[_used] = node;
        heapUp(_used);
        _used++;
        return;
    }
    
    if(gramNodeCmp(node, _data[0]) < 0) return;

    //! just abandom older _data[0]
    _data[0] = node;
    heapDown(0);
}

GramNode* GramHeap::pop()
{
    if(_used == 0) return NULL;
    GramNode* r = _data[0];
    
    _data[0] = _data[_used - 1];
    _used--;
    heapDown(0);
    return r;
}

int GramHeap::used()
{
    return _used;
}
/*---------- GramHeap Implemention End -----------------*/