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
 * @file    kpttimer.h
 *
 * @brief   System timer interface.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTTIMER_H
#define H_KPTTIMER_H

#include "kptlibsystem.h"
#include "kptapi.h"
#include "kptheap.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* timer */
DECLARE_KPTHANDLE(KPTTimerT)

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTimerCreate(KPTTimerT** aHandle,
               KPTHeapT* aHeap);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTimerDestroy(KPTTimerT** aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTimerStart(KPTTimerT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTimerStop(KPTTimerT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTimerReset(KPTTimerT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTimerIsRunning(const KPTTimerT* aHandle,
                  KPTBoolT* aIsRunning);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTimerGetElapsed(const KPTTimerT* aHandle,
                   double* aSeconds);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTimerGetResolution(const KPTTimerT* aHandle,
                      double* aSeconds);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTTIMER_H */
