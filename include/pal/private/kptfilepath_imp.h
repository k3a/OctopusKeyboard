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
 * @file    kptfilepath_imp.h
 * 
 * @brief   Private implementation structure for the file path
 *
 * @details 
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTFILEPATH_IMP_H
#define H_KPTFILEPATH_IMP_H

#include "kptlibsystem.h"
#include "kptapi.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Implementation of KPTFilePath */
struct KPTFilePathT
{
	/** Number of characters in the path (not including terminator) */
	size_t length;

	/** Maximum number of characters in the path (not including terminator) */
	size_t maxLength;

	/** The heap used to allocate memory for the buffer */
	KPTHeapT* heap;

	/** Start of the character buffer. */
	KPTSysCharT buffer[1];
};

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* H_KPTFILEPATH_IMP_H */
