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
 * @file    kpttextfile_private.h
 * 
 * @brief   Internal definitions for text files.
 *
 * @details 
 *  
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTTEXTFILEPRIVATE_H
#define H_KPTTEXTFILEPRIVATE_H

#include "kptbinaryfile.h"
#include "kptmemoryfile.h"
#include "kpttextfile.h"

#define KPT_TEXTFILE_CR 0x000D  /**< Carriage return */
#define KPT_TEXTFILE_LF 0x000A  /**< Line-feed */
#define KPT_TEXTFILE_LINE_SEPARATOR 0x2028 /**< Line separator - used by Symbian */
#define KPT_TEXTFILE_NEWLINE_SIZE 3 /**< Max number of bytes in a new-line character (including NULL) */

#define KPT_TEXTFILE_CONVERSION_BLOCK_SIZE 1024 /**< Size in bytes of conversion buffer */

/**< Everything you need to know about a text file */
struct KPTTextFileT
{
    KPTSysCharT*     FilePath;           /**< Text file location */
    KPTMemoryFileT*  MemoryFileHandle;   /**< Handle used if opened as memory file */
    KPTBinaryFileT*  BinaryFileHandle;   /**< Handle used if opened as binary file */
    KPTBinaryStreamT* FileBinaryStream;  /**< Binary stream containing file data */
    KPTUniCharT      UserNewLine[KPT_TEXTFILE_NEWLINE_SIZE];  /**< User selected newline, plus terminator */
    KPTBoolT         DataModified;       /**< eKPTTrue if file data has been modified */
    uint32_t         FileAccessOptions;  /**< User-requested access options */
    KPTBoolT         IsMemoryFile;       /**< eKPTTrue if working in memory */
    KPTTextFileBOMT  FileBOM;            /**< BOM derived from file */
    KPTTextFileBOMT  UserBOM;            /**< BOM requested by user */
    size_t           MinOffset;          /**< Used to constrain access when appending */
    size_t           DataOffset;         /**< Where the data actually begins */
    KPTHeapT*        FileHeap;           /**< Heap to be used by text file software */
    KPTBoolT         FileExists;         /**< eKPTTrue if working on a previously existing file */
    KPTBoolT         BOMFromData;        /**< If true, don't need offset for header */
	KPTBoolT         FileOpen;
    uint8_t*         ConversionBuffer;   /**< Used for block conversion of data */
};

int IsAccessApproved(const KPTTextFileT* aHandle,
                     KPTTextFileOpenT aRequestedAccess);

uint8_t* GetHandleConversionBuffer(KPTTextFileT* aHandle);

KPTResultT KPTTextFileWriteNewLineA(KPTTextFileT* aHandle);
KPTResultT KPTTextFileWriteNewLineU(KPTTextFileT* aHandle);
KPTResultT KPTTextFileWriteNewLineS(KPTTextFileT* aHandle);


#endif /* h_kpttextfileprivate_h */
