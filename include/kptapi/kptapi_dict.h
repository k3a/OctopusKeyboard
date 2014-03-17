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
 * @file    kptapi_dict.h
 *
 * @brief   Types and defines for Dictionary Management.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTAPI_DICT_H
#define H_KPTAPI_DICT_H

#include "kptapi_lang.h"
#include "kptapi_components.h"

/**
 * State information for a single dictionary component.
 */
typedef struct KPTDictStateT KPTDictStateT;
struct KPTDictStateT
{
	uint32_t fieldMask;                 /**< Identifies fields in use (@ref KPTDictStateMaskT)*/
	KPTComponentIdT componentId;        /**< Component identifier */
	KPTBoolT dictActive;                /**< If eKPTTrue, the dictionary is active */
	uint32_t dictPriority;              /**< Dictionary priority (from 0 to (numInstalledDicts - 1))*/
	KPTBoolT dictLoaded;                /**< If eKPTTrue, the dictionary is loaded */
};

/**
 * Field-in-use masks for KPTDictStateT::fieldMask
 */
enum KPTDictStateMaskT
{
	eKPTDictStateActive = KPTBIT(0),    /**< KPTDictStateT::dictActive sets, or gets, 
                                            a value that indicates whether the dictionary is active */

	eKPTDictStatePriority = KPTBIT(1),  /**< KPTDictStateT::dictPriority sets, or gets, 
                                            a value that indicates the dictionary priority */

	eKPTDictStateLoaded = KPTBIT(2),    /**< KPTDictStateT::dictLoaded indicates the loaded state */

};
typedef enum KPTDictStateMaskT KPTDictStateMaskT;

/**
 * Summary information for a dictionary component.
 * Used when loading or unloading a dictionary. Also used to
 * provide dictionary information when listing installed dictionaries.
 */
typedef struct KPTDictInfoT KPTDictInfoT;
struct KPTDictInfoT
{
	uint32_t fieldMask;                 /**< Identifies fields in use (@ref KPTDictInfoMaskT).
                                                 This value is a bitmask.*/
	KPTSysCharT* dictFileName;          /**< Dictionary file name. */
	KPTUniCharT* dictDisplayName;       /**< Name for display purposes. */
	KPTLanguageInfoT dictLanguage;      /**< Dictionary language (runtime id and BCP47 value). */
	uint32_t dictVersion;               /**< Dictionary version */
};

/**
 * Field-in-use masks for KPTDictInfoT::fieldMask
 */
enum KPTDictInfoMaskT
{
	eKPTDictInfoFileName = KPTBIT(0),       /**< KPTDictInfoT::dictFileName indicates the file name */
	eKPTDictInfoDisplayName = KPTBIT(1),    /**< KPTDictInfoT::dictDisplayName indicates the display name */
	eKPTDictInfoLanguage = KPTBIT(2),       /**< KPTDictInfoT::dictLanguage indicates the language */
	eKPTDictInfoVersion = KPTBIT(3)         /**< KPTDictInfoT::dictVersion indicates the version */
};
typedef enum KPTDictInfoMaskT KPTDictInfoMaskT;

/**
 * Contains summary and state information for a set of dictionaries.
 */
typedef struct KPTDictListAllocT KPTDictListAllocT;
struct KPTDictListAllocT
{
	KPTDictInfoT* dictInfo;     /**< Dictionary information */
	KPTDictStateT* dictState;   /**< Dictionary state information */
	size_t count;               /**< Number of dictionaries */
};

#endif /* #ifndef H_KPTAPI_DICT_H */
