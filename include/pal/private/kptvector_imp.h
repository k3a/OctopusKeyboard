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
 * @file kptvector_imp.h
 * 
 * @brief Private implementationd etails for the vector container.
 *
 * @details 
 *
 ****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPT_VECTOR_IMP_H
#define H_KPT_VECTOR_IMP_H

#include "kptheap.h"
#include "kptiterator.h"
#include "kptvector.h"

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus */

/** 
 * Private implementation of KPTVector 
 */
struct KPTVectorT
{
	KPTHeapT* heap;                     /** The heap used to allocate memory for the buffer */
	KPTElementComparerFnT* elemComparer;/** The comparision fn to beused for sorting */
	KPTElementDestFnT* elemDest;        /** Destructor to be called for freeing resources */
	KPTConstructionFnT* constFuncPtr;   /** Copy function to be called for performing deep copy */
	size_t maxSize;                     /** Maximum Size of the vector */
	size_t vectorGrowSize;              /** Grow Size of the vector */
	size_t vectorSize;					/** size of vector till current insertion point */
	size_t valSize;                     /** Size of the each value in the vector */
	void** start;                       /** Pointer to the starting node of the vector */
	void** finish;                      /** Pointer to the last node of the vector */
	void** endOfStorage;                /** Pointer to the last reserved node of the vector */
	KPTCollectionsTypeT valType;        /** Type of the vector (by value or by reference) */
	KPTBoolT isSorted;                  /** Stores whether the vector is sorted or not */
	KPTBoolT isUnique;                  /** Stores whether the vector should enforce uniqueness or not */
};

void KPTVectorGetIterator(KPTVectorT* aVector, 
                          void* aIterNode, 
                          KPTIteratorT* aIterator);

void KPTVectorGetIteratorAt(KPTVectorT* aVector, 
                            size_t aIndex,
                            KPTIteratorT* aIterator);

void KPTVectorGetConstIterator(const KPTVectorT* aVector,
                               const void* aIterNode,
                               KPTConstIteratorT* aIterator);

void KPTVectorGetConstIteratorAt(const KPTVectorT* aVector,
                                 size_t aIndex,
                                 KPTConstIteratorT* aIterator);

/**
 * Returns the value stored at the given position.
 * for internal use 
 * @param [in] aHandle		Pointer to the vector
 * @param [in] aPos			The pos to get the value from.
 * @return					void*
 */
static KPTINLINE_FORCE
void* vectorAt(KPTVectorT* aHandle,
               size_t aPos)
{
	return KPTBytePointerOffset(aHandle->start, aHandle->valSize * aPos);
}

/**
 * Returns the value stored at the given position.
 * for internal use 
 * @param [in] aHandle		Pointer to the vector
 * @param [in] aPos			The pos to get the value from.
 * @return					void*
 */
static KPTINLINE_FORCE
const void* vectorAtConst(const KPTVectorT* aHandle,
                          size_t aPos)
{
	return KPTBytePointerOffset(aHandle->start, aHandle->valSize * aPos);
}

int KPTVectorCompareAtPrivate(const KPTVectorT* aHandle,
                              size_t aPos,
                              const void* aValue);

size_t
KPT_CALL
KPTVectorLowerBoundPrivate(const KPTVectorT* aHandle,
                           const void* aValue,
                           size_t aLeft,
                           size_t aCount,
                           KPTBoolT* aExists);

size_t
KPT_CALL
KPTVectorUpperBoundPrivate(const KPTVectorT* aHandle,
                           const void* aValue,
                           size_t aLeft,
                           size_t aCount,
                           KPTBoolT* aExists);

size_t
KPT_CALL
KPTVectorEqualRangePrivate(const KPTVectorT* aHandle,
                           const void* aValue,
                           size_t aLeft,
                           size_t aCount,
                           size_t* aLast);

size_t
KPT_CALL
KPTVectorBinarySearchPrivate(const KPTVectorT* aHandle,
                             const void* aValue,
                             size_t aLeft,
                             size_t aCount,
                             KPTBoolT* aExists);

size_t
KPT_CALL
KPTVectorLinearSearchPrivate(const KPTVectorT* aHandle,
                             const void* aValue,
                             size_t aLeft,
                             size_t aCount,
                             KPTBoolT* aExists);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* H_KPT_VECTOR_IMP_H */
