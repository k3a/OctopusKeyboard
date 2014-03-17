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
 * @file    kptapi_output.h
 *
 * @brief   Output types and structures.
 *
 * @details
 *  
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "kptout.h"
#include "kpttime.h"

#ifndef H_KPTAPI_OUTPUT_H
#define H_KPTAPI_OUTPUT_H


/** Logging functions provided by the Framework components */
enum KPTOutBuiltInTypeT
{
	eKPTOutBuiltInDefault = KPTBIT(0),  /**< Default output mechanism. */
	eKPTOutBuiltInConsole = KPTBIT(1),  /**< Output to a console. */
	eKPTOutBuiltInFileText = KPTBIT(2)  /**< Output to a text log file. */
};
typedef enum KPTOutBuiltInTypeT KPTOutBuiltInTypeT;

/**
 * Function pointer for all output callbacks.
 *
 * @param[in] aOut      Text information to output
 * @param[in] aContext  User provided information associated with the callback.
 * @return              KPTResultT.
 */
typedef KPTResultT (KPT_CALLB *KPTOutCallbackT)(const KPTOutTextT* aOut, intptr_t aContext);

/** Custom Callback object identifier type */
typedef uint32_t KPTOutCustomIdT;


/*****************************************************************************
 * Writing
 *****************************************************************************/

/** Encapsulates information to be sent for output */
typedef struct KPTOutWriteT KPTOutWriteT;
struct KPTOutWriteT
{
	uint32_t categories;        /**< One or more categories that the information belongs to. */
	KPTResultT result;          /**< A result code which may contain component and status information. */
	const KPTSysCharT* format;  /**< The output text or the format string. */
	va_list args;               /**< An argument list if the text includes printf-style formatting. */
	KPTBoolT newLine;           /**< Append a new line to the text. */
};

/*****************************************************************************
 * Built-in output and custom callbacks
 *****************************************************************************/

/** Built-in output configuration */
typedef struct KPTOutEnableBuiltInT KPTOutEnableBuiltInT;
struct KPTOutEnableBuiltInT
{
	KPTOutBuiltInTypeT type;    /**< Type of logging. */
	intptr_t context;           /**< Data specific to the type of logging (eg filename). */
};


/** Custom output configuration */
typedef struct KPTOutAddCustomT KPTOutAddCustomT;
struct KPTOutAddCustomT
{
	KPTOutCallbackT callback;   /**< callback function pointer */
	intptr_t context;           /**< context to be passed to callback function */
};


#endif /* #ifndef H_KPTAPI_OUTPUT_H */
