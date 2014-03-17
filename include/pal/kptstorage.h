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
 * @file    kptstorage.h
 *
 * @brief   Interface declaration for storage.
 *
 * @details 
 * 
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTSTORAGE_H
#define H_KPTSTORAGE_H

#include "kptlibsystem.h"
#include "kptapi.h"
#include "kptfilepath.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStorageGetFreeSpaceFromString(const KPTSysCharT* aPath,
                                 uint64_t* aFreeSpace);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStorageGetFreeSpaceFromPath(const KPTFilePathT* aFilePath,
                               uint64_t* aFreeSpace);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* H_KPTSTORAGE_H */
