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
 * @file    kptunistringcontainer.h
 *
 * @brief   Provides interface for storing unicode strings.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPT_UNI_STRING_CONTAINER_H
#define H_KPT_UNI_STRING_CONTAINER_H

#include "kptapi.h"
#include "kptlibcollections.h"
#include "kptvector.h"

#ifdef __cplusplus 
extern "C" {
#endif /* __cplusplus */

DECLARE_KPTHANDLE(KPTUniStringContainerT)

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTUniStringContainerCreate(KPTUniStringContainerT** aHandle,
                            KPTHeapT* aHeap, 
                            size_t aCharacterReserveSize);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTUniStringContainerDestroy(KPTUniStringContainerT** aHandle);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTUniStringContainerAddString(KPTUniStringContainerT* aHandle,
                               const KPTUniCharT* aString);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTUniStringContainerAddStringWithLength(KPTUniStringContainerT* aHandle, 
                                         const KPTUniCharT* aString,
                                         size_t aStringLen);

KPT_LIB_COLLECTIONS
const KPTUniCharT* 
KPT_CALL
KPTUniStringContainerGet(const KPTUniStringContainerT* aHandle, 
                         size_t aIndex,
                         size_t* aLength);

KPT_LIB_COLLECTIONS
const KPTUniCharT* 
KPT_CALL
KPTUniStringContainerGetString(const KPTUniStringContainerT* aHandle, 
                               size_t aIndex);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTUniStringContainerGetStringLength(const KPTUniStringContainerT* aHandle, 
                                     size_t aIndex, 
                                     size_t* aLength);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTUniStringContainerSwapStrings(KPTUniStringContainerT* aHandle, 
                                 size_t aLeftIndex, 
                                 size_t aRightIndex);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTUniStringContainerSort(KPTUniStringContainerT* aHandle,
                          KPTElementComparerFnT* aElementcomparer);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPT_SYS_STRING_CONTAINER_H */
