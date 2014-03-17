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
 * @file    kptcrc32ieee.h
 *
 * @brief   Interface file for the CRC32 (IEEE) algorithm.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTCRC32IEEE_H
#define H_KPTCRC32IEEE_H

#include "kptlibcode.h"
#include "kptapi.h"
#include "kptcrc32.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

KPT_LIB_CODE
KPTResultT
KPT_CALL
KPTCrc32IeeeBegin(KPTCrc32T* aCheck);

KPT_LIB_CODE
uint32_t
KPT_CALL
KPTCrc32IeeeCompute(const uint8_t* aData,
                    size_t aSize);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTCRC32IEEE_H */
