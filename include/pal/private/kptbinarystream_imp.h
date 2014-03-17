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
 *
 * @file    kptbinarystream_imp.h
 *
 * @brief   Implementation structures for a binary stream.
 *
 * @details This file declares private implementation structures that
 *          objects must use if they provide stream support.
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTBINARYSTREAM_IMP_H
#define H_KPTBINARYSTREAM_IMP_H

#include "kptbinarystream.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/**
 * Function pointer for KPTBinaryStreamGetLength
 */
typedef KPTResultT (KPT_CALL* KPTBinaryStreamImpGetLengthT)(const void* aHandle,
                                                            size_t* aLength);

/**
 * Function pointer for KPTBinaryStreamGetPos
 */
typedef KPTResultT (KPT_CALL* KPTBinaryStreamImpGetPosT)(const void* aHandle,
                                                         size_t* aStartOffset,
                                                         off_t* aEndOffset);

/**
 * Function pointer for KPTBinaryStreamSetPos
 */
typedef KPTResultT (KPT_CALL* KPTBinaryStreamImpSetPosT)(void* aHandle,
                                                         KPTStreamOriginT aOrigin,
                                                         off_t aOffset);


/**
 * Function pointer for KPTBinaryStreamFlush
 */
typedef KPTResultT (KPT_CALL* KPTBinaryStreamImpFlushT)(void* aHandle);

/**
 * Function pointer for KPTBinaryStreamRead
 */
typedef KPTResultT (KPT_CALL* KPTBinaryStreamImpReadT)(void* aHandle,
                                                       void* aBuffer,
                                                       size_t aBytes,
                                                       size_t* aRead);

/**
 * Function pointer for KPTBinaryStreamRead8
 */
typedef KPTResultT (KPT_CALL* KPTBinaryStreamImpRead8T)(void* aHandle,
                                                        uint8_t* aBuffer,
                                                        size_t aCount,
                                                        size_t* aRead);

/**
 * Function pointer for KPTBinaryStreamRead16
 */
typedef KPTResultT (KPT_CALL* KPTBinaryStreamImpRead16T)(void* aHandle,
                                                         uint16_t* aBuffer,
                                                         size_t aCount,
                                                         size_t* aRead);

/**
 * Function pointer for KPTBinaryStreamRead32
 */
typedef KPTResultT (KPT_CALL* KPTBinaryStreamImpRead32T)(void* aHandle,
                                                         uint32_t* aBuffer,
                                                         size_t aCount,
                                                         size_t* aRead);

/**
* Function pointer for KPTBinaryStreamWrite
*/
typedef KPTResultT (KPT_CALL* KPTBinaryStreamImpWriteT)(void* aHandle,
                                                        const void* aBuffer,
                                                        size_t aBytes,
                                                        size_t* aWritten);

/**
* Function pointer for KPTBinaryStreamWrite8
*/
typedef KPTResultT (KPT_CALL* KPTBinaryStreamImpWrite8T)(void* aHandle,
                                                         const uint8_t* aBuffer,
                                                         size_t aCount,
                                                         size_t* aWritten);

/**
* Function pointer for KPTBinaryStreamWrite16
*/
typedef KPTResultT (KPT_CALL* KPTBinaryStreamImpWrite16T)(void* aHandle,
                                                          const uint16_t* aBuffer,
                                                          size_t aCount,
                                                          size_t* aWritten);

/**
* Function pointer for KPTBinaryStreamWrite32
*/
typedef KPTResultT (KPT_CALL* KPTBinaryStreamImpWrite32T)(void* aHandle,
                                                          const uint32_t* aBuffer,
                                                          size_t aCount,
                                                          size_t* aWritten);

/**
* Function pointer for KPTBinaryStreamGetByteSwap
*/
typedef KPTResultT (KPT_CALL* KPTBinaryStreamImpGetByteSwapT)(const void* aHandle,
                                                              KPTBoolT* aEnabled);

/**
* Function pointer for KPTBinaryStreamSetByteSwap
*/
typedef KPTResultT (KPT_CALL* KPTBinaryStreamImpSetByteSwapT)(void* aHandle,
                                                              KPTBoolT aEnabled);

