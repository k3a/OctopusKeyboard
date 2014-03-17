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
 * @file    kptbinheap.h
 *
 * @brief   Interface to bin heap.
 *
 * @details 
 *  
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


#ifndef H_KPTBINHEAP_H
#define H_KPTBINHEAP_H



#include "kptheap.h"

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus */


/*
 bin heap
*/
DECLARE_KPTHANDLE(KPTBinHeapT)



/**
* A struct holding heap statistics.
*/
typedef struct KPTHeapManStatisticsStructT KPTHeapManStatisticsStructT;
struct KPTHeapManStatisticsStructT
{
    unsigned int numAllocFailures;       /**< Number of allocation failures detected */
    unsigned int numBufferUnderruns;     /**< Number of buffer underruns detected */
    unsigned int numBufferOverruns;      /**< Number of buffer overruns detected */
    unsigned int totalBlocks;            /**< Total number of blocks allocated */
    unsigned int currBlocks;             /**< Number of blocks currently allocated */
    size_t largestBlock;                 /**< Largest requested block size, in bytes */
    size_t peakAllocation;               /**< Maximum memory allocted, in bytes */
    size_t currAllocation;               /**< Memory currently allocated, in bytes */
    unsigned int numAllocations;         /**< Number of allocations */
    unsigned int numDeallocations;       /**< Number of de-allocations */
    unsigned int numDoubleDeallocations; /**< Number of double de-allocations detected */
};



/* will report file and line of allocs/free */

/* will fill memory when allocated with defined value */

#define KPTHEAPMAN_FILL_MEM_ON_ALLOCATE_VALUE      0xA5

/* will fill memory when deallocated with defined value */

#define KPTHEAPMAN_FILL_MEM_ON_DEALLOCATE_VALUE    0xA8

/* when allocating memory - we add some bytes before and after the block
 * which we use to determine out of bounds errors */

#define KPTHEAPMAN_MEM_BOUNDARY_CHECK_PRE_SIZE     16  /* multiple of 4 */
#define KPTHEAPMAN_MEM_BOUNDARY_CHECK_PRE_VALUE    0xB3    
#define KPTHEAPMAN_MEM_BOUNDARY_CHECK_POST_SIZE    16      /* multiple of 4 */
#define KPTHEAPMAN_MEM_BOUNDARY_CHECK_POST_VALUE   0xB4

#define KPTHEAPMAN_MEM_BOUNDARY_CHECK_BLOCK_SIZE   4  
#define KPTHEAPMAN_MEM_BOUNDARY_CHECK_NUM_BLOCKS   4  
#define KPTHEAPMAN_MEM_BOUNDARY_CHECK_PRE_BLOCK    0xB3B3B3B3
#define KPTHEAPMAN_MEM_BOUNDARY_CHECK_POST_BLOCK   0xB4B4B4B4

/* will keep track of memory that has been deallocated to detect 
 * double frees. We will deallocate this memory when it is needed
 * or when it reaches a certain memory amount */
#define KPTHEAPMAN_DEALLOCATE_CHECK_LIMIT          (1024*1024) /* 1MB */




KPTResultT
KPT_CALL
KPTBinHeapCreate(KPTHeapT** aHeap, KPTHeapConfigParamsT* aHeapConfigParams);

KPTResultT
KPT_CALL
KPTBinHeapDestroy(KPTHeapT** aHeap);

void
KPT_CALL
KPTBinHeapSetErrorMode(KPTHeapT* aHeap,
                       KPTHeapManAllocFailureTypeT aFailureType, 
                       size_t aCount);

size_t
KPT_CALL
KPTBinHeapGetSystemHeapUsage(const KPTHeapT* aHeap);


/* release interface */
void*
KPT_CALL
KPTBinHeapCallocRel(KPTHeapT* aHeap, size_t aNum, size_t aSize);

void
KPT_CALL
KPTBinHeapFreeRel(KPTHeapT* aHeap, void* aMemblock);

void*
KPT_CALL
KPTBinHeapMallocRel(KPTHeapT* aHeap, size_t aSize);

