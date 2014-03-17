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
 * @file    kptcheck.h
 *
 * @brief   Checksum algorithms.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_CHECK_H
#define H_CHECK_H

#include "kptlibcode.h"
#include "kptapi.h"
#include "kptfletcher16.h"
#include "kptcrc32ieee.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

KPT_LIB_CODE
uint32_t
KPT_CALL
KPTCheckInvertedSumUpdate(uint32_t aTotal,
                          const uint8_t* aData,
                          size_t aSize);

KPT_LIB_CODE
uint8_t
KPT_CALL
KPTCheckInvertedSumEnd(uint32_t aTotal);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_CHECK_H */
