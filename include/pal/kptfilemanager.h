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
 * @file kptfilemanager.h
 *
 * @brief File manager.
 *
 * @details 
 *
 ****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPT_FILEMANAGER_H
#define H_KPT_FILEMANAGER_H

#include "kptlibsystem.h"
#include "kptapi.h"

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus */

#define FILE_OPERATION_ATTEMPTS       10
#define FILE_OPERATION_INTERVAL       50

/**
 * Attribute options for the file.
 */
enum KPTFileAttributesT
{
	eKPTFileNormal   = KPTBIT(0),   /**< Set Normal attribute to file */
	eKPTFileHidden   = KPTBIT(1),   /**< Set Hidden attribute to file */
	eKPTFileReadOnly = KPTBIT(2)    /**< Set Read only attribute to file */
};
typedef enum KPTFileAttributesT KPTFileAttributesT;

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFileManagerFileExists(const KPTSysCharT* aFileName, 
                         KPTBoolT* aFileExists);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFileManagerDeleteFile(const KPTSysCharT* aFileToDelete, 
                         KPTBoolT aForceRemove);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFileManagerRenameFile(const KPTSysCharT* aExistingFileName, 
                         const KPTSysCharT* aNewFileName, 
                         KPTBoolT aReplaceExisting);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFileManagerMoveFile(const KPTSysCharT* aExistingFileName, 
                       const KPTSysCharT* aNewFileName, 
                       KPTBoolT aReplaceExisting);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFileManagerCopyFile(const KPTSysCharT* aExistingFileName, 
                       const KPTSysCharT* aNewFileName, 
                       KPTBoolT aReplaceExisting);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTFileManagerSetAttributes(const KPTSysCharT* aFileName, 
                            uint32_t aOptions);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* H_KPT_FILEMANAGER_H */
