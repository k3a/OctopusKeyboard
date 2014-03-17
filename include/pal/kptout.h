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
 * @file    kptout.h
 *
 * @brief   Interface for platform independent output mechanism.
 *
 * @details 
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTOUT_H
#define H_KPTOUT_H

#include "kptlibsystem.h"
#include "kptapi.h"
#include "kptheap.h"
#include "kpttime.h"
#include "kptfmtspec.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Structure that defines the information that will be output.
 */
typedef struct KPTOutTextT KPTOutTextT;
struct KPTOutTextT
{
	uint32_t info;               /**< see KPTOutInfoT below */
	KPTResultT result;           /**< Severity, Component and Code */
	uint32_t categories;         /**< KPTCAT_ Categories */
	KPTTimeT* time;              /**< Optional time stamp */
	unsigned int indent;         /**< Indentation count */
	const KPTSysCharT* text;     /**< Output text */
};

/**
 * Enum defining the possible information to output.
 */
enum KPTOutInfoT
{
	eKPTOutInfoTime = KPTBIT(0),        /**< Add time */
	eKPTOutInfoDate = KPTBIT(1),        /**< Add date */
	eKPTOutInfoResult = KPTBIT(2),      /**< Add result */
	eKPTOutInfoNewLine = KPTBIT(3),     /**< Add a new line to the output */
	eKPTOutInfoFlush = KPTBIT(4),       /**< Flush output after each write */
	eKPTOutInfoSequential = KPTBIT(5),  /**< Enforce sequential access (Create) */
	eKPTOutInfoCategory = KPTBIT(6)     /**< Add categories */
};
typedef enum KPTOutInfoT KPTOutInfoT;

/**
 * Function pointer for all output callbacks.
 *
 * @param[in] aOut      Text information to output
 * @param[in] aContext  User provided information associated with the callback.
 * @return              KPTResultT.
 */
typedef KPTResultT (KPT_CALLB *KPTOutCallbackT)(const KPTOutTextT* aOut, intptr_t aContext);

/**
 * Enum defining the possible callback types.
 */
enum KPTOutCBTypeT
{
	eKPTOutCBDefault = 1,          /**< Default output mechanism. */
	eKPTOutCBConsole = 2,          /**< Output to a console. */
	eKPTOutCBFileText = 3,         /**< Output to a text log file. */
	eKPTOutCBCustom = 4,           /**< Callback provided by caller. */
	eKPTOutCBFilter = 5            /**< Callbacks called before any output. */
};
typedef enum KPTOutCBTypeT KPTOutCBTypeT;


/** Type that isdentifies callbackss */
typedef uint32_t KPTCallbackIdT;

/** Identifier for all callbacks functions */
#define KPTOUT_CALLBACKID_ALL (KPTCallbackIdT)(-1)


/** 
 * Outputs a conditional error message.
 */
#define KPTOUT_ERR(aGroup, aAction) (KPTCAT_ISDEFINED(aGroup, KPTCAT_ERROR)?action:0);

/** 
 * Outputs a conditional warning message.
 */
#define KPTOUT_WARN(aGroup, aAction) (KPTCAT_ISDEFINED(aGroup, KPTCAT_WARNING)?action:0);

/** 
 * Outputs a conditional information message.
 */
#define KPTOUT_INFO(aGroup, aAction) (KPTCAT_ISDEFINED(aGroup, KPTCAT_INFORMATION)?action:0);

/** 
 * Outputs a conditional debug message.
 */
#define KPTOUT_DEBUG(aGroup, aAction) (KPTCAT_ISDEFINED(aGroup, KPTCAT_DEBUG)?action:0);


/**
 * Output interface.
 */

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTOutCreate(KPTOutT** aHandle,
             KPTHeapT* aHeap,
             uint32_t aOptions,
             size_t aBufferSize);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTOutDestroy(KPTOutT** aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTOutGetOptions(const KPTOutT* aHandle,
                 uint32_t* aOptions);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTOutSetOptions(KPTOutT* aHandle,
                 uint32_t aOptions);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTOutGetCategories(const KPTOutT* aHandle,
                    uint32_t* aCategories);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTOutSetCategories(KPTOutT* aHandle,
                    uint32_t aCategories);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTOutInsertCallback(KPTOutT* aHandle,
                     KPTOutCBTypeT aType,
                     KPTOutCallbackT aCallback,
                     intptr_t aContext,
                     KPTCallbackIdT* aCallbackId);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTOutRemoveCallback(KPTOutT* aHandle,
                     KPTCallbackIdT aCallbackId);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTOutGetCallbackCounts(const KPTOutT* aHandle,
                        size_t* aFilter,
                        size_t* aFilterMax,
                        size_t* aOutput,
                        size_t* aOutputMax);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTOutGetIndent(const KPTOutT* aHandle,
                unsigned int* aLevel);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTOutSetIndent(KPTOutT* aHandle,
                unsigned int aLevel);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTOutIndent(KPTOutT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTOutUnIndent(KPTOutT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTOutWrite(KPTOutT* aHandle,
            uint32_t aCategory,
            KPTResultT aResult,
            const KPTSysCharT* aText);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTOutWriteLine(KPTOutT* aHandle,
                uint32_t aCategory,
                KPTResultT aResult,
                const KPTSysCharT* aText);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALLV
KPTOutWriteF(KPTOutT* aHandle,
             uint32_t aCategory,
             KPTResultT aResult, 
             const KPTSysCharT* aText,
             ...);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALLV
KPTOutWriteLineF(KPTOutT* aHandle,
                 uint32_t aCategory,
                 KPTResultT aResult,
                 const KPTSysCharT* aText,
                 ...);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTOutWriteV(KPTOutT* aHandle,
             uint32_t aCategory,
             KPTResultT aResult,
             const KPTSysCharT* aText,
             va_list aArgPtr);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTOutWriteLineV(KPTOutT* aHandle,
                 uint32_t aCategory,
                 KPTResultT aResult, 
                 const KPTSysCharT* aText,
                 va_list aArgPtr);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTOUT_H */
