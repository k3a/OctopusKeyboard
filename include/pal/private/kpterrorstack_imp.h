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
 * @file    kpterrorstack.h
 * 
 * @brief   Private implementation structure for the errorstack mechanism.
 *
 * @details 
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTERRORSTACK_IMP_H
#define H_KPTERRORSTACK_IMP_H

#include "kptlibsystem.h"
#include "kptapi.h"
#include "kpterrorstack.h"
#include "kptcritsection.h"
#include "kptout.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** 
 * A single item in the error stack.
 */
typedef struct KPTErrorStackInternalT KPTErrorStackInternalT;
struct KPTErrorStackInternalT
{
	KPTErrorStackDetailsT data; /**< details for the error */
	uint32_t id;                /**< sequential identifier */
};

/** Output categories for error stack */
#ifndef KPT_CAT_ERRORSTACK
	#define KPT_CAT_ERRORSTACK	KPT_LIBSYSTEM_CATEGORY
#endif

/** Maximum depth of error stack */
#ifndef KPTERRORSTACK_MAXDEPTH
	#define KPTERRORSTACK_MAXDEPTH 64
#endif

/** 
 * Private implementation of KPTErrorStack.
 */
struct KPTErrorStackT
{
	/* Shared values */
	KPTHeapT* heap;     /**< Heap that created the stack. */
	KPTOutT* out;       /**< The output mechanism for this stack, NULL = default. */
	size_t maxDepth;    /**< Size of the internal stack. */
	size_t count;       /**< Number of items in the internal stack. */
	size_t options;     /**< KPTErrorStackOptionsT. */
	KPTBoolT enabled;   /**< Enabled state. */
	uint32_t nextId;    /**< Identifier for next item on stack. */
	KPTCriticalSectionT* criticalSection;	/**< Thread safety. */

	/* Stack array, 0 is the bottom */
	KPTErrorStackInternalT stack[1];
};


#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTERRORSTACK_IMP_H */
