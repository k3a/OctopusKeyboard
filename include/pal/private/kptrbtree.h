/******************************************************************************
 *
 * Copyright 2011 KeyPoint Technologies (UK) Ltd.   
 * All rights reserved. This program and the accompanying materials   
 * are made available under the terms of the Eclipse Public License v1.0  
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html

 *           
 * Contributors: 
 * KeyPoint Technologies (UK) Ltd - Initial API and implementation
 *
 *****************************************************************************/
 /** 
 *
 * @file kptrbtree.h                 
 * 
 * @brief Red Black Tree Implementation.
 *
 * @details 
 *
 ****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTRBTREE_H
#define H_KPTRBTREE_H


#include "kptlibcollections.h"
#include "kptapi.h"
#include "kptiterator.h"
#include "kpttreebase.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/** Tree color */
enum KPTRBColorT
{
	eRed = 0,		/**< Red color */
	eBlack = 1     /**< Black color*/
};
typedef enum KPTRBColorT KPTRBColorT;


/* Structures for RedBlack Tree Object */
typedef struct KPTClassRBTreeT KPTClassRBTreeT;
typedef struct KPTRBTreeT KPTRBTreeT;

/** RedBlack Tree Node */
typedef struct KPTRBTreeNodeT KPTRBTreeNodeT;
struct KPTRBTreeNodeT
{
	KPTRBColorT color;		/**< color of Node */	
	KPTRBTreeNodeT *left;	/**< left child */
	KPTRBTreeNodeT *right;	/**< right child */
	KPTRBTreeNodeT *parent;	/**< parent node */
	void *value;			 /**< value contained in treenode */
};

/** Structure containing Member functions of RBTree */
struct KPTClassRBTreeT
{
    /* Get tree height */
    size_t		(*GetTreeHeight)(KPTRBTreeT* aHandle);

    /* function to know if tree is empty */
    KPTBoolT	(*IsTreeEmpty)	(KPTRBTreeT* aHandle);
};

/** Structure containing instance members of RBTree Object */
struct KPTRBTreeT
{
    KPTTreeBaseT parent;	/**< base class	*/
    KPTClassRBTreeT *cls;	/**< structure holding member functions of RBTree */
    KPTRBTreeNodeT	*rootNode;	/**< Root - RBTree Node*/
};

KPTResultT 
KPTRBTreeInit(KPTRBTreeT *aHandle,
              KPTHeapT* aHeap,
              size_t aNodeSize,
              size_t aPreAllocs,
              KPTBoolT aIsUnique);

void 
KPTClassRBTreeInit(KPTRBTreeT *aHandle);

void	
KPTRBTreeFinalize(KPTRBTreeT	*aHandle,KPTNodeDestructionFnT	aDelFn);

KPTResultT
KPTRBTreeMake(KPTTreeBaseT *aHandle,
              KPTHeapT* aHeap,
              size_t aNodeSize,
              size_t aPreAllocs,
              KPTBoolT aIsUnique);

KPTIteratorT 
KPTRBTTreeGetIterator(KPTRBTreeNodeT *aNode);

KPTConstIteratorT
KPTRBTTreeGetConstIterator(const KPTRBTreeNodeT *aNode);

/* to work with RBTree directly */

KPTIteratorT 
KPTRBTreeInsert(KPTTreeBaseT *aHandle,
                const void *aNode,
                KPTNodeComparisionFnT* aCompareFn,
                KPTTreeGetKeyFnT* aKeyFn,
                KPTNodeConstructionFnT* aConstructFn,
                KPTResultT *aRetStatus);

KPTIteratorT 
KPTRBTreeSearch(KPTTreeBaseT *aHandle,
                const void *aKey,
                KPTNodeComparisionFnT* aCompareFn,
                KPTTreeGetKeyFnT* aKeyFn,
                KPTResultT *aRetStatus);
void 
KPTRBTreeDelete(KPTTreeBaseT *aHandle,
                void *aNode,
                KPTNodeComparisionFnT* aCompareFn,
                KPTTreeGetKeyFnT* aKeyFn,
                KPTNodeDestructionFnT* aDelFn,
                KPTResultT *aRetStatus);

void 
KPTRBTreeClear( KPTTreeBaseT *aHandle,
               KPTNodeDestructionFnT* aDelFn,
               KPTResultT *aRetStatus);

KPTIteratorT 
KPTRBTreeGetRoot(KPTTreeBaseT *aHandle);

KPTConstIteratorT
KPTRBTreeGetRootConst(const KPTTreeBaseT *aHandle);

KPTBoolT	
KPTRBTreeIsTreeEmpty(const KPTRBTreeT *aHandle);

KPTIteratorT 
KPTRBTreeBegin(KPTTreeBaseT *aTree);

KPTConstIteratorT
KPTRBTreeBeginConst(const KPTTreeBaseT *aTree);

KPTIteratorT 
KPTRBTreeEnd(KPTTreeBaseT *aTree);

KPTConstIteratorT 
KPTRBTreeEndConst(const KPTTreeBaseT *aTree);


#ifdef __cplusplus
}
#endif /*__cplusplus */



#endif	/*	H_KPTRBTREE_H	*/
