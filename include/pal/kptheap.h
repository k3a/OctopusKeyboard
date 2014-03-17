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
 * @file    kptheap.h
 *
 * @brief   Abstract interface for heap objects
 *
 * @details 
 *  
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTHEAP_H
#define H_KPTHEAP_H

#include "kptlibsysmem.h"
#include "kptapi.h"

DECLARE_KPTHANDLE(KPTHeapT)
DECLARE_KPTHANDLE(KPTOutT)

/** Heap algorithms */
enum KPTHeapAlgorithmT
{
	eKPTHeapNull        = 0,    /**< System heap */
	eKPTHeapSizeOrdered = 0x1,  /**< Size ordered heap algorithm */
	eKPTHeapAddrOrdered = 0x2,  /**< Address ordered heap algorithm */
	eKPTHeapCoreBin     = 0x3   /**< Old core heap using Bins */
};
typedef enum KPTHeapAlgorithmT KPTHeapAlgorithmT;

/** Failure types for a debug heap */
enum KPTHeapManAllocFailureTypeT
{
	eKPTHeapManAllocFailureType_None = 0,         /**< No Heap Failure Enabled */
	eKPTHeapManAllocFailureType_FailAfterNum = 1, /**< Heap alloc failure after N allocations */
	eKPTHeapManAllocFailureType_FailEveryNum = 2  /**< Heap alloc failure every N allocations */
};
typedef enum KPTHeapManAllocFailureTypeT KPTHeapManAllocFailureTypeT;


/** Heap configuration structure */
typedef struct KPTHeapConfigParamsT KPTHeapConfigParamsT;
struct KPTHeapConfigParamsT
{
	size_t SizeInBytes;               /**< Initial size in bytes */
	KPTHeapT* SourceHeap;             /**< Where the heap gets its memory */
	KPTBoolT FixedHeap;               /**< True for a heap that cannot grow in size*/
	size_t GrowSizeInBytes;           /**< Minimum grow size when the heap expands */
	KPTHeapAlgorithmT HeapAlgorithm;  /**< Heap algorithm */
    KPTBoolT DebugHeap;               /**< Request debug heap */
	KPTOutT* OutHandle;               /**< Heap output when DebugHeap is true */
    KPTBoolT BoundsCheckingOn;        /**< Enable under/over-run checking for a debug heap */
    KPTHeapManAllocFailureTypeT FailureType; /**< Specify failure type for a debug heap */
    size_t FailureRate;   /**< Failure rate for a debug heap. */
    KPTBoolT Lockable;   /**< If true, critical sections are used to control access to the heap */
};

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* heap */

KPT_LIB_SYSMEM
KPTResultT
KPT_CALL
KPTHeapCreate(KPTHeapT** aHeap,
              KPTHeapConfigParamsT* aHeapConfigParams);

KPT_LIB_SYSMEM
KPTResultT
KPT_CALL
KPTHeapDestroy(KPTHeapT** aHeap);

KPT_LIB_SYSMEM
KPTResultT
KPT_CALL
KPTHeapGetSystemHeapUsage(const KPTHeapT* aHeap, size_t* aSystemBytesUsed);


KPT_LIB_SYSMEM
KPTResultT
KPT_CALL
KPTHeapSetErrorMode(KPTHeapT* aHeap,
					KPTHeapManAllocFailureTypeT aFailureType, 
					size_t aCount);

/* release interface */
KPT_LIB_SYSMEM
void*
KPT_CALL
KPTHeapCallocRel(KPTHeapT* aHeap,
                 size_t aNum,
                 size_t aSize);

KPT_LIB_SYSMEM
void
KPT_CALL
KPTHeapFreeRel(KPTHeapT* aHeap,
               void* aMemblock);

KPT_LIB_SYSMEM
void*
KPT_CALL
KPTHeapMallocRel(KPTHeapT* aHeap,
                 size_t aSize);

KPT_LIB_SYSMEM
void* 
KPT_CALL
KPTHeapReallocRel(KPTHeapT* aHeap,
                  void* aMemblock,
                  size_t aNewsize);

KPT_LIB_SYSMEM
char*
KPT_CALL
KPTHeapStrDupNRel(KPTHeapT* aHeap,
                  const char* aSource,
                  size_t aStrLen);

KPT_LIB_SYSMEM
wchar_t*
KPT_CALL
KPTHeapStrDupWRel(KPTHeapT* aHeap,
                  const wchar_t* aSource,
                  size_t aStrLen);

KPT_LIB_SYSMEM
void
KPT_CALL
KPTHeapCheckAllMemoryRel(const KPTHeapT* aHeap);

KPT_LIB_SYSMEM
void
KPT_CALL
KPTHeapEnterScopeRel(KPTHeapT* aHeap);

KPT_LIB_SYSMEM
void
KPT_CALL
KPTHeapLeaveScopeRel(KPTHeapT* aHeap);


