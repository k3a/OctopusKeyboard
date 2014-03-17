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
 * @file    kptformat.h
 *
 * @brief   Printf-style formatting functions.
 *
 * @details
 * 
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTFORMAT_H
#define H_KPTFORMAT_H

#include "kptlibsystem.h"
#include "kptapi.h"
#include "kptfmtspec.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


KPT_LIB_SYSTEM
size_t
KPT_CALL 
KPTFormatVN(char* aOut,
            size_t aBufferSize,
            const char* aFormatString,
            va_list aArgptr);

KPT_LIB_SYSTEM
size_t
KPT_CALLV
KPTFormatN(char* out,
           size_t aBufferSize,
           const char* aFormatString,
           ...);

KPT_LIB_SYSTEM
size_t
KPT_CALL 
KPTFormatVW(wchar_t* aOut,
            size_t aBufferSize,
            const wchar_t* aFormatString,
            va_list aArgptr);

KPT_LIB_SYSTEM
size_t
KPT_CALLV
KPTFormatW(wchar_t* out,
           size_t aBufferSize,
           const wchar_t* aFormatString,
           ...);


/**
 * \def KPTFormatVS
 * vprintf-style format function for KPTSysCharT.
 */

/**
 * \def KPTFormatS
 * printf-style format function for KPTSysCharT.
 */

#if KPT_TSYSCHAR_ISWIDE

#define KPTFormatVS KPTFormatVW
#define KPTFormatS KPTFormatW

#else

#define KPTFormatVS KPTFormatVN
#define KPTFormatS KPTFormatN

#endif


#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* H_KPTFORMAT_H */