void* 
KPT_CALL
KPTBinHeapReallocRel(KPTHeapT* aHeap, void* aMemblock, size_t aNewsize);

char*
KPT_CALL
KPTBinHeapStrDupNRel(KPTHeapT* aHeap, const char* aSource, size_t aStrLen);

wchar_t*
KPT_CALL
KPTBinHeapStrDupWRel(KPTHeapT* aHeap, const wchar_t* aSource, size_t aStrLen);

void
KPT_CALL
KPTBinHeapCheckAllMemoryRel(const KPTHeapT* aHeap);

void
KPT_CALL
KPTBinHeapEnterScopeRel(KPTHeapT* aHeap);

void
KPT_CALL
KPTBinHeapLeaveScopeRel(KPTHeapT* aHeap);

/* debug interface */

void*
KPT_CALL
KPTBinHeapCallocDbg(KPTHeapT* aHeap, size_t aNum, size_t aSize, const char* aFile, int aLine);

void
KPT_CALL
KPTBinHeapFreeDbg(KPTHeapT* aHeap, void* aMemblock, const char* aFile, int aLine);

void*
KPT_CALL
KPTBinHeapMallocDbg(KPTHeapT* aHeap, size_t aSize, const char* aFile, int aLine);

void* 
KPT_CALL
KPTBinHeapReallocDbg(KPTHeapT* aHeap, void* aMemblock, size_t aNewsize, const char* aFile, int aLine);

char*
KPT_CALL
KPTBinHeapStrDupNDbg(KPTHeapT* aHeap, const char* aSource, size_t aStrLen, const char* aFile, int aLine);

wchar_t*
KPT_CALL
KPTBinHeapStrDupWDbg(KPTHeapT* aHeap, const wchar_t* aSource, size_t aStrLen, const char* aFile, int aLine);

void
KPT_CALL
KPTBinHeapCheckAllMemoryDbg(const KPTHeapT* aHeap, const char* aFile, int aLine);

void
KPT_CALL
KPTBinHeapEnterScopeDbg(KPTHeapT* aHeap, const char* aFile, int aLine);

void
KPT_CALL
KPTBinHeapLeaveScopeDbg(KPTHeapT* aHeap, const char* aFile, int aLine);


/*
some useful test functions 
*/

KPTResultT
KPT_CALL
KPTBinHeapGetErrorCodeDbg(const KPTHeapT* aHeap);

KPTResultT
KPT_CALL
KPTBinHeapPrintStatisticsDbg(const KPTHeapT* aHeap);

KPTResultT
KPT_CALL
KPTBinHeapPrintLayoutDbg(const KPTHeapT* aHeap);

KPTResultT
KPT_CALL
KPTBinHeapPrintUsageInfoDbg(const KPTHeapT* aHeap);


/* release interface wrappers */
void*
KPT_CALL
KPTBinHeapCallocRel_Wrap(KPTHeapT* aHeap, size_t aNum, size_t aSize);

void
KPT_CALL
KPTBinHeapFreeRel_Wrap(KPTHeapT* aHeap, void* aMemblock);

void*
KPT_CALL
KPTBinHeapMallocRel_Wrap(KPTHeapT* aHeap, size_t aSize);

void* 
KPT_CALL
KPTBinHeapReallocRel_Wrap(KPTHeapT* aHeap, void* aMemblock, size_t aNewsize);

char*
KPT_CALL
KPTBinHeapStrDupNRel_Wrap(KPTHeapT* aHeap, const char* aSource, size_t aStrLen);

wchar_t*
KPT_CALL
KPTBinHeapStrDupWRel_Wrap(KPTHeapT* aHeap, const wchar_t* aSource, size_t aStrLen);


void
KPT_CALL
KPTBinHeapCheckAllMemoryRel_Wrap(const KPTHeapT* aHeap);

void
KPT_CALL
KPTBinHeapEnterScopeRel_Wrap(KPTHeapT* aHeap);

void
KPT_CALL
KPTBinHeapLeaveScopeRel_Wrap(KPTHeapT* aHeap);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /*_KPTBINHEAP_H_*/
