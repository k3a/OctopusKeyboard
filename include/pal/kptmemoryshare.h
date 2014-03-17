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
 * @file    kptmemoryshare.h
 *
 * @brief   Platform structures to store information about shared memory.
 *
 * @details
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTMEMORYSHARE_H
#define H_KPTMEMORYSHARE_H

#include "kptlibsysmem.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

DECLARE_KPTHANDLE(KPTMemoryShareT)

/**
 * Creates & initialises a shared memory structure.
 */
KPT_LIB_SYSMEM
KPTResultT
KPT_CALL
KPTMemoryShareCreate(KPTMemoryShareT** aHandle,
                     KPTHeapT* aHeap,
                     const KPTSysCharT* aName,
                     size_t* aSize,
                     KPTBoolT aWrite,
                     KPTBoolT aNoCreate);

/**
 * Closes & destroys the shared memory structure.
 */
KPT_LIB_SYSMEM
KPTResultT
KPT_CALL
KPTMemoryShareDestroy(KPTMemoryShareT** aHandle,
                      KPTHeapT* aHeap);

/**
 * Gets access to the shared buffer.
 */
KPT_LIB_SYSMEM
uint8_t*
KPT_CALL
KPTMemoryShareGetBuffer(KPTMemoryShareT* aHandle);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTMEMORYSHARE_H */
