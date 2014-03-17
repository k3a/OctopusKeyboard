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
 * @file    kptalloct.h
 *
 * @brief   Allocation block header.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTALLOC_H
#define H_KPTALLOC_H

#include "kptlibutil.h"
#include "kptapi.h"
#include "kptheap.h"

/** Allocation header type */
typedef struct KPTAllocT KPTAllocT;

/**
 * Signature for element destructor.
 *
 * @param[in] aProgress An allocation header.
 * @return              KPTResultT.
 */
typedef KPTResultT (KPT_CALLB *KPTAllocElementDestructorT)(KPTAllocT* aAlloc);

/** Allocation header structure */
struct KPTAllocT
{
	size_t allocSize;                             /**< Total number of bytes allocated */
	size_t dataSize;                              /**< Number of bytes in use */
	size_t elementCount;                          /**< Number of elements */
	size_t callerStructSize;                      /**< Size of the structure that wraps the header */
	KPTHeapT* heap;                               /**< The heap that stores the data */
	KPTAllocElementDestructorT elementDestructor; /**< Cleanup for elements */
	intptr_t data[1];                             /**< Start of allocation data; start = &(alloc->data) */
};

/**
 * Format for all AllocT wrappers.
 * Each wrapper must be large enough to hold a data pointer
 * as the first element. The element must be zero-initialised.
 *
 */
typedef struct KPTAllocWrapperT KPTAllocWrapperT;
struct KPTAllocWrapperT
{
	void *data;
};

KPT_LIB_UTIL
KPTResultT
KPT_CALL
KPTAllocRelease(KPTAllocWrapperT* aAlloc);

KPT_LIB_UTIL
KPTAllocT*
KPT_CALL
KPTAllocAcquire(KPTAllocWrapperT* aAllocWrapper,
                size_t aAllocWrapperSize,
                size_t aDataBytes,
                size_t aElementCount,
                KPTAllocElementDestructorT aElementDestructor,
                KPTHeapT* aHeap);

#endif /* #ifndef H_KPTALLOC_H */
