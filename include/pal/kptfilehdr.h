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
 * @file    kptfilehdr.h
 *
 * @brief   Standard file header for binary files.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTFILEHDR_H
#define H_KPTFILEHDR_H

#include "kptlibsystem.h"
#include "kptapi.h"
#include "kpterrorstack.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * File header.
 */
typedef struct KPTFileHdrT KPTFileHdrT;
struct KPTFileHdrT
{
	uint32_t byteOrderMark;     /**< Byte order mark */
	uint32_t keyPointMark;      /**< KeyPoint file indentifier */
	uint32_t headerVersion;     /**< Header version number */
	uint32_t headerInformation; /**< Header information fields (see KPTFileHdrInfoT) */
	uint32_t fileType;          /**< Data file type indentifier */
	uint32_t dataVersion;       /**< Data file version */
	uint32_t dataCheck;         /**< Data checksum/error detection value */
	uint32_t headerCheck;       /**< Header checksum/error detection value */
};

/** Byte order mark for file header */
#define KPTFILEHDR_BOM            0x12345678

/** Swapped byte order mark for file header */
#define KPTFILEHDR_BOM_SWAPPED    0x78563412

/** KeyPoint file marker */
#define KPTFILEHDR_KEYPOINTMARK   0x4B505446

/** Default header checksum */
#define KPTFILEHDR_DATACHECK      0x7A7A7A7A

/** Default data checksum */
#define KPTFILEHDR_HEADERCHECK    0x8B8B8B8B


/**
 * Enum defining the possible checksums in headers.
 */
enum KPTHeaderChecksumT
{
	eKPTHdrCheckNone = 0,          /**< No checksum, value must be zero */
	eKPTHdrCheckCRC32 = 1,         /**< CRC-32-IEEE 802.3 */
	eKPTHdrCheckFletcher16 = 2     /**< Fletcher 16 */
};
typedef enum KPTHeaderChecksumT KPTHeaderChecksumT;

/**
 * Enum defining the possible information fields.
 */
enum KPTFileHdrInfoT
{
	eKPTFileHdrInfoSize = 0,    /**< Size of header */
	eKPTFileHdrInfoDataAlg = 1, /**< Data Check algorithm  */
	eKPTFileHdrInfoHdrAlg = 2,  /**< Header Check algorithm */
	eKPTFileHdrInfoReserved = 3 /**< Reserved */
};
typedef enum KPTFileHdrInfoT KPTFileHdrInfoT;

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFileHdrInit(KPTFileHdrT* aHeader);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFileHdrConvertToHost(KPTFileHdrT* aHeader,
                        KPTBoolT* aByteSwapped);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFileHdrUpdateHeaderChecksum(KPTFileHdrT* aHeader);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFileHdrValidate(const KPTFileHdrT* aHeader);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFileHdrSetInfo(KPTFileHdrT* aHeader,
                  KPTFileHdrInfoT aType,
                  uint8_t aValue);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFileHdrGetInfo(const KPTFileHdrT* aHeader,
                  KPTFileHdrInfoT aType,
                  uint8_t* aValue);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTFILEHDR_H */
