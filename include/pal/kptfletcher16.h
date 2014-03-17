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
 * @file    kptfletcher16.h
 *
 * @brief   Interface file for the Fletcher-16 algorithm.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTFLETCHER16_H
#define H_KPTFLETCHER16_H

#include "kptlibcode.h"
#include "kptapi.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct KPTFletcher16T KPTFletcher16T;
/** Management structure for Fletcher 16 checksum. */
struct KPTFletcher16T
{
	uint16_t sum1;  /**< Accumulator 1 */
	uint32_t sum2;  /**< Accumulator 2 */
};


KPT_LIB_CODE
KPTResultT
KPT_CALL
KPTFletcher16Begin(KPTFletcher16T* aCheck);

KPT_LIB_CODE
void
KPT_CALL
KPTFletcher16Update(KPTFletcher16T* aCheck,
                    const uint8_t* aData,
                    size_t aSize);

KPT_LIB_CODE
uint16_t
KPT_CALL
KPTFletcher16End(KPTFletcher16T* aCheck);

KPT_LIB_CODE
uint16_t
KPT_CALL
KPTFletcher16Compute(const uint8_t* aData,
                     size_t aSize);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTFLETCHER16_H */

