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
 * @file kptmap.h
 *
 * @brief Interface declaration of the map container.
 *
 * @details 
 *
 ****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPT_MAP_H
#define H_KPT_MAP_H

#include "kptlibcollections.h"
#include "kptapi.h"
#include "kptiterator.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Map Handle */
DECLARE_KPTHANDLE(KPTMapT)

/** Map Options  */
enum KPTMapOptionsT
{
	eKPTMapMulti  = KPTBIT(0),		  /**< Create a multimap if supported */
	eKPTMapRBTree = eKPTTreeRBTree,		  /**< Use a RBT if supported */
	eKPTMapBSTree = eKPTTreeBSTree,		  /**< Use a BST if supported */
};
typedef enum KPTMapOptionsT KPTMapOptionsT;

/* Key used in KPTMapItem */
typedef void KPTMapKeyT;

/* Value used in KPTMapItem */
typedef void KPTMapValueT;

typedef struct KPTMapItemT KPTMapItemT;
/** Structure to hold Key-Value Pair */
struct KPTMapItemT
{
	KPTMapKeyT* key;     /**< Key element */
	KPTMapValueT* value; /**< Value element */
};

/* Map destruction function to destroy KPTMapItemT type*/
typedef void (KPT_CALLB KPTMapItemDestructionFnT)(KPTHeapT* aHeap, KPTMapItemT* aMapItem);

/* Map Key Comparision function */
typedef int (KPT_CALLB KPTMapKeyComparisionFnT)(const KPTMapKeyT* aLeftKey,
                                                const KPTMapKeyT* aRightKey);

/* Map Node construction function to construct KPTMapItemT type*/
typedef KPTResultT (KPT_CALLB KPTMapItemConstructionFnT)(KPTHeapT* aHeap,
                                                         KPTMapItemT* aTarget,
                                                         const KPTMapItemT* aSource);


KPT_LIB_COLLECTIONS
KPTResultT 
KPT_CALL
KPTMapCreate(KPTMapT** aHandle,
             KPTHeapT* aHeap,
             size_t aKeySize, 
             size_t aValueSize, 
             KPTMapKeyComparisionFnT* aCompareFn,
             KPTMapItemConstructionFnT* aConstructFn,
             KPTMapItemDestructionFnT* aDestructFn,
             size_t	aPreAllocs,
             KPTMapOptionsT aMapOptions);

KPT_LIB_COLLECTIONS
KPTResultT 
KPT_CALL
KPTMapDestroy(KPTMapT** aHandle);

KPT_LIB_COLLECTIONS
KPTResultT 
KPT_CALL
KPTMapCopyCreate(KPTMapT** aDestMap,
                 KPTHeapT* aHeap,
                 const KPTMapT* aSrcMap);

KPT_LIB_COLLECTIONS
KPTResultT 
KPT_CALL
KPTMapInsertPair(KPTMapT* aHandle,
                 const KPTMapItemT* aNodeVal, 
                 KPTIteratorT* aOutIter);


KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTMapInsert(KPTMapT* aHandle,
             const KPTMapKeyT* aKey,
             const KPTMapValueT* aValue,
             KPTIteratorT* aOutIter);

KPT_LIB_COLLECTIONS
KPTResultT 
KPT_CALL
KPTMapSearchByKey(KPTMapT* aHandle,
                  const KPTMapKeyT* aKey,
                  KPTIteratorT* aOutIter);

KPT_LIB_COLLECTIONS
KPTResultT 
KPT_CALL
KPTMapSearchByKeyConst(const KPTMapT* aHandle,
                       const KPTMapKeyT* aKey,
                       KPTConstIteratorT* aOutIter);

KPT_LIB_COLLECTIONS
KPTResultT 
KPT_CALL
KPTMapSearchByPosition(KPTMapT* aHandle,
                       KPTIteratorT aPosition);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTMapSearchByPositionConst(const KPTMapT* aHandle,
                            KPTConstIteratorT aPosition);

KPT_LIB_COLLECTIONS
KPTResultT 
KPT_CALL
KPTMapDeleteByKey(KPTMapT* aHandle, 
                  KPTMapKeyT* aKey);

KPT_LIB_COLLECTIONS
KPTResultT 
KPT_CALL
KPTMapIsEmpty(const KPTMapT* aHandle, 
              KPTBoolT* aIsEmpty);

KPT_LIB_COLLECTIONS
KPTResultT 
KPT_CALL
KPTMapIsUnique(const KPTMapT* aHandle, 
               KPTBoolT* aIsUnique);

KPT_LIB_COLLECTIONS
KPTResultT 
KPT_CALL
KPTMapSetGrowSize(KPTMapT* aHandle, 
                  size_t aChunkSize);

KPT_LIB_COLLECTIONS
KPTResultT 
KPT_CALL
KPTMapGetPreAllocSize(const KPTMapT* aHandle,
                      size_t* aChunkSize);

KPT_LIB_COLLECTIONS
KPTResultT 
KPT_CALL
KPTMapGetGrowSize(const KPTMapT* aHandle, 
                  size_t* aChunkSize);


KPT_LIB_COLLECTIONS
KPTResultT 
KPT_CALL
KPTMapGetCount(const KPTMapT* aHandle, 
               size_t* aCount);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTMapBegin(KPTMapT* aHandle,
            KPTIteratorT* aOutIter);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTMapBeginConst(const KPTMapT* aHandle,
                 KPTConstIteratorT* aOutIter);


KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTMapEnd(KPTMapT* aHandle,
          KPTIteratorT* aOutIter);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTMapEndConst(const KPTMapT* aHandle,
               KPTConstIteratorT* aOutIter);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif	/* H_KPT_MAP_H */
