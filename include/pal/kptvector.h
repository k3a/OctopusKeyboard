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
 * @file kptvector.h
 *
 * @brief Interface declaration of the vector container.
 *
 * @details 
 *
 ****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPT_VECTOR_H
#define H_KPT_VECTOR_H

#include "kptlibcollections.h"
#include "kptapi.h"
#include "kptheap.h"
#include "kptiterator.h"

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus */

DECLARE_KPTHANDLE(KPTVectorT)

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorCreate(KPTVectorT** aHandle, 
                KPTHeapT* aHeap,
                KPTElementComparerFnT* aElementComparer,
                KPTElementDestFnT* aElementDest,
                KPTConstructionFnT* aConstFuncPtr,
                KPTBoolT aIsUnique,
                KPTCollectionsTypeT aValType, 
                size_t aValSize);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorCopyCreate(KPTVectorT** aDest,
                    KPTHeapT* aHeap,
                    const KPTVectorT* aSource);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorDestroy(KPTVectorT** aHandle);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorBegin(KPTVectorT* aHandle,
               KPTIteratorT* aIterator);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorBeginConst(const KPTVectorT* aHandle,
                    KPTConstIteratorT* aIterator);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorEnd(KPTVectorT* aHandle,
             KPTIteratorT* aIterator);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorEndConst(const KPTVectorT* aHandle,
                  KPTConstIteratorT* aIterator);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorBack(KPTVectorT* aHandle,
              KPTIteratorT* aIterator);


KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorBackConst(const KPTVectorT* aHandle,
                   KPTConstIteratorT* aIterator);



KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorInsertFront(KPTVectorT* aHandle,
                     const void* aValToInsert);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorInsertBack(KPTVectorT* aHandle,
                    const void* aValToInsert);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorInsertAt(KPTVectorT* aHandle, 
                  KPTIteratorT* aIteratorPos, 
                  const void* aValToInsert);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorInsertAtIndex(KPTVectorT* aHandle, 
                       size_t aIndex, 
                       const void* aValToInsert);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorSortInsert(KPTVectorT* aHandle,
                    const void* aValue,
					size_t* aPosition);

KPT_LIB_COLLECTIONS
void*
KPT_CALL
KPTVectorAt(KPTVectorT* aHandle,
            size_t aPos);

KPT_LIB_COLLECTIONS
const void*
KPT_CALL
KPTVectorAtConst(const KPTVectorT* aHandle,
                 size_t aPos);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorSwap(KPTVectorT* aHandle,
              size_t aLeft,
              size_t aRight);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorPopBack(KPTVectorT* aHandle);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorErase(KPTVectorT* aHandle,
               KPTIteratorT* aDeletePos);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorEraseN(KPTVectorT* aHandle,
				KPTIteratorT aFirst,
				KPTIteratorT aLast,
				KPTIteratorT* aReturnPos);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorEraseAtIndex(KPTVectorT* aHandle,
                      size_t aIndex);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorClear(KPTVectorT* aHandle);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorClearMemory(KPTVectorT* aHandle);


KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorGetSize(const KPTVectorT* aHandle,
                 size_t* aSize);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorGetCapacity(const KPTVectorT* aHandle,
                     size_t* aCapacity);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorGetMaxSize(const KPTVectorT* aHandle,
                   size_t* aMaxSize);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorGetValType(const KPTVectorT* aHandle, 
                    KPTCollectionsTypeT* aVectorType);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorIsSorted(const KPTVectorT* aHandle, 
                  KPTBoolT* aIsSorted);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorIsUnique(const KPTVectorT* aHandle, 
                  KPTBoolT* aIsUnique);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorIsEmpty(const KPTVectorT* aHandle,
                 KPTBoolT* aIsEmpty);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorSetGrowSize(KPTVectorT* aHandle, 
                     size_t aGrowSize);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorSetMaxSize(KPTVectorT* aHandle,
                    size_t aMaxSize);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorReserve(KPTVectorT* aHandle,
                 size_t aNewSize);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorTruncate (KPTVectorT* aHandle,
				 size_t aNewSize);


KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorSort(KPTVectorT* aHandle,
              KPTElementComparerFnT* aElementComparer);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorFind(const KPTVectorT* aHandle,
              const void* aValueToBeFound,
              size_t* aNearestPos);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorGetDataAddress(const KPTVectorT* aHandle,
                        void** aDataAddress,
                        size_t* aSize);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorLowerBound(const KPTVectorT* aHandle,
                    const void* aValue,
                    size_t* aFirst,
                    KPTBoolT* aExists);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorUpperBound(const KPTVectorT* aHandle,
                    const void* aValue,
                    size_t* aLast,
                    KPTBoolT* aExists);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorEqualRange(const KPTVectorT* aHandle,
                    const void* aValue,
                    size_t* aFirst,
                    size_t* aLast);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorInsertRange(KPTVectorT* aHandle,
					 KPTIteratorT aInsertPos,
					 KPTIteratorT aStartPos,
					 KPTIteratorT aEndPos);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorInsertBackN(KPTVectorT* aHandle,
					 size_t aCount, 
					 void* aValToInsert,
					 KPTBoolT aInsertElement);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTVectorInsertBackArrayOfElements(KPTVectorT* aHandle,
								   size_t aCount, 
								   void** aArrayOfElements);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* H_KPT_VECTOR_H */
