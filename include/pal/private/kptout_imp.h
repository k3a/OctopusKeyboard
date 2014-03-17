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
 * @file    kptout_imp.h
 * 
 * @brief   Private implementation structure for the output mechanism.
 *
 * @details 
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTOUT_IMP_H
#define H_KPTOUT_IMP_H

#include "kptlibsystem.h"
#include "kptapi.h"
#include "kptheap.h"
#include "kptout.h"
#include "kptcritsection.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Maximum number of outputs in a KPTOut implementation */
#ifndef KPTOUT_MAXOUTARRAY
#define KPTOUT_MAXOUTARRAY      10
#endif

/** Maximum number of filters in a KPTOut implementation */
#ifndef KPTOUT_MAXFILTERARRAY
#define KPTOUT_MAXFILTERARRAY   10
#endif

/** Minimum number of system characters in an KPTOutT internal buffer */
#ifndef KPTOUT_MINBUFFERSIZE
#define KPTOUT_MINBUFFERSIZE    512
#endif

/** Maximum number of system characters in an KPTOutT internal buffer */
#ifndef KPTOUT_MAXBUFFERSIZE
#define KPTOUT_MAXBUFFERSIZE    4096
#endif

/** A storage item identifying a callback with an id and the filter/output type. */
typedef struct KPTOutCBItemT KPTOutCBItemT;
struct KPTOutCBItemT
{
	uint32_t id;                /**< Unique id for item */
	KPTOutCBTypeT type;         /**< Type of item, output or filter */
	KPTOutCallbackT callback;   /**< Callback function */
	intptr_t context;           /**< Context associated with callback function */
};


/** Private implementation of KPTOut for Windows */
struct KPTOutT
{
	/* Shared values */
	KPTHeapT* heap;                         /**< Heap that created the output. */
	size_t bufferSize;                      /**< Size of the formatting buffer. */
	uint32_t categories;                    /**< KPTCAT_ settings. */
	uint32_t options;                       /**< KPTOutInfoT. */
	uint32_t indent;                        /**< Indentation level. */
	KPTCriticalSectionT* criticalSection;   /**< Thread safety. */

	KPTOutCBItemT outCallbacks[KPTOUT_MAXOUTARRAY]; /**< Output callbacks. */
	size_t outCount;    /**< Number of output callbacks. */

	KPTOutCBItemT filterCallbacks[KPTOUT_MAXFILTERARRAY]; /**< Filter callbacks. */
	size_t filterCount; /**< Number of filter callbacks. */

	/* Buffer */
	KPTSysCharT buffer[1];
};

/* Internal, platform specific functions, for console output*/
KPTResultT
KPT_CALLB
KPTOutCreateConsole(intptr_t* aContext);

KPTResultT
KPT_CALLB
KPTOutDestroyConsole(intptr_t* aContext);

KPTResultT
KPT_CALLB
KPTOutCallbackConsole(const KPTOutTextT* aText,
                      intptr_t aContext);

/* Internal, platform specific functions, for default output */
KPTResultT
KPT_CALLB
KPTOutCreateDefault(intptr_t* aContext);

KPTResultT
KPT_CALLB
KPTOutDestroyDefault(intptr_t* aContext);

KPTResultT
KPT_CALLB
KPTOutCallbackDefault(const KPTOutTextT* aText,
                      intptr_t aContext);


/* Internal, platform specific functions, for text log output */
KPTResultT
KPT_CALLB
KPTOutCreateFileText(intptr_t* aContext,
                     const KPTSysCharT* aFileName);

KPTResultT
KPT_CALLB
KPTOutDestroyFileText(intptr_t* aContext);

KPTResultT
KPT_CALLB
KPTOutCallbackFileText(const KPTOutTextT* aText,
                       intptr_t aContext);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTOUT_IMP_H */