/* debug interface */
KPT_LIB_SYSMEM
void*
KPT_CALL
KPTHeapCallocDbg(KPTHeapT* aHeap,
                 size_t aNum,
                 size_t aSize,
                 const char* aFile,
                 int aLine);

KPT_LIB_SYSMEM
void
KPT_CALL
KPTHeapFreeDbg(KPTHeapT* aHeap,
               void* aMemblock,
               const char* aFile,
               int aLine);

KPT_LIB_SYSMEM
void*
KPT_CALL
KPTHeapMallocDbg(KPTHeapT* aHeap,
                 size_t aSize,
                 const char* aFile,
                 int aLine);

KPT_LIB_SYSMEM
void* 
KPT_CALL
KPTHeapReallocDbg(KPTHeapT* aHeap,
                  void* aMemblock,
                  size_t aNewsize,
                  const char* aFile,
                  int aLine);

KPT_LIB_SYSMEM
char*
KPT_CALL
KPTHeapStrDupNDbg(KPTHeapT* aHeap,
                  const char* aSource,
                  size_t aStrLen,
                  const char* aFile,
                  int aLine);

KPT_LIB_SYSMEM
wchar_t*
KPT_CALL
KPTHeapStrDupWDbg(KPTHeapT* aHeap,
                  const wchar_t* aSource,
                  size_t aStrLen,
                  const char* aFile,
                  int aLine);

KPT_LIB_SYSMEM
void
KPT_CALL
KPTHeapCheckAllMemoryDbg(const KPTHeapT* aHeap,
                         const char* aFile,
                         int aLine);

KPT_LIB_SYSMEM
void
KPT_CALL
KPTHeapEnterScopeDbg(KPTHeapT* aHeap,
                     const char* aFile,
                     int aLine);

KPT_LIB_SYSMEM
void
KPT_CALL
KPTHeapLeaveScopeDbg(KPTHeapT* aHeap,
                     const char* aFile,
                     int aLine);


#if defined(KPTHEAP_USE_DEBUG)

#define KPTHeapCalloc(heap, num, size)      KPTHeapCallocDbg(heap, num, size, KPTLOC, KPTLINE)
#define KPTHeapFree(heap, mem)              KPTHeapFreeDbg(heap, mem, KPTLOC, KPTLINE)
#define KPTHeapMalloc(heap, size)           KPTHeapMallocDbg(heap, size, KPTLOC, KPTLINE)
#define KPTHeapRealloc(heap, mem, newsize)  KPTHeapReallocDbg(heap, mem, newsize, KPTLOC, KPTLINE)
#define KPTHeapStrDupN(heap, str, len)      KPTHeapStrDupNDbg(heap, str, len, KPTLOC, KPTLINE)
#define KPTHeapStrDupW(heap, str, len)      KPTHeapStrDupWDbg(heap, str, len, KPTLOC, KPTLINE)
#define KPTHeapCheckAllMemory(heap)         KPTHeapCheckAllMemoryDbg(heap, KPTLOC, KPTLINE)
#define KPTHeapEnterScope(heap)             KPTHeapEnterScopeDbg(heap, KPTLOC, KPTLINE)
#define KPTHeapLeaveScope(heap)             KPTHeapLeaveScopeDbg(heap, KPTLOC, KPTLINE)

#if KPT_TSYSCHAR_ISWIDE
	#define KPTHeapStrDupS(heap, str, len)       KPTHeapStrDupWDbg(heap, str, len, KPTLOC, KPTLINE)
#else
	#define KPTHeapStrDupS(heap, str, len)       KPTHeapStrDupNDbg(heap, str, len, KPTLOC, KPTLINE)
#endif

#else

#define KPTHeapCalloc(heap, num, size)      KPTHeapCallocRel(heap, num, size)
#define KPTHeapFree(heap, mem)              KPTHeapFreeRel(heap, mem)
#define KPTHeapMalloc(heap, size)           KPTHeapMallocRel(heap, size)
#define KPTHeapRealloc(heap, mem, newsize)  KPTHeapReallocRel(heap, mem, newsize)
#define KPTHeapStrDupN(heap, str, len)      KPTHeapStrDupNRel(heap, str, len)
#define KPTHeapStrDupW(heap, str, len)      KPTHeapStrDupWRel(heap, str, len)
#define KPTHeapCheckAllMemory(heap)         KPTHeapCheckAllMemoryRel(heap)
#define KPTHeapEnterScope(heap)             KPTHeapEnterScopeRel(heap)
#define KPTHeapLeaveScope(heap)             KPTHeapLeaveScopeRel(heap)

#if KPT_TSYSCHAR_ISWIDE
	#define KPTHeapStrDupS(heap, str, len)       KPTHeapStrDupWRel(heap, str, len)
#else
	#define KPTHeapStrDupS(heap, str, len)       KPTHeapStrDupNRel(heap, str, len)
#endif

#endif /* end if not KPTHEAP_USE_DEBUG */

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTHEAP_H */
