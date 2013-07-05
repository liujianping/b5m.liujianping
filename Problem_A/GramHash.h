/**
 * @file  GramHash.h
 * @brief Definition of the class GramHash. 
 */

#ifndef GRAMHASH_H
#define	GRAMHASH_H

#include "GramDefs.h"
#include "GramHeap.h"

/**
 * class GramHash
 * @brief A data structure for GramNode insert&find by hashtable.
 */
class GramHash {
public:
    /**
     * @brief Hash function for hash string
     * @param key       string start pointer
     * @param len       string length
     * @param size      hash table size
     */
    static unsigned GramHash_Hash(const char *key, size_t len, unsigned size);
public:
    /**
     * @brief the constructor for the GramHash
     * @param sz      hash table size
     */
    GramHash(int sz);
    
    /**
     * @brief the destructor for the GramHash
     */
    virtual ~GramHash();
    
    /**
     * @brief the dest GramNode freqence incremntment
     * @param key       GramNode key start pointer
     * @param key_sz    GramNode key length
     */
    void       freqGram(const char* key, size_t key_sz);
    
    /**
     * @brief insert a new GramNode with the fixed value
     * @param key       GramNode key start pointer
     * @param key_sz    GramNode key length
     * @param value     GramNode fixed value
     */
    GramNode*  insert(const char* key, size_t key_sz, int value);
    
    /**
     * @brief locate&find a dest GramNode with the key
     * @param key       GramNode key start pointer
     * @param key_sz    GramNode key length
     */
    GramNode*  locate(const char* key, size_t key_sz);
    
    /**
     * @brief iterator all GramNodes in the GramHash to the GramHeap object
     * @param gramHeap  a GramHeap object reference
     */
    void       sortHeap(GramHeap& gramHeap);
    
    /**
     * @brief get GramNode total number in the GramHash
     */
    int        used();
protected:
    /**
     * @brief resize the GramHash size
     * @param size      hash table size to resize
     */
    inline void resize(int size);
    
    /**
     * @brief grow the GramHash size when all slots used up
     */
    inline void grow();
    
    /**
     * @brief link a new GramNode object to the GramHash
     * @param node      a GramNode object pointer to be linked
     */
    inline void link(GramNode* node);
    
    /**
     * @brief clear the GramHash's all GramNodes' memory
     */
    inline void clear();
private:
    GramHash(const GramHash& orig);
    GramHash operator=(const GramHash& orig);
    
private:
    int         _size;			/** length of entries array */
    int         _used;			/** number of entries in table */
    GramNode  **_data;                  /** entries array, auto-resized */
};


#endif	/* GRAMHASH_H */

