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
 * @file    kptapi_dispatch.h
 *
 * @brief   Dispatch Interface
 *
 * @details 
 *  
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTAPI_DISPATCH_H
#define H_KPTAPI_DISPATCH_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

KPT_LIB_API
KPTResultT
KPT_CALL
KPTFwkRunCmd(uint32_t aCommand,
             intptr_t aFirst,
             intptr_t aSecond);


KPT_LIB_API
KPTResultT
KPT_CALL
KPTFwkCancelCmd(void);

#ifdef __cplusplus
}
#endif /*__cplusplus */


#endif /* #ifndef H_KPTAPI_DISPATCH_H */
