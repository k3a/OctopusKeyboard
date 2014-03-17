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
 * @file    kptheap_imp.h
 *
 * @author  Patrick O'Neill
 *
 * @date    18/12/08
 * 
 * @brief   Private implementation structure for heap objects
 *
 * @details 
 *  
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTHEAP_IMP_H
#define H_KPTHEAP_IMP_H
#include "kptheap.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Function pointer to a heap destroy function */
typedef KPTResultT (KPT_CALL* KPTHeapImpDestroyT)(KPTHeapT** aThis);

/** Function pointer to error mode function */
typedef void (KPT_CALL* KPTHeapImpSetErrorModeT)(KPTHeapT* aThis,
												 KPTHeapManAllocFailureTypeT aFailureType, 
												 size_t aCount);


/** Function pointer to a heap calloc function (release version)*/
typedef void* (KPT_CALL* KPTHeapImpCallocRelT)(KPTHeapT* aThis, size_t aNum, size_t aSize);

/** Function pointer to a heap free function (release version)*/
typedef void (KPT_CALL* KPTHeapImpFreeRelT)(KPTHeapT* aThis, void* aMemblock);

/** Function pointer to a heap malloc function (release version)*/
typedef void* (KPT_CALL* KPTHeapImpMallocRelT)(KPTHeapT* aThis, size_t aSize);

/** Function pointer to a heap realloc function (release version)*/
typedef void* (KPT_CALL* KPTHeapImpReallocRelT)(KPTHeapT* aThis, void* aMemblock, size_t aNewsize);

/** Function pointer to a heap narrow-strdup function (release version)*/
typedef char* (KPT_CALL* KPTHeapImpStrDupNRelT)(KPTHeapT* aThis, const char* aSource, size_t aStrLen);

/** Function pointer to a heap wide-strdup function (release version)*/
typedef wchar_t* (KPT_CALL* KPTHeapImpStrDupWRelT)(KPTHeapT* aThis, const wchar_t* aSource, size_t aStrLen);

/** Function pointer to a heap self-check function (release version)*/
typedef void (KPT_CALL* KPTHeapImpCheckAllMemoryRelT)(const KPTHeapT* aThis);

/** Function pointer to a heap enter-memory-scope function (release version)*/
typedef void (KPT_CALL* KPTHeapImpEnterScopeRelT)(KPTHeapT* aThis);

/** Function pointer to a heap leave-memory-scope function (release version)*/
typedef void (KPT_CALL* KPTHeapImpLeaveScopeRelT)(KPTHeapT* aThis);



/** Function pointer to a heap calloc function (debug version)*/
typedef void* (KPT_CALL* KPTHeapImpCallocDbgT)(KPTHeapT* aThis, size_t aNum, size_t aSize, const char* aFile, int aLine);

/** Function pointer to a heap free function (debug version)*/
typedef void (KPT_CALL* KPTHeapImpFreeDbgT)(KPTHeapT* aThis, void* aMemblock, const char* aFile, int aLine);

/** Function pointer to a heap malloc function (debug version)*/
typedef void* (KPT_CALL* KPTHeapImpMallocDbgT)(KPTHeapT* aThis, size_t aSize, const char* aFile, int aLine);

/** Function pointer to a heap realloc function (debug version)*/
typedef void* (KPT_CALL* KPTHeapImpReallocDbgT)(KPTHeapT* aThis, void* aMemblock, size_t aNewsize, const char* aFile, int aLine);

/** Function pointer to a heap narrow-strdup function (debug version)*/
typedef char* (KPT_CALL* KPTHeapImpStrDupNDbgT)(KPTHeapT* aThis, const char* aSource, size_t aStrLen, const char* aFile, int aLine);

/** Function pointer to a heap wide-strdup function (debug version)*/
typedef wchar_t* (KPT_CALL* KPTHeapImpStrDupWDbgT)(KPTHeapT* aThis, const wchar_t* aSource, size_t aStrLen, const char* aFile, int aLine);

/** Function pointer to a heap self-check function (debug version)*/
typedef void (KPT_CALL* KPTHeapImpCheckAllMemoryDbgT)(const KPTHeapT* aThis, const char* aFile, int aLine);

/** Function pointer to a heap enter-memory-scope function (debug version)*/
typedef void (KPT_CALL* KPTHeapImpEnterScopeDbgT)(KPTHeapT* aThis, const char* aFile, int aLine);

/** Function pointer to a heap leave-memory-scope function (debug version)*/
typedef void (KPT_CALL* KPTHeapImpLeaveScopeDbgT)(KPTHeapT* aThis, const char* aFile, int aLine);

/** Function pointer to get system heap usage function */
typedef size_t (KPT_CALL* KPTHeapUsageT)(const KPTHeapT* aThis);


/**
 * Function table for generic heap interface.
 *
 */
typedef struct KPTHeapImpFuncT KPTHeapImpFuncT;
struct KPTHeapImpFuncT
{
	KPTHeapImpDestroyT Destroy;                          /**< Destroy */

	KPTHeapImpSetErrorModeT SetErrorMode;                /**< SetErrorMode */

	KPTHeapUsageT GetSystemHeapUsage;                    /**< Get system heap usage */

	KPTHeapImpCallocRelT CallocRel;                      /**< Calloc (Release) */
	KPTHeapImpFreeRelT FreeRel;                          /**< Free (Release) */
	KPTHeapImpMallocRelT MallocRel;                      /**< Malloc (Release) */
	KPTHeapImpReallocRelT ReallocRel;                    /**< Reaalloc (Release) */
	KPTHeapImpStrDupNRelT StrDupNRel;                    /**< Narrow StrdDup (Release) */
	KPTHeapImpStrDupWRelT StrDupWRel;                    /**< Wide StrdDup (Release) */
	KPTHeapImpCheckAllMemoryRelT CheckAllMemoryRel;      /**< Memory self-check (Release) */
	KPTHeapImpEnterScopeRelT EnterScopeRel;              /**< Enter memory scope (Release) */
	KPTHeapImpLeaveScopeRelT LeaveScopeRel;              /**< Leave memory scope (Release) */

	KPTHeapImpCallocDbgT CallocDbg;                      /**< Calloc (Debug) */
	KPTHeapImpFreeDbgT FreeDbg;                          /**< Free (Debug) */
	KPTHeapImpMallocDbgT MallocDbg;                      /**< Malloc (Debug) */
	KPTHeapImpReallocDbgT ReallocDbg;                    /**< Reaalloc (Debug) */
	KPTHeapImpStrDupNDbgT StrDupNDbg;                    /**< Narrow StrdDup (Debug) */
	KPTHeapImpStrDupWDbgT StrDupWDbg;                    /**< Wide StrdDup (Debug) */
	KPTHeapImpCheckAllMemoryDbgT CheckAllMemoryDbg;      /**< Memory self-check (Debug) */
	KPTHeapImpEnterScopeDbgT EnterScopeDbg;              /**< Enter memory scope (Debug) */
	KPTHeapImpLeaveScopeDbgT LeaveScopeDbg;              /**< Leave memory scope (Debug) */
};

/**
 * Structure for generic heap interface.
 *
 * This structure allows certain functions to use the KPTHeap methods
 * without knowing the underlying heap implementation. Any object that
 * implements this interface must have this structure as its first member.
 */
struct KPTHeapT
{
	KPTHeapImpFuncT ft; /** Function pointer table */
};

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef _KPT_HEAP_IMP_H_ */
