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
 * @file kptdirscan.h
 *
 * @brief scans the directory and populates the required lists
 *
 * @details 
 *
 ****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPT_DIRSCAN_H
#define H_KPT_DIRSCAN_H

#include "kptlibsystem.h"
#include "kptlist.h"
#include "kptapi.h"

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus */

DECLARE_KPTHANDLE(KPTDirListT)

/**
 * Options for file listings
 */
enum KPTFileListOptionT
{
	eKPTFilelistDefault = 0x00000000,            /**< default options */
	eKPTFilelistRemoveExtension = 0x00000001,    /**< remove the file extension */
	eKPTFilelistFullPath = 0x00000002            /**< creates and stores the full path to the file */
};
typedef enum KPTFileListOptionT KPTFileListOptionT;

KPT_LIB_SYSTEM 
KPTResultT
KPT_CALL
KPTDirScanCreateFileList(KPTHeapT* aHeap,
                         uint32_t aOptions,
                         const KPTSysCharT* aDirectory, 
                         const KPTSysCharT* aSearch, 
                         KPTListT** aFileList);

KPT_LIB_SYSTEM 
KPTResultT
KPT_CALL
KPTDirScanCreateDirList(KPTDirListT** aHandle,
                        KPTHeapT* aHeap,
                        uint32_t aOptions,
                        const KPTSysCharT* aBaseDirectory, 
                        const KPTSysCharT* aSearch);

KPT_LIB_SYSTEM 
KPTResultT
KPT_CALL
KPTDirScanDestroyDirList(KPTDirListT** aList);

KPT_LIB_SYSTEM 
KPTResultT
KPT_CALL
KPTDirScanGetFileList(KPTDirListT* aDirHandle,
                      const KPTSysCharT* aDirName, 
                      KPTListT** aFileList);

KPT_LIB_SYSTEM 
KPTResultT
KPT_CALL
KPTDirScanCreateRecursiveFileList(KPTHeapT* aHeap,
                                  uint32_t aOptions,
                                  const KPTSysCharT* aBase,
                                  const KPTSysCharT* aSearch, 
                                  KPTListT** aFileList);

KPT_LIB_SYSTEM 
KPTResultT
KPT_CALL
KPTDirScanGetDirList(KPTDirListT* aDirHandle, 
                     KPTListT** aDirList);

KPT_LIB_SYSTEM 
KPTResultT
KPT_CALL
KPTDirScanGetDirName(KPTDirListT* aDirHandle,
                     KPTSysCharT** aDirName);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* H_KPT_DIRSCAN_H */

