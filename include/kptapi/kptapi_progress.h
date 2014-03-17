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
 * @file    kptapi_progress.h
 *
 * @brief   Progress types.
 *
 * @details
 *  
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTAPI_PROGRESS_H
#define H_KPTAPI_PROGRESS_H

#include "kptapi.h"

/** Progress item */
typedef struct KPTProgressItemT KPTProgressItemT;
struct KPTProgressItemT
{
	size_t maximum;     /**< Maximum value */
	size_t position;    /**< Position */
};

/** Progress data */
typedef struct KPTProgressDataT KPTProgressDataT;
struct KPTProgressDataT
{
	KPTProgressItemT current;   /**< Progress for current item */
	KPTProgressItemT overall;   /**< Progress for overall operation */
};

/**
 * Function signature for progress callbacks.
 *
 * @param[in] aProgress Progress information returned with the callback.
 * @param[in] aContext  User provided information associated with the callback.
 * @return              KPTResultT.
 */
typedef KPTResultT (KPT_CALLB *KPTProgressFnT)(const KPTProgressDataT* aProgress, intptr_t aContext);

#endif /* #ifndef H_KPTAPI_PROGRESS_H */
