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
 * @file    kptbinarystream.h
 *
 * @brief   Abstract interface for a binary stream.
 *
 * @details This file declares an interface that can be used with different
 *          types of streams.
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTBINARYSTREAM_H
#define H_KPTBINARYSTREAM_H

#include "kptlibsystem.h"
#include "kptapi.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

DECLARE_KPTHANDLE(KPTBinaryStreamT)

/**
 * Possible values for a stream origin.
*/
enum KPTStreamOriginT
{
	eKPTStreamBegin = 0,   /**< Use the beginning of the stream as the origin */
	eKPTStreamCurrent = 1, /**< Use the current location as the origin */
	eKPTStreamEnd = 2      /**< Use the end as the origin */
};
typedef enum KPTStreamOriginT KPTStreamOriginT;

/**
 * Possible values for the byte order in a stream.
*/
enum KPTStreamByteOrderT
{
	eKPTStreamLittleEndian = 0,   /**< Little endian */
	eKPTStreamBigEndian    = 1,   /**< Big endian */
	eKPTStreamHostOrder    = 2,   /**< Host Order */
	eKPTStreamNetworkOrder = 3    /**< Network Order */
};
typedef enum KPTStreamByteOrderT KPTStreamByteOrderT;

/**
 * Stream capabilities.
*/
enum KPTStreamInfoT
{
	eKPTStreamValid = KPTBIT(0),          /**< Valid stream handle */
	eKPTStreamOpen = KPTBIT(1),           /**< Stream is open */
	eKPTStreamCanSeek = KPTBIT(2),        /**< Seeking possible */
	eKPTStreamCanRead = KPTBIT(3),        /**< Reading possible */
	eKPTStreamCanWrite = KPTBIT(4),       /**< Writing possible */
	eKPTStreamGetBufferUser = KPTBIT(5)   /**< Stream does not need user buffer for GetBuffer */
};
typedef enum KPTStreamInfoT KPTStreamInfoT;

/**
 * Structure used to access the stream data.
 */
typedef struct KPTStreamBufferT KPTStreamBufferT;
struct KPTStreamBufferT
{	
	uint8_t* userBuffer;        /**< [in] Pointer to user buffer */	
	size_t userBufferSize;      /**< [in] Maximum size of the user buffer */
	size_t dataPosition;        /**< [in] File offset to start of data */
	size_t dataSize;            /**< [in] Number of bytes to read */	
	size_t dataSizeMax;         /**< [in] Maximum number of bytes to read */
	uint8_t* streamBuffer;      /**< [out] Pointer to stream buffer */	
	size_t streamBufferSize;    /**< [out] Number of stream bytes in buffer */
};

/**
 * Function pointer for stream filters.
 * @param[in] aData      Pointer to memory representing some or all of the stream.
 * @param[in] aBytes     The number of bytes pointed to in aData.
 * @param[in] aMoreData  True if more data is expected after this call.
 * @param[in] aContext   Pointer to user supplied "context" data passed into KPTBinaryStreamFilter.
 * @param[out] aModified Set to eKPTTrue if the contents of \a aData have been modified by this call.
 */
typedef KPTResultT (KPT_CALLB *KPTStreamFilterT)(uint8_t* aData,
                                                 size_t aBytes,
                                                 KPTBoolT aMoreData,
                                                 void* aContext,
                                                 KPTBoolT* aModified);

/*=====================================================================
 * KPTBinaryStreamT Interface
 *====================================================================*/

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStreamGetLength(const KPTBinaryStreamT* aHandle,
                         size_t* aLength);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStreamGetPos(const KPTBinaryStreamT* aHandle,
                      size_t* aStartOffset,
                      off_t* aEndOffset);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStreamSetPos(KPTBinaryStreamT* aHandle,
                      KPTStreamOriginT aOrigin,
                      off_t aOffset);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStreamFlush(KPTBinaryStreamT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStreamRead(KPTBinaryStreamT* aHandle,
                    void* aBuffer,
                    size_t aBytes,
                    size_t* aRead);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStreamRead8(KPTBinaryStreamT* aHandle,
                     uint8_t* aBuffer,
                     size_t aCount,
                     size_t* aRead);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStreamRead16(KPTBinaryStreamT* aHandle,
                      uint16_t* aBuffer,
                      size_t aCount,
                      size_t* aRead);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStreamRead32(KPTBinaryStreamT* aHandle,
                      uint32_t* aBuffer,
                      size_t aCount,
                      size_t* aRead);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStreamWrite(KPTBinaryStreamT* aHandle,
                     const void* aBuffer,
                     size_t aBytes,
                     size_t* aWritten);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStreamWrite8(KPTBinaryStreamT* aHandle,
                      const uint8_t* aBuffer,
                      size_t aCount,
                      size_t* aWritten);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStreamWrite16(KPTBinaryStreamT* aHandle,
                      const uint16_t* aBuffer,
                      size_t aCount,
                      size_t* aWritten);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStreamWrite32(KPTBinaryStreamT* aHandle,
                      const uint32_t* aBuffer,
                      size_t aCount,
                      size_t* aWritten);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStreamGetByteSwap(const KPTBinaryStreamT* aHandle,
                           KPTBoolT* aEnabled);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStreamSetByteSwap(KPTBinaryStreamT* aHandle,
                           KPTBoolT aEnabled);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStreamSetByteOrder(KPTBinaryStreamT* aHandle,
                            KPTStreamByteOrderT aByteOrder);

KPT_LIB_SYSTEM
uint32_t
KPT_CALL
KPTBinaryStreamGetInfo(const KPTBinaryStreamT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStreamGetBuffer(KPTBinaryStreamT* aHandle,
                         KPTStreamBufferT* aRequest);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStreamReleaseBuffer(KPTBinaryStreamT* aHandle,
                             KPTStreamBufferT* aRequest,
                             KPTBoolT aModified);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStreamCopyTo(KPTBinaryStreamT* aHandle,
                      KPTBinaryStreamT* aTarget,
                      size_t aSize,
                      size_t* aCopied);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTBinaryStreamFilter(KPTBinaryStreamT* aHandle,
                      size_t aPosition,
                      size_t aSize,
                      size_t aBufferSize,
                      KPTStreamFilterT aCallback,
                      void* aContext);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTBINARYSTREAM_H */
