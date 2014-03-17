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
 * @file    kptcritsection.h
 *
 * @brief   Support for a platform idependent critical section.
 *
 * @details 
 *  
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTCRITSECTION_H
#define H_KPTCRITSECTION_H

#include "kptlibsystem.h"
#include "kptapi.h"
#include "kptheap.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

DECLARE_KPTHANDLE(KPTCriticalSectionT)

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTCriticalSectionCreate(KPTCriticalSectionT** aHandle,
                         KPTHeapT* aHeap);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTCriticalSectionDestroy(KPTCriticalSectionT** aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTCriticalSectionLock(KPTCriticalSectionT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTCriticalSectionTryLock(KPTCriticalSectionT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTCriticalSectionUnlock(KPTCriticalSectionT* aHandle);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTCRITSECTION_H */
