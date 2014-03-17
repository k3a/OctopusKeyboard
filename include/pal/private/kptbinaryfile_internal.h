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
 * @file    kptbinaryfile_internal.h
 * 
 * @brief   Internal binary file header declarations
 *
 * @details
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTBINARYFILE_INTERNAL_H
#define H_KPTBINARYFILE_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
 * Function to hide the way that the platform gets a standard C file handle.
 */
FILE* KPTBinaryFileOpenPlatform(uint32_t aOptions,
                                const KPTSysCharT* aPath,
                                KPTResultT* result,
                                uint32_t* aOSError);

/*
 * Function to hide the way that the platform gets a file length.
 */
KPTResultT KPTBinaryFileGetLengthPlatform(FILE* aFile,
                                          size_t* aSize,
                                          uint32_t* aOSError);


#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTBINARYFILE_INTERNAL_H*/