/**
* Function pointer for KPTBinaryStreamSetByteOrder
*/
KPT_LIB_SYSTEM
typedef KPTResultT (KPT_CALL* KPTBinaryStreamImpSetByteOrderT)(void* aHandle,
                                                               KPTStreamByteOrderT aByteOrder);

/**
* Function pointer for KPTBinaryStreamGetInfo
*/
typedef uint32_t (KPT_CALL* KPTBinaryStreamImpGetInfoT)(const void* aHandle);

/**
* Function pointer for KPTBinaryStreamGetBuffer
*/
typedef KPTResultT (KPT_CALL* KPTBinaryStreamImpGetBufferT)(void* aHandle,
                                                            KPTStreamBufferT* aRequest);

/**
* Function pointer for KPTBinaryStreamReleaseBuffer
*/
typedef KPTResultT (KPT_CALL* KPTBinaryStreamImpReleaseBufferT)(void* aHandle,
                                                                KPTStreamBufferT* aRequest,
                                                                KPTBoolT aModified);

/**
* Function pointer for KPTBinaryStreamCopyTo
*/
typedef KPTResultT (KPT_CALL* KPTBinaryStreamImpCopyToT)(void* aHandle,
                                                         KPTBinaryStreamT* aTarget,
                                                         size_t aSize,
                                                         size_t* aCopied);

/**
* Function pointer for KPTBinaryStreamFilter
*/
typedef KPTResultT (KPT_CALL* KPTBinaryStreamImpFilterT)(void* aHandle,
                                                         size_t aPosition,
                                                         size_t aSize,
                                                         size_t aBufferSize,
                                                         KPTStreamFilterT aCallback,
                                                         void* aContext);

/**
 * Implementation structure for abstract KPTBinaryStream interface.
 */
struct KPTBinaryStreamT
{
	void* sourceHandle;                            /**< Handle of concrete object */
	KPTBinaryStreamImpGetLengthT GetLength;         /**< Pointer to GetLength implementation */
	KPTBinaryStreamImpGetPosT GetPos;               /**< Pointer to GetPos implementation */
	KPTBinaryStreamImpSetPosT SetPos;               /**< Pointer to SetPos implementation */
	KPTBinaryStreamImpFlushT Flush;                 /**< Pointer to Flush implementation */
	KPTBinaryStreamImpReadT Read;                   /**< Pointer to Read implementation */
	KPTBinaryStreamImpRead8T Read8;                 /**< Pointer to Read8 implementation */
	KPTBinaryStreamImpRead16T Read16;               /**< Pointer to Read16 implementation */
	KPTBinaryStreamImpRead32T Read32;               /**< Pointer to Read32 implementation */
	KPTBinaryStreamImpWriteT Write;                 /**< Pointer to Write implementation */
	KPTBinaryStreamImpWrite8T Write8;               /**< Pointer to Write8 implementation */
	KPTBinaryStreamImpWrite16T Write16;             /**< Pointer to Write16 implementation */
	KPTBinaryStreamImpWrite32T Write32;             /**< Pointer to Write32 implementation */
	KPTBinaryStreamImpGetByteSwapT GetByteSwap;     /**< Pointer to GetByteSwap implementation */
	KPTBinaryStreamImpSetByteSwapT SetByteSwap;     /**< Pointer to SetByteSwap implementation */
	KPTBinaryStreamImpSetByteOrderT SetByteOrder;   /**< Pointer to SetByteOrder implementation */
	KPTBinaryStreamImpGetInfoT GetInfo;             /**< Pointer to GetInfo implementation */
	KPTBinaryStreamImpGetBufferT GetBuffer;         /**< Pointer to GetBuffer implementation */
	KPTBinaryStreamImpReleaseBufferT ReleaseBuffer; /**< Pointer to ReleaseBuffer implementation */
	KPTBinaryStreamImpCopyToT CopyTo;               /**< Pointer to CopyTo implementation */
	KPTBinaryStreamImpFilterT Filter;               /**< Pointer to Filter implementation */
};

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTBINARYSTREAM_IMP_H */
