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
 * @file    kptbinaryfile.h
 *
 * @brief   Interface for a binary file.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTBINARYFILE_H
#define H_KPTBINARYFILE_H

#include "kptlibsystem.h"
#include "kptapi.h"
#include "kptbinarystream.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

DECLARE_KPTHANDLE(KPTBinaryFileT)

/**
 * Modes for opening a binary file.
 */
enum KPTBinaryFileOpenT
{
	eKPTBinaryFileRead       = KPTBIT(0),   /**< Opens with Read support */
	eKPTBinaryFileWrite      = KPTBIT(1),   /**< Opens with Write support */
	eKPTBinaryFileNoCreate   = KPTBIT(2),   /**< Open fails if the file does not exist */
	eKPTBinaryFileNoTruncate = KPTBIT(3),   /**< Do not truncate the file if it exists */
	eKPTBinaryFileByteSwap   = KPTBIT(4),   /**< Byte swapping in initially enabled */
	eKPTBinaryFileShareRead  = KPTBIT(5),   /**< Allow others read access */
	eKPTBinaryFileShareWrite = KPTBIT(6),   /**< Allow others write access */
	eKPTBinaryFileRandom     = KPTBIT(7),   /**< Expect random access */

	/** Read and Write */
	eKPTBinaryFileReadWrite = eKPTBinaryFileRead|eKPTBinaryFileWrite,

	/** No Sharing */
	eKPTBinaryFileShareNone  = 0,

	/** Share read and write */
	eKPTBinaryFileShareAll = eKPTBinaryFileShareRead|eKPTBinaryFileShareWrite
};
typedef enum KPTBinaryFileOpenT KPTBinaryFileOpenT;

/*=====================================================================
 * KPTBinaryFileT Interface
 *====================================================================*/

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryFileCreate(KPTBinaryFileT** aHandle,
                    KPTHeapT* aHeap);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryFileDestroy(KPTBinaryFileT** aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryFileCreateWithOpen(KPTBinaryFileT** aHandle,
                            KPTHeapT* aHeap,
                            const KPTSysCharT* aPath,
							uint32_t aOptions);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryFileOpen(KPTBinaryFileT* aHandle,
				  const KPTSysCharT* aPath,
                  uint32_t aOptions);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryFileSetIOBuffer(KPTBinaryFileT* aHandle,
                         uint8_t* aBuffer,
                         size_t aBufferSize,
                         size_t aBlockSize);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryFileClose(KPTBinaryFileT* aHandle);

/*=====================================================================
 * KPTBinaryStreamT Interface
 *===================================================================*/

KPT_LIB_SYSTEM
KPTBinaryStreamT*
KPT_CALL
KPTBinaryFileGetStream(KPTBinaryFileT* aHandle);

KPT_LIB_SYSTEM
void
KPT_CALL
KPTBinaryFileReleaseStream(KPTBinaryStreamT** aStream);

/*======================================================================
 * KPTBinaryStreamT Implementation
 *======================================================================*/

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryFileGetLength(const KPTBinaryFileT* aHandle,
                       size_t* aLength);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryFileGetPos(const KPTBinaryFileT* aHandle,
                    size_t* aStartOffset,
                    off_t* aEndOffset);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryFileSetPos(KPTBinaryFileT* aHandle,
                    KPTStreamOriginT aOrigin,
                    off_t aOffset);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryFileFlush(KPTBinaryFileT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryFileRead(KPTBinaryFileT* aHandle,
                  void* aBuffer,
                  size_t aBytes,
                  size_t* aRead);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryFileRead8(KPTBinaryFileT* aHandle,
                   uint8_t* aBuffer,
                   size_t aCount,
                   size_t* aRead);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryFileRead16(KPTBinaryFileT* aHandle,
                    uint16_t* aBuffer,
                    size_t aCount,
                    size_t* aRead);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryFileRead32(KPTBinaryFileT* aHandle,
                    uint32_t* aBuffer,
                    size_t aCount,
                    size_t* aRead);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryFileWrite(KPTBinaryFileT* aHandle,
                   const void* aBuffer,
                   size_t aBytes,
                   size_t* aWritten);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryFileWrite8(KPTBinaryFileT* aHandle,
                    const uint8_t* aBuffer,
                    size_t aCount,
                    size_t* aWritten);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryFileWrite16(KPTBinaryFileT* aHandle,
                     const uint16_t* aBuffer,
                     size_t aCount,
                     size_t* aWritten);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryFileWrite32(KPTBinaryFileT* aHandle,
                     const uint32_t* aBuffer,
                     size_t aCount,
                     size_t* aWritten);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryFileGetByteSwap(const KPTBinaryFileT* aHandle,
                         KPTBoolT* aEnabled);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryFileSetByteSwap(KPTBinaryFileT* aHandle,
                         KPTBoolT aEnabled);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryFileSetByteOrder(KPTBinaryFileT* aHandle,
                          KPTStreamByteOrderT aByteOrder);

KPT_LIB_SYSTEM
uint32_t
KPT_CALL
KPTBinaryFileGetInfo(const KPTBinaryFileT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryFileGetBuffer(KPTBinaryFileT* aHandle,
                       KPTStreamBufferT* aRequest);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryFileReleaseBuffer(KPTBinaryFileT* aHandle,
                           KPTStreamBufferT* aRequest,
                           KPTBoolT aModified);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryFileCopyTo(KPTBinaryFileT* aHandle,
                    KPTBinaryStreamT* aTarget,
                    size_t aSize,
                    size_t* aCopied);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryFileFilter(KPTBinaryFileT* aHandle,
                    size_t aPosition,
                    size_t aSize,
                    size_t aBufferSize,
                    KPTStreamFilterT aCallback,
                    void* aContext);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTBINARYFILE_H */
