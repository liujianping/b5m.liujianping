/**
 * @file  GramHeap.h
 * @brief Definition of the class GramHeap. 
 */

#ifndef GRAMHEAP_H
#define	GRAMHEAP_H

#include "GramDefs.h"

/**
 * class GramHeap
 * @brief A data structure for GramNode sorting by heap.
 */
class GramHeap {
public:
    /**
     * @brief the constructor for the GramHeap
     * @param size      GramNode Heap limit size
     */
    GramHeap(int size);
    
    /**
     * @brief the destructor for the GramHeap
     */
    virtual ~GramHeap();
    
    /**
     * @brief insert a GramNode to the GramHeap
     * @param node      pointer the GramNode
     */
    void   insert(GramNode* node);
    
    /**
     * @brief pop a GramNode from the GramHeap
     */
    GramNode* pop();
    
    /**
     * @brief GramNodes Compair method
     * @param node1     the left GramNode to be compair
     * @param node2     the right GramNode to be compair
     */
    int    gramNodeCmp(GramNode* node1,GramNode* node2);
    
    /**
     * @brief get GramNode total number of the GramHeap 
     */
    int    used();
protected:
    /**
     * @brief resize the GramHeap size
     * @param size      GramHeap size to resize
     */
    void   resize(int size);
    
    /**
     * @brief clear the GramHeap alloc memory, but not the GramNode memory
     */
    void   clear();
    
    /**
     * @brief Heap element adjust from position to the root
     * @param pos      the position adjustment up start
     */
    void   heapUp(int pos);
    
    /**
     * @brief Heap element adjust from position to the leaf
     * @param pos      the position adjustment down start
     */
    void   heapDown(int pos);
private:
    int        _size;/** length of entries array */
    int        _used;/** number of entries in heap used */
    GramNode** _data;/** entries array, auto-resized */
};

#endif	/* GRAMHEAP_H */

