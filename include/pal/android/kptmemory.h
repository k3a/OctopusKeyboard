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
 * @file    kptmemory.h
 *
 * @brief   Standard system memory allocators for android.
 *
 * @details 
 *  
 *****************************************************************************/

#ifndef H_KPTMEMORY_H
#define H_KPTMEMORY_H

#include "kptlibsysmem.h"
#include "kptapi.h"
#include "kptsysmem.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (KPTMEM_USE_DEBUG)

	#define KPTMemStartupRel			KPTSysMemStartupRel
	#define KPTMemShutdownRel			KPTSysMemShutdownRel
	#define KPTMemCallocRel				KPTSysMemCallocRel
	#define KPTMemFreeRel				KPTSysMemFreeRel
	#define KPTMemMallocRel				KPTSysMemMallocRel
	#define KPTMemReallocRel			KPTSysMemReallocRel
	#define KPTMemStrDupNRel			KPTSysMemStrDupNRel
	#define KPTMemStrDupWRel			KPTSysMemStrDupWRel
	#define KPTMemCheckAllMemoryRel		KPTSysMemCheckAllMemoryRel
	#define KPTMemEnterScopeRel			KPTSysMemEnterScopeRel
	#define KPTMemLeaveScopeRel			KPTSysMemLeaveScopeRel

	#define KPTMemStartupDbg			KPTSysMemStartupDbg
	#define KPTMemShutdownDbg			KPTSysMemShutdownDbg
	#define KPTMemCallocDbg				KPTSysMemCallocDbg
	#define KPTMemFreeDbg				KPTSysMemFreeDbg
	#define KPTMemMallocDbg				KPTSysMemMallocDbg
	#define KPTMemReallocDbg			KPTSysMemReallocDbg
	#define KPTMemStrDupNDbg			KPTSysMemStrDupNDbg
	#define KPTMemStrDupWDbg			KPTSysMemStrDupWDbg
	#define KPTMemCheckAllMemoryDbg		KPTSysMemCheckAllMemoryDbg
	#define KPTMemEnterScopeDbg			KPTSysMemEnterScopeDbg
	#define KPTMemLeaveScopeDbg			KPTSysMemLeaveScopeDbg

	#define KPTMemStartup(ptr)           KPTSysMemStartupDbg(ptr, KPTLOC, KPTLINE)
	#define KPTMemShutdown(ptr)          KPTSysMemShutdownDbg(ptr, KPTLOC, KPTLINE)
	#define KPTMemCalloc(num, size)      KPTSysMemCallocDbg(num, size, KPTLOC, KPTLINE)
	#define KPTMemFree(mem)              KPTSysMemFreeDbg(mem, KPTLOC, KPTLINE)
	#define KPTMemMalloc(size)           KPTSysMemMallocDbg(size, KPTLOC, KPTLINE)
	#define KPTMemRealloc(mem, newsize)  KPTSysMemReallocDbg(mem, newsize, KPTLOC, KPTLINE)
	#define KPTMemStrDupN(str)           KPTSysMemStrDupNDbg(str, KPTLOC, KPTLINE)
	#define KPTMemStrDupW(str)           KPTSysMemStrDupWDbg(str, KPTLOC, KPTLINE)
	#define KPTMemCheckAllMemory()       KPTSysMemCheckAllMemoryDbg(KPTLOC, KPTLINE)
	#define KPTMemEnterScope()           KPTSysMemEnterScopeDbg(KPTLOC, KPTLINE)
	#define KPTMemLeaveScope()           KPTSysMemLeaveScopeDbg(KPTLOC, KPTLINE)

#elif defined(KPTMEM_USE_RELEASE) /* #if defined (KPTMEM_USE_DEBUG) */

	#define KPTMemStartupRel			KPTSysMemStartupRel
	#define KPTMemShutdownRel			KPTSysMemShutdownRel
	#define KPTMemCallocRel				KPTSysMemCallocRel
	#define KPTMemFreeRel				KPTSysMemFreeRel
	#define KPTMemMallocRel				KPTSysMemMallocRel
	#define KPTMemReallocRel			KPTSysMemReallocRel
	#define KPTMemStrDupNRel			KPTSysMemStrDupNRel
	#define KPTMemStrDupWRel			KPTSysMemStrDupWRel
	#define KPTMemCheckAllMemoryRel		KPTSysMemCheckAllMemoryRel
	#define KPTMemEnterScopeRel			KPTSysMemEnterScopeRel
	#define KPTMemLeaveScopeRel			KPTSysMemLeaveScopeRel

	#define KPTMemStartupDbg			KPTSysMemStartupDbg
	#define KPTMemShutdownDbg			KPTSysMemShutdownDbg
	#define KPTMemCallocDbg				KPTSysMemCallocDbg
	#define KPTMemFreeDbg				KPTSysMemFreeDbg
	#define KPTMemMallocDbg				KPTSysMemMallocDbg
	#define KPTMemReallocDbg			KPTSysMemReallocDbg
	#define KPTMemStrDupNDbg			KPTSysMemStrDupNDbg
	#define KPTMemStrDupWDbg			KPTSysMemStrDupWDbg
	#define KPTMemCheckAllMemoryDbg		KPTSysMemCheckAllMemoryDbg
	#define KPTMemEnterScopeDbg			KPTSysMemEnterScopeDbg
	#define KPTMemLeaveScopeDbg			KPTSysMemLeaveScopeDbg

	#define KPTMemStartup(ptr)           KPTSysMemStartupDbg(ptr)
	#define KPTMemShutdown(ptr)          KPTSysMemShutdownDbg(ptr)
	#define KPTMemCalloc(num, size)      KPTSysMemCallocRel(num, size)
	#define KPTMemFree(mem)              KPTSysMemFreeRel(mem)
	#define KPTMemMalloc(size)           KPTSysMemMallocRel(size)
	#define KPTMemRealloc(mem, newsize)  KPTSysMemReallocRel(mem, newsize)
	#define KPTMemStrDupN(str)           KPTSysMemStrDupNRel(str)
	#define KPTMemStrDupW(str)           KPTSysMemStrDupWRel(str)
	#define KPTMemCheckAllMemory()       KPTSysMemCheckAllMemoryRel()
	#define KPTMemEnterScope()           KPTSysMemEnterScopeRel()
	#define KPTMemLeaveScope()           KPTSysMemLeaveScopeRel()

