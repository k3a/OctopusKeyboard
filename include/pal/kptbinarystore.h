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
 * @file    kptbinarystore.h
 *
 * @brief   Interface for a binary store.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTBINARYSTORE_H
#define H_KPTBINARYSTORE_H

#include "kptlibsystem.h"
#include "kptapi.h"
#include "kptbinarystream.h"
#include "kptfilehdr.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Constructs a block identifier from four bytes, or characters.
 */
#define KPTBLOCKID_MAKE(b0, b1, b2, b3) (KPTBIT8_PACK((b0), 0) | \
                                         KPTBIT8_PACK((b1), 1) | \
                                         KPTBIT8_PACK((b2), 2) | \
                                         KPTBIT8_PACK((b3), 3))

/** Extracts byte 0 from a block identifier. */
#define KPTBLOCKID_EXTRACT0(id) (KPTBIT8_UNPACK((id), 0))
/** Extracts byte 1 from a block identifier. */
#define KPTBLOCKID_EXTRACT1(id) (KPTBIT8_UNPACK((id), 1))
/** Extracts byte 2 from a block identifier. */
#define KPTBLOCKID_EXTRACT2(id) (KPTBIT8_UNPACK((id), 2))
/** Extracts byte 3 from a block identifier. */
#define KPTBLOCKID_EXTRACT3(id) (KPTBIT8_UNPACK((id), 3))

/** The default checksum used in binary block headers */
#define KPTBLOCK_DATACHECK      0x9C9C9C9C

typedef struct KPTBinaryBlockT KPTBinaryBlockT;
/** Identifier structure for a block in a binary store. */
struct KPTBinaryBlockT
{
	uint32_t id;             /**< Block identifier */
	uint32_t information;    /**< Block information */
	uint32_t dataChecksum;   /**< Checksum for block data */
	uint32_t dataSize;       /**< Size of block data */

	size_t dataPosition;     /**< File position for the start of block data */
	uint32_t status;         /**< Block status */
};

/**
 * Enum defining the possible information fields in a block.
 */
enum KPTBinaryBlockInfoT
{
	eKPTBlockInfoCompress = 0, /**< Compression Algorithm*/
	eKPTBlockInfoEncrypt = 1,  /**< Data Check algorithm  */
	eKPTBlockInfoDataAlg = 2,  /**< Checksum algorithm for data */
	eKPTBlockInfoCheck = 3     /**< Checksum value for header */
};
typedef enum KPTBinaryBlockInfoT KPTBinaryBlockInfoT;

/**
 * Enum defining the possible compression.
 */
enum KPTBlockCompressionT
{
	eKPTBlockCompressNone = 0,          /**< No compression */
};
typedef enum KPTBlockCompressionT KPTBlockCompressionT;

/**
 * Enum defining the possible encryption.
 */
enum KPTBlockEncryptionT
{
	eKPTBlockEncryptNone = 0,          /**< No encryption */
};
typedef enum KPTBlockEncryptionT KPTBlockEncryptionT;

/**
 * Status flags for a binary block
 */
enum KPTBinaryBlockStatusT
{
	eKPTBinaryBlockCreated = KPTBIT(0), /**< Block was created by KPTBinaryStoreCreateBlock */
	eKPTBinaryBlockModified = KPTBIT(1) /**< Block size may have been modified in some way */
};
typedef enum KPTBinaryBlockStatusT KPTBinaryBlockStatusT;

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStoreReadFileHeader(KPTBinaryStreamT* aHandle,
                             KPTFileHdrT* aHeader,
                             KPTBoolT aDataCheck);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStoreWriteFileHeader(KPTBinaryStreamT* aHandle,
                              const KPTFileHdrT* aHeader);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStoreUpdateFileHeader(KPTBinaryStreamT* aHandle,
                               size_t aHeaderPosition,
                               KPTHeaderChecksumT aHeaderAlgorithm,
                               off_t aDataSize,
                               KPTHeaderChecksumT aDataAlgorithm);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStoreReadBlockHeader(KPTBinaryStreamT* aHandle,
                              KPTBinaryBlockT* aBlock);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStoreFindBlock(KPTBinaryStreamT* aHandle,
                        KPTBinaryBlockT* aBlock,
                        KPTBinaryBlockT* aParentBlock);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStoreWriteBlockHeader(KPTBinaryStreamT* aHandle,
                               KPTBinaryBlockT* aBlock);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStoreExitBlock(KPTBinaryStreamT* aHandle,
                        KPTBinaryBlockT* aBlock);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStoreValidateBlock(KPTBinaryStreamT* aHandle,
                            KPTBinaryBlockT* aBlock,
                            KPTBoolT aDataCheck);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStoreComputeCheck(KPTBinaryStreamT* aHandle,
                           size_t aPosition,
                           size_t aSize,
                           size_t aBufferSize,
                           KPTHeaderChecksumT aAlgorithm,
                           uint32_t aDefault,
                           uint32_t* aCheck);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStoreSetBlockInfo(KPTBinaryBlockT* aBlock,
                           KPTBinaryBlockInfoT aType,
                           uint8_t aValue);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStoreGetBlockInfo(const KPTBinaryBlockT* aBlock,
                           KPTBinaryBlockInfoT aType,
                           uint8_t* aValue);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTBINARYSTORE_H */
