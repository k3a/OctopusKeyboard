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
 * @file    kptapi_error.h
 *
 * @brief   Error Manager Types and Structures.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTAPI_ERROR_H
#define H_KPTAPI_ERROR_H

/**
 * Field-in-use masks for KPTErrorPopStackT::fieldMask
 */
enum KPTErrorStackPopMaskT
{
	eKPTErrorReadCodes =         KPTBIT(0),  /**< Read error codes (@ref KPTErrorDetailsT::resultCode 
                                             and @ref KPTErrorDetailsT::additionalErrorCode)*/
	eKPTErrorReadEntireString =  KPTBIT(1),  /**< Read string into KPTErrorDetailsT::errorString and
											 fail if KPTErrorDetailsT::buffLen is not large enough */
	eKPTErrorReadPartialString = KPTBIT(2),  /**< Read string into KPTErrorDetailsT::errorString and
											 truncate text if KPTErrorDetailsT::buffLen is not large enough */

	eKPTErrorReadCodesAndEntireString =  (eKPTErrorReadCodes | eKPTErrorReadEntireString), /**< eKPTErrorReadCodes | eKPTErrorReadEntireString */
	eKPTErrorReadCodesAndPartialString = (eKPTErrorReadCodes | eKPTErrorReadPartialString) /**< eKPTErrorReadCodes | eKPTErrorReadPartialString */
};
typedef enum KPTErrorStackPopMaskT KPTErrorStackPopMaskT;

/**
 * Structure containing error details
 *
 */
typedef struct KPTErrorDetailsT KPTErrorDetailsT;
struct KPTErrorDetailsT
{
	KPTResultT resultCode;          /**< Framework result code */
	uint32_t additionalErrorCode;   /**< Additional error code (eg from Operating System) */
	KPTSysCharT* errorString;       /**< String details associated with error (eg filename). NULL if not used */
	uint32_t buffLen;               /**< Length of buffer on input and length required/written on output. Includes terminating NULL character */
};


/**
 * Structure used when reading an error from the error stack
 */
typedef struct KPTErrorPopStackT KPTErrorPopStackT;
struct KPTErrorPopStackT
{
	uint32_t fieldMask;                 /**< Identifies fields in use (@ref KPTErrorStackPopMaskT)*/
	KPTErrorDetailsT errorDetails;      /**< Error details */
};

#endif /* #ifndef H_KPTAPI_ERROR_H */
