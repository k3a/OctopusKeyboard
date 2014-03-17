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
 * @file    kptpal.h
 *
 * @brief   Global settings for the Platform Abstraction Layer.
 *
 * @details 
 *  
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTPAL_H
#define H_KPTPAL_H

#include "kptlibsystem.h"
#include "kptapi.h"
#include "kptheap.h"
#include "kptout.h"
#include "kpterrorstack.h"
#include "kptunicodetable.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

DECLARE_KPTHANDLE(KPTPalT)

/**
 * Startup options for the PAL.
 */
enum KPTPalStartupT
{
	eKPTPalInitOutput = KPTBIT(0),      /**< Initialise the output object */
	eKPTPalInitErrorStack = KPTBIT(1),  /**< Initialise the error object */
	eKPTPalDefaultOut = KPTBIT(2),      /**< Add the default output */
	eKPTPalConsoleOut = KPTBIT(3),      /**< Add console output */
	eKPTPalLogTextOut = KPTBIT(4),      /**< Add log output, using logfile member */
};
typedef enum KPTPalStartupT KPTPalStartupT;

typedef struct KPTPalStartupSettingsT KPTPalStartupSettingsT;
/** Startup settings for the PAL. */
struct KPTPalStartupSettingsT
{
	uint32_t version;                       /**< Version of the structure */
	uint32_t startupOptions;                /**< KPTPalStartupT Options */
	uint32_t outputOptions;                 /**< KPTOutT options */
	uint32_t outputDetail;                  /**< KPTCAT_ options */
	uint32_t errorOptions;                  /**< KPTErrorStackT options */
	size_t outputBufferSize;                /**< Number of characters in output buffer */
	size_t errorStackDepth;                 /**< Size of error stack */
	const KPTSysCharT* logFile;             /**< Text log file */
	const KPTSysCharT* applicationDirPath;  /**< application directory path. needed for android only*/ 
	const KPTSysCharT* tempDirPath;         /**< temporaray directory path. needed for android only*/
	KPTHeapConfigParamsT* heapConfig;       /**< Configuration for PAL heap */
};

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTPalCreateEnvironment(KPTPalStartupSettingsT* aSettings);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTPalDestroyEnvironment();

KPT_LIB_SYSTEM
KPTHeapT*
KPT_CALL
KPTPalGetDefaultHeap();

KPT_LIB_SYSTEM
KPTOutT*
KPT_CALL
KPTPalGetDefaultOut();

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTPalSetDefaultOut(KPTOutT* aNew,
                    KPTOutT** aPrevious);

KPT_LIB_SYSTEM
KPTErrorStackT*
KPT_CALL
KPTPalGetDefaultErrorStack();


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTPalSetDefaultErrorStack(KPTErrorStackT* aNew,
                           KPTErrorStackT** aPrevious);

KPT_LIB_SYSTEM
KPTBoolT
KPT_CALL
KPTPalIsLittleEndian();

KPT_LIB_SYSTEM
KPTBoolT
KPT_CALL
KPTPalIsBigEndian();

KPT_LIB_SYSTEM
const KPTUniCharT*
KPT_CALL
KPTPalGetNewLine();

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTPalSetEnvironment(KPTPalT* aEnvironment);

KPT_LIB_SYSTEM
KPTPalT*
KPT_CALL
KPTPalGetEnvironment(void);


#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTPAL_H */
