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
 * @file    kptapi_componenttypes.h
 *
 * @brief   Defines and structures for API component types.
 *
 * @details 
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTAPI_COMPONENTTYPES_H
#define H_KPTAPI_COMPONENTTYPES_H

#include "kptapi_dict.h"

/** Component type base value (not used directly) */
#define KPT_COMPONENTTYPE                0x00000000

/** Application component type */
#define KPT_COMPONENTTYPE_ADAPTXTENGINE  (KPT_COMPONENTTYPE + 1)

/** Dictionary component type */
#define KPT_COMPONENTTYPE_DICTIONARY     (KPT_COMPONENTTYPE + 2)


/** 
 * KPTComponentExtra...T (eg KPTComponentExtraDictionaryT) begin with a uint32.
 * So components' "Extra Details" space must be rounded up to end on a 4-byte boundary
 */
#define KPT_COMPONENTEXTRA_ALIGNMENTSIZE 4


/**
 * Extra details structure for @ref KPT_COMPONENTTYPE_DICTIONARY type.
 * To access this information the caller must cast the field KPTComponentInfoT::extraDetails 
 * to a const KPTComponentExtraDictionaryT*.
*/
typedef struct KPTComponentExtraDictionaryT KPTComponentExtraDictionaryT;
struct KPTComponentExtraDictionaryT
{
	uint32_t type;              /**< Component type.*/
	KPTDictInfoT dictInfo;      /**< Dictionary detail information.*/
	KPTDictStateT dictState;    /**< Dictionary state information.*/
};

#endif /* #ifndef H_KPTAPI_COMPONENTTYPES_H */