#else /* #elif defined(KPTMEM_USE_RELEASE) */

	#define KPTMemStartupRel(ptr)								KPT_NOP_FUNCTION
	#define KPTMemShutdownRel(ptr)								KPT_NOP_FUNCTION
	#define KPTMemCallocRel(aNum, aSize)						calloc(aNum, aSize)
	#define KPTMemFreeRel(aMemblock)							free(aMemblock)
	#define KPTMemMallocRel(aSize)								malloc(aSize)
	#define KPTMemReallocRel(aMemblock, aSize)					realloc(aMemblock, aSize)
	#define KPTMemStrDupNRel(aStr)								strdup(aStr)
#if defined(LINUX) || defined(MEEGO) || defined(IOS)
	#define KPTMemStrDupWRel(aStr)								wcsdup(aStr)
#else
	#define KPTMemStrDupWRel(aStr)								strdup(aStr)
#endif
	#define KPTMemCheckAllMemoryRel()							KPT_NOP_FUNCTION
	#define KPTMemEnterScopeRel()								KPT_NOP_FUNCTION
	#define KPTMemLeaveScopeRel()								KPT_NOP_FUNCTION

	#define KPTMemStartupDbg(ptr, aFile, aLine)					KPT_NOP_FUNCTION
	#define KPTMemShutdownDbg(ptr, aFile, aLine)				KPT_NOP_FUNCTION
	#define KPTMemCallocDbg(aNum, aSize, aFile, aLine)			calloc(aNum, aSize)
	#define KPTMemFreeDbg(aMemblock, aFile, aLine)				free(aMemblock)
	#define KPTMemMallocDbg(aSize, aFile, aLine)				malloc(aSize)
	#define KPTMemReallocDbg(aMemblock, aSize, aFile, aLine)	realloc(aMemblock, aSize)
	#define KPTMemStrDupNDbg(aStr, aFile, aLine)				strdup(aStr)
#if defined(LINUX) || defined(MEEGO) || defined(IOS)
	#define KPTMemStrDupWDbg(aStr, aFile, aLine)				wcsdup(aStr)
#else
	#define KPTMemStrDupWDbg(aStr, aFile, aLine)				strdup(aStr)
#endif
	#define KPTMemCheckAllMemoryDbg(aFile, aLine)				KPT_NOP_FUNCTION
	#define KPTMemEnterScopeDbg(aFile, aLine)					KPT_NOP_FUNCTION
	#define KPTMemLeaveScopeDbg(aFile, aLine)					KPT_NOP_FUNCTION

	#define KPTMemStartup(ptr)									KPT_NOP_FUNCTION
	#define KPTMemShutdown(ptr)									KPT_NOP_FUNCTION
	#define KPTMemCalloc(aNum, aSize)							calloc(aNum, aSize)
	#define KPTMemFree(aMemblock)								free(aMemblock)
	#define KPTMemMalloc(aSize)									malloc(aSize)
	#define KPTMemRealloc(aMemblock, aSize)						realloc(aMemblock, aSize)
	#define KPTMemStrDupN(aStr)									strdup(aStr)
#if defined(LINUX) || defined(MEEGO) || defined(IOS)
	#define KPTMemStrDupW(aStr)									wcsdup(aStr)
#else
	#define KPTMemStrDupW(aStr)									strdup(aStr)
#endif
	#define KPTMemCheckAllMemory()								KPT_NOP_FUNCTION
	#define KPTMemEnterScope()									KPT_NOP_FUNCTION
	#define KPTMemLeaveScope()									KPT_NOP_FUNCTION

#endif /* #elif defined(KPTMEM_USE_RELEASE) */

KPT_LIB_SYSMEM
KPTResultT
KPT_CALL
KPTMemCopy(void* aDest,
           size_t aDestBytes,
           const void* aSource,
           size_t aSourceBytes);

KPT_LIB_SYSMEM
KPTResultT
KPT_CALL
KPTMemMove(void* aDest,
           size_t aDestBytes,
           const void* aSource,
           size_t aSourceBytes);

KPT_LIB_SYSMEM
KPTResultT
KPT_CALL
KPTMemCompare(const void* aBuffer1,
              const void* aBuffer2,
              size_t aBytes,
              int* aCompare);

KPT_LIB_SYSMEM
KPTResultT
KPT_CALL
KPTMemZero(void* aDest,
           size_t aBytes);

KPT_LIB_SYSMEM
KPTResultT
KPT_CALL
KPTMemSet(void* aDest,
          int aValue,
          size_t aBytes);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTMEMORY_H */
