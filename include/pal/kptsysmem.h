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
 * @file    kptsysmem.h
 *
 * @brief   System memory allocators
 *
 * @details This is an abstract interface for external memory libraries.
 * 
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTSYSMEM_H
#define H_KPTSYSMEM_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* release interface */
KPT_LIB_SYSMEM
void
KPT_CALL
KPTSysMemStartupRel(void* aReserved);

KPT_LIB_SYSMEM
void
KPT_CALL
KPTSysMemShutdownRel(void* aReserved);

KPT_LIB_SYSMEM
void*
KPT_CALL
KPTSysMemCallocRel(size_t aNum,
                   size_t aSize);

KPT_LIB_SYSMEM
void
KPT_CALL
KPTSysMemFreeRel(void* aMemblock);

KPT_LIB_SYSMEM
void*
KPT_CALL
KPTSysMemMallocRel(size_t aSize);

KPT_LIB_SYSMEM
void*
KPT_CALL
KPTSysMemReallocRel(void* aMemblock,
                    size_t aNewsize);

KPT_LIB_SYSMEM
char*
KPT_CALL
KPTSysMemStrDupNRel(const char* aSource);

KPT_LIB_SYSMEM
wchar_t*
KPT_CALL
KPTSysMemStrDupWRel(const wchar_t* aSource);

KPT_LIB_SYSMEM
void
KPT_CALL
KPTSysMemCheckAllMemoryRel();

KPT_LIB_SYSMEM
void
KPT_CALL
KPTSysMemEnterScopeRel();

KPT_LIB_SYSMEM
void
KPT_CALL
KPTSysMemLeaveScopeRel();


/* debug interface */
KPT_LIB_SYSMEM
void
KPT_CALL
KPTSysMemStartupDbg(void* aReserved,
                    const char* aFile,
                    int aLine);

KPT_LIB_SYSMEM
void
KPT_CALL
KPTSysMemShutdownDbg(void* aReserved,
                     const char* aFile,
                     int aLine);

KPT_LIB_SYSMEM
void*
KPT_CALL
KPTSysMemCallocDbg(size_t aNum,
                   size_t aSize,
                   const char* aFile,
                   int aLine);

KPT_LIB_SYSMEM
void
KPT_CALL
KPTSysMemFreeDbg(void* aMemblock,
                 const char* aFile,
                 int aLine);

KPT_LIB_SYSMEM
void*
KPT_CALL
KPTSysMemMallocDbg(size_t aSize,
                   const char* aFile,
                   int aLine);

KPT_LIB_SYSMEM
void* 
KPT_CALL
KPTSysMemReallocDbg(void* aMemblock,
                    size_t aNewsize,
                    const char* aFile,
                    int aLine);

KPT_LIB_SYSMEM
char*
KPT_CALL
KPTSysMemStrDupNDbg(const char* aSource,
                    const char* aFile,
                    int aLine);

KPT_LIB_SYSMEM
wchar_t*
KPT_CALL
KPTSysMemStrDupWDbg(const wchar_t* aSource,
                    const char* aFile,
                    int aLine);

KPT_LIB_SYSMEM
void
KPT_CALL
KPTSysMemCheckAllMemoryDbg(const char* aFile,
                           int aLine);

KPT_LIB_SYSMEM
void
KPT_CALL
KPTSysMemEnterScopeDbg(const char* aFile,
                       int aLine);

KPT_LIB_SYSMEM
void
KPT_CALL
KPTSysMemLeaveScopeDbg(const char* aFile,
                       int aLine);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTSYSMEM_H */
