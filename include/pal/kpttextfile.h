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
 * @file    kpttextfile.h
 *
 * @brief   Abstract interface for text files.
 *
 * @details
 * 
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTTEXTFILE_H
#define H_KPTTEXTFILE_H

#include "kptlibsystem.h"
#include "kptapi.h"
#include "kptheap.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

DECLARE_KPTHANDLE(KPTTextFileT)

/*
enumerations used when opening a file
*/
enum KPTTextFileOpenT
{
    eKPTTextFileRead         = KPTBIT(0),  /**< fails if file doesn't exist */
    eKPTTextFileWrite        = KPTBIT(1),  /**< created it it doesn't exist, overwritten if it does */
    eKPTTextFileAppend       = KPTBIT(2)   /**< created if it doesn't exist, appended if it does */
};
typedef enum KPTTextFileOpenT KPTTextFileOpenT;

/* 
flags for getinfo NB read/write/append same as fileopenT, unit test relies on this
*/
enum KPTTextFileInfoT
{
	eKPTTextFileInfoRead   =  KPTBIT(0),
    eKPTTextFileInfoWrite  =  KPTBIT(1),
    eKPTTextFileInfoAppend =  KPTBIT(2),
    eKPTTextFileInfoOpen   =  KPTBIT(3)
};

typedef enum KPTTextFileInfoT KPTTextFileInfoT;


/*

suport for encryption has not yet been implemented.

*/
enum KPKTTextFileConfigurationT
{
    eKPTTextFileWorkInMemory       = KPTBIT(3), /**< if not set, work on disk */
    eKPTTextFileWriteCRLF          = KPTBIT(4), /**< if not set, use PAL default */
    eKPTTextFileWriteLF            = KPTBIT(5),  /**< if not set, use PAL default */ 
    eKPTTextFileWriteLineSeparator = KPTBIT(6)  /**< for Symbian */
};
typedef enum KPKTTextFileConfigurationT KPKTTextFileConfigurationT;

enum KPTTextFileBOMT
{
    eKPTTextFileBOM_ASCII        = KPTBIT(7), /**< ASCII file, no BOM */
    eKPTTextFileBOM_UTF8         = KPTBIT(8), /**< UTF-8 BOM */
    eKPTTextFileBOM_UTF16BE      = KPTBIT(9), /**< UTF-16 big-endian BOM */
    eKPTTextFileBOM_UTF16LE      = KPTBIT(10), /**< UTF-16 little-endian BOM */
    eKPTTextFileBOM_UTF32BE      = KPTBIT(11), /**< UTF-32 big-endian BOM */
    eKPTTextFileBOM_UTF32LE      = KPTBIT(12), /**< UTF-32 little-endian BOM */
    eKPTTextFileBOM_Unknown      = KPTBIT(13) /**< set this to accept whetever is in the file */
};
typedef enum KPTTextFileBOMT KPTTextFileBOMT;

enum KPTTextFileCloseT
{
    eKPTTextFileSaveChanges    = KPTBIT(0), /**< Preserve data changes when file closed. */
    eKPTTextFileAbandonChanges  = KPTBIT(1) /**< Abandon any data changes when file closed. */
};
typedef enum KPTTextFileCloseT KPTTextFileCloseT;


/*
use when setting cursor position
*/
enum KPTTextFileOriginT
{
    eKPTTextFileStart   = 0, /**< Apply offset from beginning of file */
    eKPTTextFileCurrent = 1, /**< Apply offset at cursor position. */
    eKPTTextFileEnd     = 2  /**< Apply offset from file end */
};

typedef enum KPTTextFileOriginT KPTTextFileOriginT;

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTextFileCreate(KPTTextFileT** aHandle, 
                  KPTHeapT* aHeap);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTextFileDestroy(KPTTextFileT** aHandle);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTextFileOpen(KPTTextFileT* aHandle,
                const KPTSysCharT* aPath,
                uint32_t aOpenOptions);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTextFileCreateWithOpen(KPTTextFileT** aHandle, 
                          KPTHeapT* aHeap,
                          const KPTSysCharT* aPath,
                          uint32_t aOpenOptions);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTextFileClose(KPTTextFileT* aHandle, 
                 uint32_t aCloseOptions);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTextFileReadCharsU(KPTTextFileT* aHandle,
                      KPTUniCharT* aTargetBuffer,
                      size_t aTargetBufferSize,
                      size_t aNumCharsToRead,
                      size_t* aNumCharsRead);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTextFileWriteCharsU(KPTTextFileT* aHandle,
                       const KPTUniCharT* aSourceBuffer,
                       size_t aNumCharsToWrite,
                       size_t* aNumCharsWritten);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTextFileReadLineU(KPTTextFileT* aHandle,
                     KPTUniCharT* aTargetBuffer,
                     size_t aTargetBufferSize,
                     size_t* aNumCharsRead);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTextFileWriteLineU(KPTTextFileT* aHandle,
                      const KPTUniCharT* aSourceBuffer,
                      size_t aNumCharsToWrite,
                      size_t* aNumCharsWritten);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTextFileReadCharsS(KPTTextFileT* aHandle,
                      KPTSysCharT* aTargetBuffer,
                      size_t aTargetBufferSize,
                      size_t aNumCharsToRead,
                      size_t* aNumCharsRead);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTextFileWriteCharsS(KPTTextFileT* aHandle,
                       const KPTSysCharT* aSourceBuffer,
                       size_t aNumCharsToWrite,
                       size_t* aNumCharsWritten);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTextFileReadLineS(KPTTextFileT* aHandle,
                     KPTSysCharT* aTargetBuffer,
                     size_t aTargetBufferSize,
                     size_t* aNumCharsRead);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTextFileWriteLineS(KPTTextFileT* aHandle,
                      const KPTSysCharT* aSourceBuffer,
                      size_t aNumCharsToWrite,
                      size_t* aNumCharsWritten);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTextFileReadCharsA(KPTTextFileT* aHandle,
                      uint8_t* aTargetBuffer,
                      size_t aTargetBufferSize,
                      size_t aNumCharsToRead,
                      size_t* aNumCharsRead);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTextFileWriteCharsA(KPTTextFileT* aHandle,
                       const uint8_t* aSourceBuffer,
                       size_t aNumCharsToWrite,
                       size_t* aNumCharsWritten);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTextFileReadLineA(KPTTextFileT* aHandle,
                     uint8_t* aTargetBuffer,
                     size_t aTargetBufferSize,
                     size_t* aNumCharsRead);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTextFileWriteLineA(KPTTextFileT* aHandle,
                      const uint8_t* aSourceBuffer,
                      size_t aNumCharsToWrite,
                      size_t* aNumCharsWritten);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTextFileSetPos(KPTTextFileT* aHandle,
                  KPTTextFileOriginT aOrigin,
                  off_t aOffset);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTextFileGetPos(const KPTTextFileT* aHandle,
                  size_t* aPos);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTextFileGetDataLength(const KPTTextFileT* aHandle,
                         size_t* aLength);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTextFileGetLength(const KPTTextFileT* aHandle,
                     size_t* aLength);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTextFileFlush(KPTTextFileT* aHandle);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTextFileWriteNewLine(KPTTextFileT* aHandle);

KPT_LIB_SYSTEM
uint32_t
KPT_CALL
KPTTextFileGetInfo(const KPTTextFileT* aHandle);


#ifdef __cplusplus
}
#endif /*__cplusplus */


#endif /* h_kpttextfile_h */
