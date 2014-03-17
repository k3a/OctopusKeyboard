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
 * @file    kpterrorstack.h
 *
 * @brief   Error stack interface.
 *
 * @details 
 *  
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTERRORSTACK_H
#define H_KPTERRORSTACK_H

#include "kptlibsystem.h"
#include "kptapi.h"
#include "kptheap.h"
#include "kptout.h"
#include "kpttime.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

DECLARE_KPTHANDLE(KPTErrorStackT)

/** Error details */
typedef struct KPTErrorStackDetailsT KPTErrorStackDetailsT;
struct KPTErrorStackDetailsT
{
	uint32_t os;                /**< os code */
	KPTResultT result;          /**< result */
	const KPTSysCharT* text1;   /**< text info, may be NULL */
	const KPTSysCharT* text2;   /**< text info, may be NULL */
	const char* file;           /**< file where error occured, may be NULL */
	int line;                   /**< line number */
};

/** Access structure for the error stack */
typedef struct KPTErrorStackItemT KPTErrorStackItemT;
struct KPTErrorStackItemT
{
	KPTTimeT time;              /**< timestamp (to be decided) */
	KPTErrorStackT* stack;      /**< source */
	uint32_t id;                /**< sequential identifier */
	KPTErrorStackDetailsT data; /**< details for the error */
};

/** Error stack creation options */
enum KPTErrorStackOptionsT
{
	eKPTErrorStackSequential = KPTBIT(0),   /* Thread safe */
	eKPTErrorStackEnabled = KPTBIT(1),      /* Enabled state */
	eKPTErrorStackOutput = KPTBIT(2)        /* Output items added to the stack */
};
typedef enum KPTErrorStackOptionsT KPTErrorStackOptionsT;


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrorStackCreate(KPTErrorStackT** aHandle,
                    KPTHeapT* aHeap,
                    KPTOutT* aOut,
                    size_t aMaxDepth,
                    uint32_t aOptions);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrorStackDestroy(KPTErrorStackT** aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrorStackClear(KPTErrorStackT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrorStackGetCount(const KPTErrorStackT* aHandle,
                      size_t* aCount);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrorStackEnable(KPTErrorStackT* aHandle,
                    KPTBoolT aNew,
                    KPTBoolT* aPrevious);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrorStackIsEnabled(const KPTErrorStackT* aHandle,
                       KPTBoolT* aEnabled);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrorStackPopError(KPTErrorStackT* aHandle,
                      KPTErrorStackItemT* aError);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrorStackReleaseError(KPTErrorStackItemT* aError);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrorStackPushRel(KPTErrorStackT* aHandle,
                     KPTResultT aResult,
                     int aLine);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrorStackPushOSRel(KPTErrorStackT* aHandle,
                       KPTResultT aResult,
                       uint32_t aOS,
                       int aLine);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrorStackPushText1Rel(KPTErrorStackT* aHandle,
                          KPTResultT aResult,
                          const KPTSysCharT* aText1,
                          int aLine);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrorStackPushText2Rel(KPTErrorStackT* aHandle,
                          KPTResultT aResult,
                          const KPTSysCharT* aText1,
                          const KPTSysCharT* aText2,
                          int aLine);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrorStackPushDbg(KPTErrorStackT* aHandle,
                     KPTResultT aResult,
                     int aLine,
                     const char* aFile);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrorStackPushOSDbg(KPTErrorStackT* aHandle,
                       KPTResultT aResult,
                       uint32_t aOS,
                       int aLine,
                       const char* aFile);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrorStackPushText1Dbg(KPTErrorStackT* aHandle,
                          KPTResultT aResult,
                          const KPTSysCharT* aText1,
                          int aLine,
                          const char* aFile);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrorStackPushText2Dbg(KPTErrorStackT* aHandle,
                          KPTResultT aResult,
                          const KPTSysCharT* aText1,
                          const KPTSysCharT* aText2,
                          int aLine,
                          const char* aFile);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTERRORSTACK_H */
