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
 * @file    kpttextfilecharconverter.h
 *
 * @brief   Interface to character conversion code.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTTEXTFILECHARCONVERTER_H
#define H_KPTTEXTFILECHARCONVERTER_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Number of bytes required to identify a utf8 character */
#define KPT_UTF8_MAX_BYTES 4

/* Converting from one encoding to another may generate an
   increase in number of datums - this will be big enough
*/
#define KPT_UTF_CONVERT_OUT_SIZE 5

KPTResultT KPTConvertUTF8toUTF16(const KPTUtf8CharT** aSourceStart, 
                                 const KPTUtf8CharT* aSourceEnd, 
                                 KPTUtf16CharT** aDestStart, 
                                 KPTUtf16CharT* aDestEnd, 
                                 KPTBoolT aStrict);

KPTResultT KPTConvertUTF16toUTF8(const KPTUtf16CharT** aSourceStart, 
                                 const KPTUtf16CharT* aSourceEnd,
                                 KPTUtf8CharT** aDestStart, 
                                 KPTUtf8CharT* aDestEnd, 
                                 KPTBoolT aStrict);

KPTResultT KPTConvertUTF8toUTF32(const KPTUtf8CharT** aSourceStart, 
                                 const KPTUtf8CharT* aSourceEnd, 
		                         KPTUtf32CharT** aTargetStart, 
                                 KPTUtf32CharT* aTargetEnd, 
                                 KPTBoolT aStrict);

KPTResultT KPTConvertUTF32toUTF8(const KPTUtf32CharT** aSourceStart, 
                                 const KPTUtf32CharT* aSourceEnd, 
		                         KPTUtf8CharT** aTargetStart, 
                                 KPTUtf8CharT* aTargetEnd, 
                                 KPTBoolT aStrict);
		
KPTResultT KPTConvertUTF16toUTF32(const KPTUtf16CharT** aSourceStart, 
                                  const KPTUtf16CharT* aSourceEnd, 
		                          KPTUtf32CharT** aTargetStart, 
                                  KPTUtf32CharT* aTargetEnd, 
                                  KPTBoolT aStrict);

KPTResultT KPTConvertUTF32toUTF16(const KPTUtf32CharT** aSourceStart, 
                                  const KPTUtf32CharT* aSourceEnd, 
		                          KPTUtf16CharT** aTargetStart, 
                                  KPTUtf16CharT* aTargetEnd, 
                                  KPTBoolT aStrict);


KPTBoolT IsLegalUTF8(const KPTUtf8CharT* aSource, 
                     size_t aLength);

/*
made publicly available as required by bom code
*/
const char* KPTConvertGetUTF8TrailingBytesTable();


#ifdef __cplusplus
}
#endif

#endif /* H_KPTTEXTFILECHARCONVERTER_H */
