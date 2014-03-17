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
 * @file kptunicodebinarydata.h                                                               
 * 
 * @brief Parses the unicode binary file and sores the data in a heap array.
 *
 * @details 
 *
 ****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPT_UNICODEBINARYDATA_H__
#define H_KPT_UNICODEBINARYDATA_H__

#include "kptapi.h"
#include "kptheap.h"
#include "kptunicodetable.h"
#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus */

KPTResultT 
KPT_CALL
KPTUnicodeBinaryDataParseFile(KPTPalUnicodeTableT* aUnicodeTable, KPTHeapT* aKptHeap);

KPTResultT 
KPT_CALL
KPTUnicodeBinaryDataDestroyTables(KPTPalUnicodeTableT* aUnicodeTable, KPTHeapT* aKptHeap);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* H_KPT_UNICODEBINARYDATA_H__ */

