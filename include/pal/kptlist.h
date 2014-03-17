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
 * @file    kptlist.h
 *
 * @brief   Provides interface for storing elements in a list data structure
 *
 * @details 
 *  
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPT_LIST_H
#define H_KPT_LIST_H

#include "kptlibcollections.h"
#include "kptapi.h"
#include "kptheap.h"
#include "kptiterator.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

DECLARE_KPTHANDLE(KPTListT)

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTListCreate(KPTListT** aHandle,
              KPTHeapT* aHeap,
              KPTElementComparerFnT* aElementComparer,
              KPTElementDestFnT* aElementDest,
              KPTConstructionFnT* aElementConst,
              KPTBoolT aIsUnique,
              KPTCollectionsTypeT aValType,
              size_t aValSize);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTListCopyCreate(KPTListT** aDest,
                  KPTHeapT* aHeap,
                  const KPTListT* aSource);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTListDestroy(KPTListT** aHandle);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTListBegin(KPTListT* aHandle,
             KPTIteratorT *aIterator);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTListBack(KPTListT* aHandle,
            KPTIteratorT* aIterator);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTListEnd(KPTListT* aHandle,
           KPTIteratorT* aIterator);


KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTListBeginConst(const KPTListT* aHandle,
                  KPTConstIteratorT *aIterator);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTListBackConst(const KPTListT* aHandle,
                 KPTConstIteratorT* aIterator);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTListEndConst(const KPTListT* aHandle,
                KPTConstIteratorT* aIterator);


KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTListClear(KPTListT* aHandle);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTListIsEmpty(const KPTListT* aHandle ,
               KPTBoolT* aIsEmpty);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTListSetMaxSize(KPTListT* aHandle,
                  size_t aMaxSize);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTListSize(const KPTListT* aHandle,
            size_t* aSize);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTListPushFront(KPTListT* aHandle,
                 void* aValue);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTListPushBack(KPTListT* aHandle,
                void* aValue);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTListSort(KPTListT* aHandle,
            KPTElementComparerFnT* aComparerFunction);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTListSetInsertUnique(KPTListT* aHandle,
                       KPTBoolT aUnique);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTListReserveNodes(KPTListT* aHandle,
                    size_t aListSize);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTListSetGrowSize(KPTListT* aHandle,
                   size_t aGrowSize);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTListSortOnInsert(KPTListT* aHandle,
                    void* aValue);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTListInsert(KPTListT* aHandle,
              KPTIteratorT* aPosition ,
              void* aValue);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTListDelete(KPTListT* aHandle,
              KPTIteratorT* aPosition);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTListGetValueType(const KPTListT* aHandle,
                    KPTCollectionsTypeT* aType);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTListIsSorted(const KPTListT* aHandle,
                KPTBoolT* aIsSorted);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTListIsUnique(const KPTListT* aHandle,
                KPTBoolT* aIsUnique);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPT_LIST_H */
