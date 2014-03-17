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
 * @file    kpterr.h
 *
 * @brief   Simplified error interface for the default PAL errorstack.
 *
 * @details This file provides wrapper functions and macros for use inside 
 *          the PAL libraries. These will simplify pushing errors onto
 *          the error stack, or disabling stack support altogether.
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTERR_H
#define H_KPTERR_H

#include "kptlibsystem.h"
#include "kptapi.h"
#include "kpterrorstack.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrClear();

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrGetCount(size_t* aCount);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrEnable(KPTBoolT aNew,
             KPTBoolT* aPrevious);

KPT_LIB_SYSTEM
KPTBoolT
KPT_CALL
KPTErrIsEnabled();

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrPop(KPTErrorStackItemT* aError);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrRelease(KPTErrorStackItemT* aError);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrPushRel(KPTResultT aResult,
              int aLine);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrPushOSRel(KPTResultT aResult,
                uint32_t aOS,
                int aLine);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrPushText1Rel(KPTResultT aResult,
                   const KPTSysCharT* aText1,
                   int aLine);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrPushText2Rel(KPTResultT aResult,
                   const KPTSysCharT* aText1,
                   const KPTSysCharT* aText2,
                   int aLine);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrPushDbg(KPTResultT aResult,
              int aLine,
              const char* aFile);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrPushOSDbg(KPTResultT aResult,
                uint32_t aOS,
                int aLine,
                const char* aFile);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrPushText1Dbg(KPTResultT aResult,
                   const KPTSysCharT* aText1,
                   int aLine,
                   const char* aFile);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTErrPushText2Dbg(KPTResultT aResult,
                   const KPTSysCharT* aText1,
                   const KPTSysCharT* aText2,
                   int aLine,
                   const char* aFile);

/**
 * \def KPTERR_PUSH(aResult)
 * Pushes a result code on to the default error stack.
 */

/**
 * \def KPTERR_PUSHOS(aResult, aOS)
 * Pushes a result code and OS code on to the default error stack.
 */

/**
 * \def KPTERR_PUSHTEXT1(aResult, aText)
 * Pushes a result code and text string on to the default error stack.
 */

/**
 * \def KPTERR_PUSHTEXT2(aResult, aText1, aText2)
 * Pushes a result code and two text strings on to the default error stack.
 */

/**
 * \def KPTERR_PUSH_ERROR(aCC, aSC)
 * Creates an error result code from component and status codes.
 * Pushes result code on to the default error stack.
 */

/**
 * \def KPTERR_PUSHOS_ERROR(aCC, aSC, aOS)
 * Creates an error result code from component and status codes.
 * Pushes result code and OS code on to the default error stack.
 */

/**
 * \def KPTERR_PUSHTEXT1_ERROR(aCC, aSC, aText)
 * Creates an error result code from component and status codes.
 * Pushes result code and text string on to the default error stack.
 */

/**
 * \def KPTERR_PUSHTEXT2_ERROR(aCC, aSC, aText1, aText2)
 * Creates an error result code from component and status codes.
 * Pushes result code and two text strings on to the default error stack.
 */

/**
 * \def KPTERR_MODE
 * Defines the operating mode for the stack KPTERR_PUSH macros.
 * \li 0 = Disabled, do not push anything
 * \li 1 = Release mode, push error, but no file information
 * \li 2 = Debug mode, push error and file location
 */

/** Set the detail level for the stack */
#ifndef KPTERR_MODE
	#ifdef NDEBUG
		#define KPTERR_MODE 1
	#else
		#define KPTERR_MODE 2
	#endif
#endif

#if KPTERR_MODE == 1

	#define KPTERR_PUSH(aResult) \
			KPTErrPushRel(aResult, KPTLINE)

	#define KPTERR_PUSHOS(aResult, aOS) \
			KPTErrPushOSRel(aResult, aOS, KPTLINE)

	#define KPTERR_PUSHTEXT1(aResult, aText) \
			KPTErrPushText1Rel(aResult, aText, KPTLINE)

	#define KPTERR_PUSHTEXT2(aResult, aText1, aText2) \
			KPTErrPushText2Rel(aResult, aText1, aText2, KPTLINE)

#elif KPTERR_MODE == 2

	#define KPTERR_PUSH(aResult) \
			KPTErrPushDbg(aResult, KPTLINE, KPTLOC)

	#define KPTERR_PUSHOS(aResult, aOS) \
			KPTErrPushOSDbg(aResult, aOS, KPTLINE, KPTLOC)

	#define KPTERR_PUSHTEXT1(aResult, aText) \
			KPTErrPushText1Dbg(aResult, aText, KPTLINE, KPTLOC)

	#define KPTERR_PUSHTEXT2(aResult, aText1, aText2) \
			KPTErrPushText2Dbg(aResult, aText1, aText2, KPTLINE, KPTLOC)

#else

	#define KPTERR_PUSH(aResult)  (aResult)

	#define KPTERR_PUSHOS(aResult, aOS)  (aResult)

	#define KPTERR_PUSHTEXT1(aResult, aText)  (aResult)

	#define KPTERR_PUSHTEXT2(aResult, aText1, aText2)  (aResult)

#endif

#define KPTERR_PUSH_ERROR(aCC, aSC) KPTERR_PUSH(KPTRESULT_ERROR(aCC, aSC))

#define KPTERR_PUSHOS_ERROR(aCC, aSC, aOS) KPTERR_PUSHOS(KPTRESULT_ERROR(aCC, aSC), aOS)

#define KPTERR_PUSHTEXT1_ERROR(aCC, aSC, aText) KPTERR_PUSHTEXT1(KPTRESULT_ERROR(aCC, aSC), aText)

#define KPTERR_PUSHTEXT2_ERROR(aCC, aSC, aText1, aText2) KPTERR_PUSHTEXT2(KPTRESULT_ERROR(aCC, aSC), aText1, aText2)

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTERR_H */

