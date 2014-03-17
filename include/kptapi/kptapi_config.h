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
 * @file    kptapi_config.h
 *
 * @brief   Types and defines for Configuration Management.
 *
 * @details 
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTAPI_CONFIG_H
#define H_KPTAPI_CONFIG_H

/**
 * Values for the locking state.
 */
enum KPTLockingStateT
{
	eKPTLockingInvalid = 0,     /**< Undefined value */
	eKPTLockingOn = 1,          /**< Locking on */
	eKPTLockingOff = 2          /**< Do not lock */
};
typedef enum KPTLockingStateT KPTLockingStateT;

#endif /* #ifndef H_KPTAPI_CONFIG_H */
