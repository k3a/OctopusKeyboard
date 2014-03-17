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
 * @file    kptiterator.h
 *
 * @brief   Provides a common interface for iterator functionality for all the collection containers
 *
 * @details 
 *  
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPT_ITERATOR_H
#define H_KPT_ITERATOR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum KPTCollectionsTypeT
{
	eKPTByVal = 0,   /**< false */
	eKPTByRef = 1     /**< true */
};

typedef enum KPTCollectionsTypeT KPTCollectionsTypeT;

/** Tree Options  */
enum KPTTreeOptionsT
{
    eKPTTreeMulti  = KPTBIT(0),		  /**< Create a non-unique tree if supported */
    eKPTTreeRBTree = KPTBIT(1),		  /**< Use a RBT if supported */
    eKPTTreeBSTree = KPTBIT(2),		  /**< Use a BST if supported */
};
typedef enum KPTTreeOptionsT KPTTreeOptionsT;



/* values stored in tree */
typedef void KPTTreeValueT;

/* Tree Node destruction function */
typedef void (KPT_CALLB KPTNodeDestructionFnT)(KPTHeapT* aHeap, KPTTreeValueT* aNode);

/* Tree Nodes comparision function */
typedef int (KPT_CALLB KPTNodeComparisionFnT)(const KPTTreeValueT* aLeftNode, const KPTTreeValueT* aRightNode);

/* Tree Node construction function */
typedef	KPTResultT (KPT_CALLB KPTNodeConstructionFnT)(KPTHeapT* aHeap,
                                                       KPTTreeValueT* aTarget,
                                                       const KPTTreeValueT* aSource);

/** Increments the passed iterator  */
#define KPTITER_INC(iter)                  (iter).iterFnPtr->IncIterator(&iter)
/** Increments the passed iterator by passed value*/
#define KPTITER_INC_N(iter,n)              (iter).iterFnPtr->IncIteratorN(&iter,n)
/** Decrements the passed iterator */
#define KPTITER_DEC(iter)                  (iter).iterFnPtr->DecIterator(&iter)
/** Decrements the passed iterator by passed value*/
#define KPTITER_DEC_N(iter,n)              (iter).iterFnPtr->DecIteratorN(&iter,n)
/** Returns the value pointed by the iterator */
#define KPTITER_REF(iter)                  (iter).iterFnPtr->RefIterator(&(iter))
/** Checks if the passed iterators are equal */
#define KPTITER_ISEQUAL(iterL,iterR)       (iterL).iterFnPtr->IsEqual(&(iterL),&(iterR))
/** Swaps the position of the two elements refrenced by iterators */
#define KPTITER_SWAP(iterL,iterR)          (iterL).iterFnPtr->Swap(&(iterL), &(iterR))

/** Construction Function for vector */
typedef void (KPT_CALLB KPTConstructionFnT)(KPTHeapT* aHeap,void* aTarget,const void* aSource);
/** Node Comparison Function for vectors & Lists */
typedef int (KPT_CALLB KPTElementComparerFnT) (const void* aLeftVal, const void* aRightVal); 
/** Node Destruction Function for vectors & Lists */
typedef void (KPT_CALLB KPTElementDestFnT) (KPTHeapT* aHeap,void* aValToDestroy);

/* 
 * Read/Write Iterator
 */

/** Typedef for Iterator Structure */
typedef struct KPTIteratorT KPTIteratorT;

/** Iterator Function Pointer Structure */
typedef struct KPTIteratorFnPtrT KPTIteratorFnPtrT;
struct KPTIteratorFnPtrT
{
    void* (KPT_CALLB *RefIterator) (KPTIteratorT* aIterator);
	KPTResultT (KPT_CALLB *Swap) (KPTIteratorT* aLeft, KPTIteratorT* aRight);
    void (KPT_CALLB *IncIterator) (KPTIteratorT* aIterator);
    void (KPT_CALLB *IncIteratorN) (KPTIteratorT* aIterator, size_t n);
    void (KPT_CALLB *DecIterator) (KPTIteratorT* aIterator);
    void (KPT_CALLB *DecIteratorN) (KPTIteratorT* aIterator, size_t n);
    KPTBoolT (KPT_CALLB *IsEqual) (const KPTIteratorT* aIterator, const KPTIteratorT* aValue);
};

/** Iterator Structure */
struct KPTIteratorT
{
	void* elementNode;
	void* handle;
	KPTIteratorFnPtrT* iterFnPtr;
};

/* 
 * const iterator
 */

/** Forward declaration of const iterator */
typedef struct KPTConstIteratorT KPTConstIteratorT;

/** Const Iterator Function Pointer Structure */
typedef struct KPTConstIteratorFnPtrT KPTConstIteratorFnPtrT;
struct KPTConstIteratorFnPtrT
{
	/** Function to return a reference to the element */
	const void* (KPT_CALLB *RefIterator) (KPTConstIteratorT* aIterator);
	/** Function to move forward one element */
	void (KPT_CALLB *IncIterator) (KPTConstIteratorT* aIterator);
	/** Function to move forward N elements */
	void (KPT_CALLB *IncIteratorN) (KPTConstIteratorT* aIterator,size_t n);
	/** Function to move backward one element */
	void (KPT_CALLB *DecIterator) (KPTConstIteratorT* aIterator);
	/** Function to move backward N elements */
	void (KPT_CALLB *DecIteratorN) (KPTConstIteratorT* aIterator, size_t n);
	/** Function to check if two iterators are equal */
	KPTBoolT (KPT_CALLB *IsEqual) (const KPTConstIteratorT* aIterator, const KPTConstIteratorT* aValue);
};

/** Const Iterator Structure */
struct KPTConstIteratorT
{
	const void* elementNode;
	const void* handle;
	const KPTConstIteratorFnPtrT* iterFnPtr;
};

#ifdef __cplusplus
}
#endif /*__cplusplus */
#endif /* H_KPT_ITERATOR_H */
