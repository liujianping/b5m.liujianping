/**
 * @file  GramDefs.h
 * @brief Definitions of the NGram.
 */

#ifndef GRAMDEFS_H
#define	GRAMDEFS_H

#include <limits.h>
#include <stddef.h>
#include <iostream>
#include <assert.h>
#include <string.h>

//! max ngram node size
const int MAX_NGRAM_SZ = 5;

//! max slots for store the ngram nodes
const int MAX_OUTOFPLACE = 400;

#define TABLEPOW   13
//! gram hash table size
#define TABLESIZE  (1<<TABLEPOW)

//! max score of the ngrams' distance
#define MAXSCORE  INT_MAX

/** @brief GramNode type definition. */
typedef struct GramNode_s {
    char    key[MAX_NGRAM_SZ + 1];      ///< NGRAM key 
    int     value;			///< associated value 
    struct GramNode_s *next;		///< colliding entry 
}GramNode;


#endif	/* GRAMDEFS_H */

