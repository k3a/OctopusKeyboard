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
 * @file    kptdirlist_imp.h
 * 
 * @brief   Private implementation structure for the directory file list
 *
 * @details 
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTDIRLIST_IMP_H
#define H_KPTDIRLIST_IMP_H

#include "kptlibsystem.h"
#include "kptapi.h"
#include "kptlist.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/**
 * Private implementation structure for directory listings
 */
struct KPTDirListT
{
	KPTSysCharT* dirName;
	KPTHeapT* kptHeap;
	KPTListT* dirList;
	KPTListT* fileList;
};

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* H_KPTDIRLIST_IMP_H*/
