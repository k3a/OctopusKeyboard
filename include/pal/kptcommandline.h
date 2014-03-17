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
 * @file    kptcommandline.h
 *
 * @author  Patrick O'Neill
 *
 * @details Handling command-line arguments is a commonly repeated task. This
 *          file declares interfaces for support functions.
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTCOMMANDLINE_H
#define H_KPTCOMMANDLINE_H

#include "kpttextfile.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct KPTCommandArgumentT KPTCommandArgumentT;
/**
 * A structure to define a single, parsed, command line argument.
 */
struct KPTCommandArgumentT
{
	KPTSysCharT option;        /**< The option found in the string, 0 if not found */
	const KPTSysCharT* key;    /**< The key part, or whole part of an option argument */
	size_t keyLength;          /**< The length of the key */
	const KPTSysCharT* value;  /**< The value part of an option argument */
	size_t valueLength;        /**< The length of the value */
};

typedef struct KPTCommandInputT KPTCommandInputT;
/**
 * Input for a command option callback.
 */
struct KPTCommandInputT
{
	KPTCommandArgumentT argument;   /**< Argument details */
	KPTBoolT parsed;                /**< True if parsed successfully */
	int index;                      /**< Argument index, or line number */
	const KPTSysCharT* source;      /**< Source text for option */
	void* userContext;              /**< User supplied context */
};

/**
 * Callback function for handling command line options
 *
 * @param[in] aInput    The command to handle
 * @return              KPTRESULT_SUCCESS to continue parsing, any other value to stop.
 */
typedef KPTResultT (KPT_CALLB *KPTCommandLineCallbackT) (const KPTCommandInputT* aInput);

KPT_LIB_SYSTEM
KPTBoolT
KPT_CALL
KPTCommandLineParseArg(const KPTSysCharT* aSource,
                       KPTCommandArgumentT* aArgument);

KPT_LIB_SYSTEM
KPTBoolT
KPT_CALL
KPTCommandLineSplitArg(KPTSysCharT* aSource,
                       KPTCommandArgumentT* aArgument);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTCommandLineParseFile(KPTCommandLineCallbackT aCallback,
                        void* aContext,
                        const KPTSysCharT* aPath);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTCommandLineParseArgs(KPTCommandLineCallbackT aCallback,
                        void* aContext,
                        int aFirst,
                        int aArgC,
                        KPTSysCharT* aArgV[],
                        KPTBoolT aSplit);

KPT_LIB_SYSTEM
KPTBoolT
KPT_CALL
KPTCommandLineGetUint32(const KPTSysCharT* aText,
                       uint32_t* aValue,
                       uint32_t aDefault);

KPT_LIB_SYSTEM
KPTBoolT
KPT_CALL
KPTCommandLineGetInt32(const KPTSysCharT* aText,
                       int32_t* aValue,
                       int32_t aDefault);

KPT_LIB_SYSTEM
KPTBoolT
KPT_CALL
KPTCommandLineGetBool(const KPTSysCharT* aText,
                      KPTBoolT* aValue,
                      KPTBoolT aDefault);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* H_KPTCOMMANDLINE_H */
