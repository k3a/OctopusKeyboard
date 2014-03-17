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
 * @file    kptthread.h
 *
 * @brief   Platform Independent Thread Handling API's.
 *
 * @details.
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTTHREAD_H
#define H_KPTTHREAD_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "kptlibsystem.h"
#include "kptapi.h"
#include "kptheap.h"

/** Platform independent Thread Attributes */
DECLARE_KPTHANDLE(KPTThreadAttribT)

/** Thread State that tells wether thread is joinable/detached */
enum KPTThreadStateT
{
	eKPTThreadStateJoin,        /**< Joinable thread - will wait */
	eKPTThreadStateDetached     /**< Un joinable thread - detachable - wont wait */
};
typedef enum KPTThreadStateT KPTThreadStateT;

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTThreadAttribCreate(KPTThreadAttribT** aAttributes,
                      KPTHeapT* aHeap);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTThreadAttribDestroy(KPTThreadAttribT** aAttributes);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTThreadAttribGetStackSize(KPTThreadAttribT* aAttributes,
                            size_t* aStackSize);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTThreadAttribSetStackSize(KPTThreadAttribT* aAttributes,
                            size_t aStackSize);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTThreadAttribGetState(KPTThreadAttribT* aAttributes,
                        KPTThreadStateT* aState);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTThreadAttribSetState(KPTThreadAttribT* aAttributes,
                        KPTThreadStateT aState);



/** Thread Handle */
DECLARE_KPTHANDLE(KPTThreadT)


/** Platform independent identifier */
typedef intptr_t KPTThreadIdentifierT;

/** Platform independent thread parameters */
typedef intptr_t KPTThreadParamT;

/** Platform independent Thread Routine */
typedef KPTResultT (KPT_CALLB *KPTThreadRoutineT)(KPTThreadParamT aParam);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTThreadCreate(KPTThreadT** aThread,
                KPTHeapT* aHeap,
                KPTThreadAttribT* aAttributes,
                KPTThreadRoutineT aRoutine,
                KPTThreadParamT aParam);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTThreadDestroy(KPTThreadT** aThread);

KPT_LIB_SYSTEM
KPTBoolT
KPT_CALL
KPTThreadIsRunning(KPTThreadT* aThread,
                   KPTResultT* aThreadResult);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTThreadWait(KPTThreadT* aThread,
              KPTResultT* aThreadResult);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTThreadGetId(KPTThreadT* aThread,
               KPTThreadIdentifierT* aIdentifier);


KPT_LIB_SYSTEM
void
KPT_CALL
KPTThreadCurrentSleep(uint32_t aMilliseconds);

KPT_LIB_SYSTEM
KPTThreadIdentifierT
KPT_CALL
KPTThreadCurrentGetId();

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTTHREAD_H */
