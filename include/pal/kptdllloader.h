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
 * @file    kptdllloader.h
 *
 * @brief   DLL Loader.
 *
 * @details Loading DLL libraries dynamically.
 *  
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTDLLLOADER_H
#define H_KPTDLLLOADER_H

#include "kptlibsystem.h"
#include "kptapi.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus*/


DECLARE_KPTHANDLE(KPTDllHandleT)

typedef void (*KPTDllFunctionPointerT)(void);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTDllLoadLibrary(KPTDllHandleT** aModule, 
                  KPTHeapT* aHeap,
                  const KPTSysCharT* aLibraryName);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTDllFreeLibrary(KPTDllHandleT** aModule);

KPT_LIB_SYSTEM
KPTBoolT 
KPT_CALL
KPTDllLookupByOrdSupported(void);

KPT_LIB_SYSTEM
KPTBoolT 
KPT_CALL
KPTDllLookupByNameSupported(void);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTDllLookupByOrd(const KPTDllHandleT* aModule,
                  int aOrdinal,
                  KPTDllFunctionPointerT* aFunction);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTDllLookupByName(const KPTDllHandleT* aModule,
                   const KPTSysCharT* aFnName, 
                   KPTDllFunctionPointerT* aFunction);


#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* #ifndef H_KPTDLLLOADER_H*/
