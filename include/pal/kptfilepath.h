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
 * @file kptfilepath.h
 *
 * @brief File path manipulation object.
 *
 * @details 
 *
 ****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPT_FILEPATH_H
#define H_KPT_FILEPATH_H

#include "kptlibsystem.h"
#include "kptapi.h"
#include "kptheap.h"
#include "kptfilepath_platform.h"

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus */

enum KPTDirSpecialT
{
	eKPTDirPrograms = 0,	/**< User's program folder */
	eKPTDirSystem = 1,		/**< Base system folder */
	eKPTDirTemp = 2,		/**< Temporary folder */
	eKPTDirApplication = 3	/**< Application Path*/
};
typedef enum KPTDirSpecialT KPTDirSpecialT;


DECLARE_KPTHANDLE(KPTFilePathT)

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFilePathCreate(KPTFilePathT** aHandle,
                  KPTHeapT* aHeap,
                  size_t aMaxLength);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFilePathDestroy(KPTFilePathT** aHandle);

KPT_LIB_SYSTEM
const KPTSysCharT*
KPT_CALL
KPTFilePathGetString(const KPTFilePathT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFilePathGetDir(const KPTFilePathT* aHandle,
                  KPTSysCharT* aDirectory,
                  size_t* aSize);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFilePathGetFileName(const KPTFilePathT* aHandle,
                       KPTSysCharT* aFileName, 
                       size_t* aSize);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFilePathGetTitle(const KPTFilePathT* aHandle,
                    KPTSysCharT* aTitle,
                    size_t* aSize);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFilePathGetExtension(const KPTFilePathT* aHandle,
                        KPTSysCharT* aExtension,
                        size_t* aSize);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL 
KPTFilePathAppend(KPTFilePathT* aHandle,
                  const KPTSysCharT* aPathToAdd,
                  KPTBoolT aAddDirDelim);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFilePathCombine(KPTFilePathT* aHandle,
                   const KPTSysCharT* aDirectory,
                   const KPTSysCharT* aFileName);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFilePathCombineExt(KPTFilePathT* aHandle,
                      const KPTSysCharT* aDirectory,
                      const KPTSysCharT* aTitle,
                      const KPTSysCharT* aExtension);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFilePathChangeExtenstion(KPTFilePathT* aHandle,
                            const KPTSysCharT* aExtension);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFilePathRemoveExtension(KPTFilePathT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFilePathRemoveFileName(KPTFilePathT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFilePathClear(KPTFilePathT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFilePathGetBufferLength(const KPTFilePathT* aHandle,
                           size_t* aLength);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFilePathGetBufferMaxLength(const KPTFilePathT* aHandle,
                              size_t* aMaxLength);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFilePathGetTempFolder(KPTFilePathT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFilePathGetSpecialFolder(KPTFilePathT* aHandle,
                            KPTDirSpecialT aSpecial);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFilePathGetTempFileName(KPTFilePathT* aHandle, 
                           const KPTSysCharT* aDirectory, 
                           const KPTSysCharT* aPrefix);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFilePathFullPath(KPTFilePathT* aHandle,
                    const KPTSysCharT* aRelativePath);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFilePathFindWildCard(KPTFilePathT* aHandle,
                        size_t* aOffset, 
                        size_t* aLength);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFilePathEndMatches(const KPTFilePathT* aHandle,
                      const KPTFilePathT* aPath,
                      size_t aStrLen,
                      KPTBoolT* aResult);

KPT_LIB_SYSTEM
KPTBoolT
KPT_CALL
KPTFilePathIsDirDelim(KPTSysCharT aChar);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* H_KPT_FILEPATH_H */
