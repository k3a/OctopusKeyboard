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
 * @file    kptcrc32.h
 *
 * @brief   Interface file for the CRC32 algorithm.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTCRC32_H
#define H_KPTCRC32_H

#include "kptlibcode.h"
#include "kptapi.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define KPTCRC32_IEEE8023   0xEDB88320UL  /**< CRC-32-IEEE 802.3 Polynomial */
#define KPTCRC32_CASTAGNOLI 0x82F63B78UL  /**< Castagnoli Polynomial */
#define KPTCRC32_KOOPMAN    0xEB31D82EUL  /**< Koopman Polynomial */

typedef struct KPTCrc32T KPTCrc32T;
/** Management structure for calculating a CRC32. */
struct KPTCrc32T
{
	uint32_t crc;               /**< The running crc value used in Update functions */
	const uint32_t* crcTable;   /**< 256 entry CRC table filled by KPTCrc32FillTable. */
};

KPT_LIB_CODE
void
KPT_CALL
KPTCrc32FillTable(uint32_t* aTable, uint32_t aPolynomial);

KPT_LIB_CODE
KPTResultT
KPT_CALL
KPTCrc32Begin(KPTCrc32T* aCheck, const uint32_t* aCRCTable);

KPT_LIB_CODE
void
KPT_CALL
KPTCrc32Update(KPTCrc32T* aCheck, const uint8_t* aData, size_t aSize);

KPT_LIB_CODE
uint32_t
KPT_CALL
KPTCrc32End(KPTCrc32T* aCheck);

KPT_LIB_CODE
uint32_t
KPT_CALL
KPTCrc32Compute(const uint8_t* aData, size_t aSize, const uint32_t* aCRCTable);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTCRC32_H */
