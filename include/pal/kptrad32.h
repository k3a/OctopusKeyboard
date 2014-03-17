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
 * @file    kptrad32.h
 *
 * @brief   Interface file for the rad32 algorithm.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTRAD32_H
#define H_KPTRAD32_H

#include "kptlibcode.h"
#include "kptapi.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define KPTRAD32_GETVALERROR -1
#define KPTRAD32_GETCHARERROR 255

KPT_LIB_CODE
KPTResultT
KPT_CALL
KPTRad32Convert16To(const uint16_t* aDataBuffer,
                    size_t aDataBufferSize,
                    char* aRadBuffer,
                    size_t aRadBufferSize);

KPT_LIB_CODE
KPTResultT
KPT_CALL
KPTRad32Convert16From(const char* aRadBuffer,
                      size_t aRadBufferSize,
                      uint16_t* aDataBuffer,
                      size_t aDataBufferSize);

KPT_LIB_CODE
char
KPT_CALL
KPTRad32GetChar(int aValue);

KPT_LIB_CODE
int
KPT_CALL
KPTRad32GetValue(char aChar);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTRAD32_H */
