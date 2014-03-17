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
 * @file    kptorderedheap.h
 * 
 * @brief   Interface to ordered heap.
 *
 * @details 
 *  
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTORDEREDHEAP_H
#define H_KPTORDEREDHEAP_H

#include "kptheap.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
* A struct holding heap statistics.
*/
typedef struct KPTHeapTestInfoT KPTHeapTestInfoT;
struct KPTHeapTestInfoT
{
    size_t HeapError;         /**< Last recorded heap error code */
    size_t CurrentNumAllocs;  /**< Number of blocks currently allocated */
    size_t TotalNumAllocs;    /**< Total number of blocks allocated */
    size_t SizeLargestAlloc;  /**< Largest requested block size, in bytes */
    size_t CurrentAllocation; /**< Memory currently allocated, in bytes */
    size_t PeakAllocation;    /**< Maximum memory allocated, in bytes */
    size_t NumMultipleAlloc;  /**< Number of multiple allocs detected */
    size_t NumAllocFails;     /**< Number of allocation failures */
    size_t TotalNumFrees;     /**< Total number of deallocations */
    size_t NumRepeatFrees;    /**< Number of repeat frees detected */
    size_t NumInvalidFrees;   /**< Number of invalid frees detected */
    size_t NumUnderruns;      /**< Number of block overruns detected */
    size_t NumOverruns;       /**< Number of block underruns detected */
    size_t NumFreeBlocks;     /**< Number of free blocks */
	size_t ErrorAllocCount;   /**< Used when injecting errors */
};


/*
 address/size-ordered heap
*/
DECLARE_KPTHANDLE(KPTOrderedHeapT)

/* General system support */
KPTResultT
KPT_CALL
KPTOrderedHeapCreate(KPTHeapT** aHeap, KPTHeapConfigParamsT* aHeapConfigParams);

KPTResultT
KPT_CALL
KPTOrderedHeapDestroy(KPTHeapT** aHeap);

void
KPT_CALL
KPTOrderedHeapSetErrorMode(KPTHeapT* aHeap,
                           KPTHeapManAllocFailureTypeT aFailureType, 
                           size_t aCount);

size_t
KPT_CALL
KPTOrderedHeapGetSystemHeapUsage(const KPTHeapT* aHeap);


/* release interface when release heap */
void*
KPT_CALL
KPTOrderedHeapCallocRel(KPTHeapT* aHeap, size_t aNum, size_t aSize);

void
KPT_CALL
KPTOrderedHeapFreeRel(KPTHeapT* aHeap, void* aMemblock);

void*
KPT_CALL
KPTOrderedHeapMallocRel(KPTHeapT* aHeap, size_t aSize);

void* 
KPT_CALL
KPTOrderedHeapReallocRel(KPTHeapT* aHeap, void* aMemblock, size_t aNewsize);

char*
KPT_CALL
KPTOrderedHeapStrDupNRel(KPTHeapT* aHeap, const char* aSource, size_t aStrLen);

wchar_t*
KPT_CALL
KPTOrderedHeapStrDupWRel(KPTHeapT* aHeap, const wchar_t* aSource, size_t aStrLen);

void
KPT_CALL
KPTOrderedHeapCheckAllMemoryRel(const KPTHeapT* aHeap);

void
KPT_CALL
KPTOrderedHeapEnterScopeRel(KPTHeapT* aHeap);

void
KPT_CALL
KPTOrderedHeapLeaveScopeRel(KPTHeapT* aHeap);

/* debug interface - call release functions if called for a release heap*/
void*
KPT_CALL
KPTOrderedHeapCallocDbg(KPTHeapT* aHeap, size_t aNum, size_t aSize, const char* aFile, int aLine);

void
KPT_CALL
KPTOrderedHeapFreeDbg(KPTHeapT* aHeap, void* aMemblock, const char* aFile, int aLine);

void*
KPT_CALL
KPTOrderedHeapMallocDbg(KPTHeapT* aHeap, size_t aSize, const char* aFile, int aLine);

void* 
KPT_CALL
KPTOrderedHeapReallocDbg(KPTHeapT* aHeap, void* aMemblock, size_t aNewsize, const char* aFile, int aLine);

char*
KPT_CALL
KPTOrderedHeapStrDupNDbg(KPTHeapT* aHeap, const char* aSource, size_t aStrLen, const char* aFile, int aLine);

wchar_t*
KPT_CALL
KPTOrderedHeapStrDupWDbg(KPTHeapT* aHeap, const wchar_t* aSource, size_t aStrLen, const char* aFile, int aLine);


void
KPT_CALL
KPTOrderedHeapCheckAllMemoryDbg(const KPTHeapT* aHeap, const char* aFile, int aLine);

void
KPT_CALL
KPTOrderedHeapEnterScopeDbg(KPTHeapT* aHeap, const char* aFile, int aLine);

void
KPT_CALL
KPTOrderedHeapLeaveScopeDbg(KPTHeapT* aHeap, const char* aFile, int aLine);

/*
release wrappers - these are required for the situation where it's a debug
heap but a release function has been called
*/
void*
KPT_CALL
KPTOrderedHeapCallocRel_Wrap(KPTHeapT* aHeap, size_t aNum, size_t aSize);

void
KPT_CALL
KPTOrderedHeapFreeRel_Wrap(KPTHeapT* aHeap, void* aMemblock);

void*
KPT_CALL
KPTOrderedHeapMallocRel_Wrap(KPTHeapT* aHeap, size_t aSize);

void* 
KPT_CALL
KPTOrderedHeapReallocRel_Wrap(KPTHeapT* aHeap, void* aMemblock, size_t aNewsize);

char*
KPT_CALL
KPTOrderedHeapStrDupNRel_Wrap(KPTHeapT* aHeap, const char* aSource, size_t aStrLen);

wchar_t*
KPT_CALL
KPTOrderedHeapStrDupWRel_Wrap(KPTHeapT* aHeap, const wchar_t* aSource, size_t aStrLen);

void
KPT_CALL
KPTOrderedHeapCheckAllMemoryRel_Wrap(const KPTHeapT* aHeap);

void
KPT_CALL
KPTOrderedHeapEnterScopeRel_Wrap(KPTHeapT* aHeap);

void
KPT_CALL
KPTOrderedHeapLeaveScopeRel_Wrap(KPTHeapT* aHeap);

/*
some useful test functions - do nothing when release heap
*/

size_t
KPT_CALL
KPTOrderedHeapGetDataSizeOfFirstBlock(KPTHeapT* aHeap);

size_t
KPT_CALL
KPTOrderedHeapGetDataSizeOfLastBlock(KPTHeapT* aHeap);

int
KPT_CALL
KPTOrderedHeapGetFreeDataSizes(KPTHeapT* aHeap,
                               size_t* apSizeOfSmallestFree,
                               size_t* apSizeOfLargestFree,
                               size_t* apTotalFreeMemory);

KPTResultT
KPT_CALL
KPTOrderedHeapGetTestInfo(KPTHeapT* aHeap, KPTHeapTestInfoT* apTestInfo);

KPTResultT
KPT_CALL
KPTOrderedHeapGetErrorCodeDbg(const KPTHeapT* aHeap);

KPTResultT
KPT_CALL
KPTOrderedHeapPrintStatisticsDbg(const KPTHeapT* aHeap);

KPTResultT
KPT_CALL
KPTOrderedHeapPrintLayoutDbg(const KPTHeapT* aHeap);

KPTResultT
KPT_CALL
KPTOrderedHeapPrintUsageInfoDbg(const KPTHeapT* aHeap);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /*  H_KPTORDEREDHEAP_H */
