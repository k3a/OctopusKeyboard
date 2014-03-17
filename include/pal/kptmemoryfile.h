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
 * @file    kptmemoryfile.h
 *
 * @brief   Interface for a memory file.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTMEMORYFILE_H
#define H_KPTMEMORYFILE_H

#include "kptlibsystem.h"
#include "kptapi.h"
#include "kptbinarystream.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

DECLARE_KPTHANDLE(KPTMemoryFileT)

/**
 * Modes for opening a memory file.
 */
enum KPTMemoryFileOpenT
{
	eKPTMemoryFileRead       = KPTBIT(0),   /**< Opens with Read support */
	eKPTMemoryFileWrite      = KPTBIT(1),   /**< Opens with Write support */
	eKPTMemoryFileNoCreate   = KPTBIT(2),   /**< Opens fails if the file does not exist (CreateShare only)*/
	eKPTMemoryFileByteSwap   = KPTBIT(3),   /**< Byte swapping in initially enabled */

	/**< Read and write access */
	eKPTMemoryFileReadWrite = eKPTMemoryFileRead|eKPTMemoryFileWrite
};
typedef enum KPTMemoryFileOpenT KPTMemoryFileOpenT;

/*=====================================================================
 * KPTmemoryFileT Interface
 *===================================================================*/

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileCreate(KPTMemoryFileT** aHandle,
                    KPTHeapT* aHeap);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileDestroy(KPTMemoryFileT** aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileOpenDynamic(KPTMemoryFileT* aHandle,
                         uint32_t aOptions,
                         void* aBuffer,
                         size_t aSize,
                         size_t aCapacity,
                         size_t aGrowSize);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileOpenFixed(KPTMemoryFileT* aHandle,
                       uint32_t aOptions,
                       void* aBuffer,
                       size_t aSize,
                       size_t aCapacity);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileOpenShared(KPTMemoryFileT* aHandle,
                        uint32_t aOptions,
                        const KPTSysCharT* aSharedName,
                        size_t aSize,
                        size_t aCapacity);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileClose(KPTMemoryFileT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileGetCapacity(const KPTMemoryFileT* aHandle,
                         size_t* aCapacity);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileSetCapacity(KPTMemoryFileT* aHandle,
                         size_t aCapacity);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileSetLength(KPTMemoryFileT* aHandle,
                       size_t aBytes);

/*=====================================================================
 * KPTBinaryStreamT Interface
 *===================================================================*/

KPT_LIB_SYSTEM
KPTBinaryStreamT*
KPT_CALL
KPTMemoryFileGetStream(KPTMemoryFileT* aHandle);

KPT_LIB_SYSTEM
void
KPT_CALL
KPTMemoryFileReleaseStream(KPTBinaryStreamT** aStream);

/*=====================================================================
 * KPTBinaryStreamT Implementation
 *===================================================================*/

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileGetLength(const KPTMemoryFileT* aHandle,
                       size_t* aLength);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileGetPos(const KPTMemoryFileT* aHandle,
                    size_t* aStartOffset,
                    off_t* aEndOffset);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileSetPos(KPTMemoryFileT* aHandle,
                    KPTStreamOriginT aOrigin,
                    off_t aOffset);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileFlush(KPTMemoryFileT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileRead(KPTMemoryFileT* aHandle,
                  void* aBuffer,
                  size_t aBytes,
                  size_t* aRead);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileRead8(KPTMemoryFileT* aHandle,
                   uint8_t* aBuffer,
                   size_t aCount,
                   size_t* aRead);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileRead16(KPTMemoryFileT* aHandle,
                    uint16_t* aBuffer,
                    size_t aCount,
                    size_t* aRead);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileRead32(KPTMemoryFileT* aHandle,
                    uint32_t* aBuffer,
                    size_t aCount,
                    size_t* aRead);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileWrite(KPTMemoryFileT* aHandle,
                   const void* aBuffer,
                   size_t aBytes,
                   size_t* aWritten);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileWrite8(KPTMemoryFileT* aHandle,
                    const uint8_t* aBuffer,
                    size_t aCount,
                    size_t* aWritten);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileWrite16(KPTMemoryFileT* aHandle,
                     const uint16_t* aBuffer,
                     size_t aCount,
                     size_t* aWritten);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileWrite32(KPTMemoryFileT* aHandle,
                     const uint32_t* aBuffer,
                     size_t aCount,
                     size_t* aWritten);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileGetByteSwap(const KPTMemoryFileT* aHandle,
                         KPTBoolT* aEnabled);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileSetByteSwap(KPTMemoryFileT* aHandle,
                         KPTBoolT aEnabled);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileSetByteOrder(KPTMemoryFileT* aHandle,
                          KPTStreamByteOrderT aByteOrder);

KPT_LIB_SYSTEM
uint32_t
KPT_CALL
KPTMemoryFileGetInfo(const KPTMemoryFileT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileGetBuffer(KPTMemoryFileT* aHandle,
                       KPTStreamBufferT* aRequest);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileReleaseBuffer(KPTMemoryFileT* aHandle,
                           KPTStreamBufferT* aRequest,
                           KPTBoolT aModified);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileCopyTo(KPTMemoryFileT* aHandle,
                    KPTBinaryStreamT* aTarget,
                    size_t aSize,
                    size_t* aCopied);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileFilter(KPTMemoryFileT* aHandle,
                    size_t aPosition,
                    size_t aSize,
                    size_t aBufferSize,
                    KPTStreamFilterT aCallback,
                    void* aContext);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileReadAll(KPTMemoryFileT* aHandle,
                     const KPTSysCharT* aFilePath);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTMemoryFileWriteAll(KPTMemoryFileT* aHandle,
                      const KPTSysCharT* aFilePath);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTMEMORYFILE_H */
