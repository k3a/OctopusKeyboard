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
 * @file    kptapi_create.h
 *
 * @brief   Create types and structures.
 *
 * @details 
 *  
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTAPI_CREATE_H
#define H_KPTAPI_CREATE_H

#include "kptapi_init.h"

/*****************************************************************************
 * Creation Parameters
 *****************************************************************************/

/** Creation initialisation structure type. */
typedef struct KPTCreateParamsT KPTCreateParamsT;
struct KPTCreateParamsT
{
	KPTInitT* initItems;        /**< Initialisation items */
	size_t initItemCount;       /**< Number of initialisation items */
};

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Creates the Framework. */
KPT_LIB_API
KPTResultT
KPT_CALL
KPTFwkCreate(const KPTCreateParamsT* aCreate);

#ifdef __cplusplus
}
#endif /*__cplusplus */


#endif /* #ifndef H_KPTAPI_CREATE_H */
