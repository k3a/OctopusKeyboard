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
 * @file    kptglobal.h
 * 
 * @brief   Internal header file to retrieve global instances.
 *
 * @details
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_GLOBAL_H
#define H_GLOBAL_H

#include <f32file.h>

/* Defines to convert uint to TPtr */
#define SYMBIAN_STR_8(symStr, str, length, maxLength)  TPtr8  symStr((TUint8 *) (str), (length), (maxLength))
#define SYMBIAN_STR_EMPTY_8(symStr, str, maxLength)  TPtr8  symStr((TUint8 *)(str), 0, (maxLength))
#define SYMBIAN_STR_16(symStr, str, length, maxLength) TPtr16 symStr((TUint16 *)(str), (length), (maxLength))

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

KPT_LIB_SYSTEM
RFs&
KPT_CALL
KPTPalGetFileServer();

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTSYMBIAN_GLOBAL_H */
