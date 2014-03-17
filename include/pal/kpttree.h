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
 * @file kpttree.h
 *
 * @brief Interface declaration of the tree container.
 *
 * @details
 *
 ****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPT_TREE_H
#define H_KPT_TREE_H

#include "kptlibcollections.h"
#include "kptapi.h"
#include "kptiterator.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* KPT Tree  handle */
DECLARE_KPTHANDLE(KPTTreeT)


KPT_LIB_COLLECTIONS
KPTResultT	
KPT_CALL
KPTTreeCreate(KPTTreeT** aHandle, 
              KPTHeapT* aHeap,
              size_t aNodeSize,
              KPTTreeOptionsT aTreeOptions,
              size_t aPreAllocs,
              KPTNodeComparisionFnT* aCompareFn,
              KPTNodeConstructionFnT* aConstructFn,
              KPTNodeDestructionFnT* aDestructFn);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTTreeDestroy(KPTTreeT** aHandle);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTTreeCopyCreate(KPTTreeT** aDestTree,
                  KPTHeapT* aHeap,
                  const KPTTreeT* aSrcTree);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTTreeInsert(KPTTreeT* aHandle,
              const KPTTreeValueT* aNodeVal,
              KPTIteratorT *aOutIter);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTTreeSearchByValue(KPTTreeT* aHandle,
                     const KPTTreeValueT* aNodeVal,
                     KPTIteratorT* aOutIter);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTTreeSearchByPosition(KPTTreeT* aHandle ,
                        KPTIteratorT aPosition);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTTreeDeleteNode(KPTTreeT* aHandle,
                  KPTIteratorT aPosition);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTTreeDeleteByValue(KPTTreeT* aHandle,
                     KPTTreeValueT* aNodeVal);
KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTTreeClear(KPTTreeT* aHandle); 

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTTreeIsEmpty(KPTTreeT* aHandle, 
               KPTBoolT *aIsEmpty);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTTreeIsUnique(KPTTreeT* aHandle, 
                KPTBoolT *aIsUnique);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTTreeSetGrowSize(KPTTreeT* aHandle , 
                   size_t aChunkSize);


KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTTreeGetPreAllocSize(KPTTreeT* aHandle,
                       size_t *aChunkSize);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTTreeGetGrowSize(KPTTreeT* aHandle,
                   size_t *aChunkSize);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTTreeGetType(KPTTreeT* aHandle , 
               KPTTreeOptionsT *aTreeType);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTTreeGetCount(KPTTreeT* aHandle, 
                size_t *aCount);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTTreeGetRoot(KPTTreeT* aHandle , 
               KPTIteratorT *aOutIter);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTTreeBegin(KPTTreeT* aHandle,
             KPTIteratorT *aOutIter);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTTreeEnd(KPTTreeT* aHandle,
           KPTIteratorT *aOutIter);


#ifdef  __cplusplus
}
#endif  /*__cplusplus */

#endif  /* H_KPT_TREE_H */
