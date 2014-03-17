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
 * @file kptdirmanager.h
 *
 * @brief Directory manager.
 *
 * @details 
 *
 ****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPT_DIRMANAGER_H
#define H_KPT_DIRMANAGER_H

#include "kptlibsystem.h"
#include "kptapi.h"

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus */

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTDirManagerDirExists(const KPTSysCharT* aPath, 
                       KPTBoolT* aDirExists);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTDirManagerCreateDir(const KPTSysCharT* aDirPath);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTDirManagerCreateDirPath(const KPTSysCharT* aDirPath);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTDirManagerDeleteDir(const KPTSysCharT* aDirPath);

KPT_LIB_SYSTEM 
KPTResultT
KPT_CALL
KPTDirManagerDeleteTree(const KPTSysCharT* aPath);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTDirManagerMoveDir(const KPTSysCharT* aExistingDirName, 
                     const KPTSysCharT* aNewDirName, 
                     KPTBoolT aReplaceExisting);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTDirManagerRenameDir(const KPTSysCharT* aExistingDirName, 
                       const KPTSysCharT* aNewDirName, 
                       KPTBoolT aReplaceExisting);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTDirManagerCopyDir(const KPTSysCharT* aExistingDirName, 
                     const KPTSysCharT* aNewDirName, 
                     KPTBoolT aReplaceExisting);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* H_KPT_DIRMANAGER_H */
