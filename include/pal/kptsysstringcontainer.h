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
 * @file    KPTSysStringContainer.h
 * 
 * @brief   Provides interface for storing system strings
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPT_SYS_STRING_CONTAINER_H
#define H_KPT_SYS_STRING_CONTAINER_H

#include "kptapi.h"
#include "kptlibcollections.h"
#include "kptvector.h"

#ifdef __cplusplus 
extern "C" {
#endif /* __cplusplus */

DECLARE_KPTHANDLE(KPTSysStringContainerT)

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTSysStringContainerCreate(KPTSysStringContainerT** aHandle,
                            KPTHeapT* aHeap, 
                            size_t aCharacterReserveSize);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTSysStringContainerDestroy(KPTSysStringContainerT** aHandle);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTSysStringContainerAddString(KPTSysStringContainerT* aHandle, 
                               const KPTSysCharT* aString);

KPT_LIB_COLLECTIONS
const KPTSysCharT* 
KPT_CALL
KPTSysStringContainerGet(const KPTSysStringContainerT* aHandle, 
                         size_t aIndex,
                         size_t* aLength);

KPT_LIB_COLLECTIONS
const KPTSysCharT* 
KPT_CALL
KPTSysStringContainerGetString(const KPTSysStringContainerT* aHandle, 
                               size_t aIndex);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTSysStringContainerGetStringLength(const KPTSysStringContainerT* aHandle, 
                                     size_t aIndex, 
                                     size_t* aLength);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTSysStringContainerSwapStrings(KPTSysStringContainerT* aHandle, 
                                 size_t aLeftIndex, 
                                 size_t aRightIndex);

KPT_LIB_COLLECTIONS
KPTResultT
KPT_CALL
KPTSysStringContainerSort(KPTSysStringContainerT* aHandle,
                          KPTElementComparerFnT* aElementcomparer);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPT_SYS_STRING_CONTAINER_H */
