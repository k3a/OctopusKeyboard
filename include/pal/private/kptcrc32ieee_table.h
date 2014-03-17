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
 * @file    kptcrc32ieee_table.h
 * 
 * @brief   Private implementation structure for heap objects
 *
 * @details 
 *  
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTCRC32IEEE_TABLE_H
#define H_KPTCRC32IEEE_TABLE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern 
const uint32_t* KPTCrc32IeeeGetTable();

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTCRC32IEEE_TABLE_H */
