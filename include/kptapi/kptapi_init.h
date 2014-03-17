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
 * @file    kptapi_init.h
 *
 * @brief   Initialisation Types and Structures.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTAPI_INIT_H
#define H_KPTAPI_INIT_H

#include "kptapi_components.h"

/*****************************************************************************
 * Basic Types
 *****************************************************************************/

/** Base initialisation structure. */
typedef struct KPTInitT KPTInitT;
struct KPTInitT
{
	KPTComponentIdT component;      /**< Component to be initialised */
	uint32_t version;               /**< Version of component data */
	intptr_t key;                   /**< Defines the initialisation setting to update */
	intptr_t value;                 /**< Specifies the new value for the setting */
};


/*
 * Initialisation keys
 *
 * The values here are only unique for a given component
 *
 * Other data types (strings, pointers to structures) can be used as keys as well
 * but it makes sense for all keys for a given component to be the same type.
 */

/**
 * Enables or disables Framework command locking [Optional]
 *
 * The KPTInitT::key type is KPTBoolT, either eKPTTrue or eKPTFalse
 */
#define KPT_INIT_FRAMEWORK_LOCKINGENABLED 0x00000001

/**
 * Sets the base path for the Framework's files  [Required]
 *
 * The KPTInitT::key type is const KPTSysCharT*
 */
#define KPT_INIT_FRAMEWORK_BASEPATH       0x00000002

#endif /* #ifndef H_KPTAPI_INIT_H */
