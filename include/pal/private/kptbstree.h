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
 * @file kptbstree.h                                                       
 * 
 * @brief Binary Search Tree Implementation.
 *
 * @details 
 *
 ****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTBSTTREE_H
#define H_KPTBSTTREE_H


#include "kptlibcollections.h"
#include "kptapi.h"
#include "kptiterator.h"
#include "kpttreebase.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* forward declarations */
typedef struct KPTClassBSTreeT KPTClassBSTreeT;
typedef struct KPTBSTreeT KPTBSTreeT;
typedef struct KPTBSTreeNodeT KPTBSTreeNodeT;


/** BSTree Node */
struct KPTBSTreeNodeT
{
	KPTBSTreeNodeT *left;	/**< left child  */
	KPTBSTreeNodeT *right;	/**< right child */
	KPTBSTreeNodeT *parent;	/**< parent node */
	void *value;			/**< value contained in treenode */
};

/** Structure containing Member functions of BSTree */
struct KPTClassBSTreeT
{
	/* Get tree height */
	size_t		(*GetTreeHeight)(KPTBSTreeT* aHandle);
	/* function to know if tree is empty */
	KPTBoolT	(*IsTreeEmpty)	(KPTBSTreeT* aHandle);
};

/** Structure containing instance members of BSTree Object */
struct KPTBSTreeT
{
	KPTTreeBaseT parent;		/**< base class	*/
	KPTClassBSTreeT *cls;		/**< structure holding member functions of BSTree */	
	KPTBSTreeNodeT	*rootNode;	/**< Root - BSTree Node*/
};

KPTResultT 
KPTBSTreeInit(KPTBSTreeT* aHandle,
              KPTHeapT* aHeap,
              size_t aNodeSize,
              size_t aPreAllocs,
              KPTBoolT aIsUnique);

void KPTClassBSTreeInit(KPTBSTreeT* aHandle);

KPTResultT
KPTBSTreeMake(KPTTreeBaseT *aHandle,
              KPTHeapT* aHeap,
              size_t aNodeSize,
              size_t aPreAllocs,
              KPTBoolT aIsUnique);

void
KPTBSTreeFinalize(KPTBSTreeT *aHandle,
                  KPTNodeDestructionFnT* aDelFn);

KPTIteratorT
KPTBSTTreeGetIterator(KPTBSTreeNodeT* aNode);

KPTConstIteratorT
KPTBSTTreeGetConstIterator(const KPTBSTreeNodeT* aNode);

/* to work with BSTree directly */

KPTIteratorT 
KPTBSTreeInsert(KPTTreeBaseT *aHandle,
                const void* aNode,
                KPTNodeComparisionFnT* aCompareFn,
                KPTTreeGetKeyFnT* aKeyFn,
                KPTNodeConstructionFnT* aConstructFn,
                KPTResultT *aRetStatus);

KPTIteratorT 
KPTBSTreeSearch(KPTTreeBaseT *aHandle,
                const void *aKey,
                KPTNodeComparisionFnT* aCompareFn,
                KPTTreeGetKeyFnT* aKeyFn,
                KPTResultT *aRetStatus);

KPTConstIteratorT 
KPTBSTreeSearchConst(const KPTTreeBaseT *aHandle,
                     const void *aKey,
                     KPTNodeComparisionFnT* aCompareFn,
                     KPTTreeGetKeyFnT* aKeyFn,
                     KPTResultT *aRetStatus);

void 
KPTBSTreeDelete(KPTTreeBaseT *aHandle,
                void *aNode,
                KPTNodeComparisionFnT* aCompareFn,
                KPTTreeGetKeyFnT* aKeyFn,
                KPTNodeDestructionFnT* aDelFn,
                KPTResultT *aRetStatus);

void 
KPTBSTreeClear(KPTTreeBaseT *aHandle,
               KPTNodeDestructionFnT* aDelFn,
               KPTResultT *aRetStatus);

KPTIteratorT
KPTBSTreeGetRoot(KPTTreeBaseT* aHandle);

KPTConstIteratorT
KPTBSTreeGetRootConst(const KPTTreeBaseT* aHandle);

KPTBoolT
KPTBSTreeIsTreeEmpty(const KPTBSTreeT* aHandle);

KPTIteratorT
KPTBSTreeBegin(KPTTreeBaseT *aTree);

KPTConstIteratorT 
KPTBSTreeBeginConst(const KPTTreeBaseT* aTree);

KPTIteratorT 
KPTBSTreeEnd(KPTTreeBaseT* aTree);

KPTConstIteratorT 
KPTBSTreeEndConst(const KPTTreeBaseT* aTree);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif	/*	H_KPTBSTTREE_H	*/
