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
 * @file    kptapi_components.h
 *
 * @brief   Types and defines for Component Management.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTAPI_COMPONENTS_H
#define H_KPTAPI_COMPONENTS_H

/** Component Identifier */
typedef uint32_t KPTComponentIdT;

/** Component Type (@ref kptapi_componenttypes.h) */
typedef uint32_t KPTComponentTypeT;

/** State information for a single component */
typedef struct KPTComponentInfoT KPTComponentInfoT;

/** State information for a single component */
struct KPTComponentInfoT
{
	KPTComponentIdT componentId;        /**< Runtime identifier for the component */
	KPTComponentTypeT componentType;    /**< Component type (@ref kptapi_componenttypes.h)*/
	uint32_t version;                   /**< Component version */
	KPTBoolT isLoaded;                  /**< Loaded state */
	KPTBoolT isActive;                  /**< Active state */
	intptr_t extraDetails;              /**< This field depends on the component type (@ref kptapi_componenttypes.h)*/
};

/** A container for KPTComponentInfoT items */
typedef struct KPTComponentListAllocT KPTComponentListAllocT;
struct KPTComponentListAllocT
{
	KPTComponentInfoT* components;      /**< list of components */
	size_t count;                       /**< number of components */
};

/** Value for unassigned component IDs */
#define KPT_COMPONENTID_INVALID 0

#endif /* #ifndef H_KPTAPI_COMPONENTS_H */
