/**
 * @file  GramHash.cpp
 * @brief Implementation to the class GramHash.
 */
#include "GramFactory.h"
#include "GramHash.h"

/**
    * @brief Hash function for hash string
    * @param key       string start pointer
    * @param len       string length
    * @param size      hash table size
    */
unsigned GramHash::GramHash_Hash(const char *key, size_t len, unsigned size)
{
    unsigned long h = 0;
    unsigned long g;

    /*
     * From the "Dragon" book by Aho, Sethi and Ullman.
     */

    while (len-- > 0) {
	h = (h << 4U) + *(unsigned const char *) key++;
	if ((g = (h & 0xf0000000)) != 0) {
	    h ^= (g >> 24U);
	    h ^= g;
	}
    }
    return (h % size);
}

/**
    * @brief the constructor for the GramHash
    * @param sz      hash table size
    */
GramHash::GramHash(int sz):_size(0),_used(0),_data(0)
{
    resize(sz);
}

/**
    * @brief the destructor for the GramHash
    */
GramHash::~GramHash()
{
    clear();
}

/**
    * @brief the dest GramNode freqence incremntment
    * @param key       GramNode key start pointer
    * @param key_sz    GramNode key length
    */
void       GramHash::freqGram(const char* key, size_t key_sz)
{
    GramNode* node = locate(key, key_sz);
    if(node)
        node->value++;
    else
        insert(key, key_sz, 1);
}

/**
    * @brief insert a new GramNode with the fixed value
    * @param key       GramNode key start pointer
    * @param key_sz    GramNode key length
    * @param value     GramNode fixed value
    */
GramNode*  GramHash::insert(const char* key, size_t key_sz, int value)
{
    GramNode *ht;

    if (_used >= _size) grow();
    
    ht = GramFactory::Instance().create();
    strncpy(ht->key, key, key_sz);
    ht->value = value;
    link(ht);
    return (ht);
}

/**
    * @brief locate&find a dest GramNode with the key
    * @param key       GramNode key start pointer
    * @param key_sz    GramNode key length
    */
GramNode*  GramHash::locate(const char* key, size_t key_sz)
{
    GramNode *ht;

#define	KEY_EQ(x,y,l) (x[0] == y[0] && memcmp(x,y,l) == 0)

    for (ht = _data[GramHash_Hash(key, key_sz, _size)]; ht; ht = ht->next)
        if (key_sz == strlen(ht->key) && KEY_EQ(key, ht->key, key_sz))
            return (ht);
    return (0);
}

/**
    * @brief iterator all GramNodes in the GramHash to the GramHeap object
    * @param gramHeap  a GramHeap object reference
    */
void       GramHash::sortHeap(GramHeap& gramHeap)
{
    GramNode **list;
    GramNode *member;
    int     i;

    for (i = 0; i < _size; i++)
        for (member = _data[i]; member != 0; member = member->next)
            gramHeap.insert(member);
}

/**
    * @brief get GramNode total number in the GramHash
    */
int        GramHash::used()
{
    return _used;
}

/**
    * @brief resize the GramHash size
    * @param size      hash table size to resize
    */
inline void GramHash::resize(int size)
{
    GramNode **h;

    if(size){
        _data = h = (GramNode **) malloc(size * sizeof(GramNode *));
        _size = size;
        _used = 0;
    }

    while (size-- > 0)
	*h++ = 0;
}

/**
    * @brief grow the GramHash size when all slots used up
    */
inline void GramHash::grow()
{
    GramNode *ht;
    GramNode *next;
    unsigned old_size = _size;
    GramNode **h = _data;
    GramNode **old_entries = h;

    resize(2 * old_size);

    while (old_size-- > 0) {
	for (ht = *h++; ht; ht = next) {
	    next = ht->next;
	    link(ht);
	}
    }
    free((char *) old_entries);
}

/**
    * @brief link a new GramNode object to the GramHash
    * @param node      a GramNode object pointer to be linked
    */
inline void GramHash::link(GramNode* node)
{
    GramNode **_h = _data + GramHash_Hash(node->key, strlen(node->key), _size);
    node->next = *_h;
    *_h = node; 
    _used++;
}

/**
    * @brief clear the GramHash's all GramNodes' memory
    */
inline void GramHash::clear()
{
	GramNode *ht;
	GramNode *next;
	GramNode **h = _data;

	while (_size-- > 0) {
	    for (ht = *h++; ht; ht = next) {
		next = ht->next;
                GramFactory::Instance().destroy(ht);
	    }
	}
	free((char *) _data);
	_data = 0;
}
