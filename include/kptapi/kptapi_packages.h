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
 * @file    kptapi_packages.h
 *
 * @brief   Structures for API package operations.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTAPI_PACKAGE_H
#define H_KPTAPI_PACKAGE_H

#include "kptapi_dict.h"
#include "kptapi_lang.h"

/** Identifier for an installed package; persisted for the installed lifetime of a package */
typedef uint32_t KPTPackageInstalledIdT;

/** Structure describing a component inside a package */
typedef struct KPTPackageComponentInfoT KPTPackageComponentInfoT;
struct KPTPackageComponentInfoT
{
	KPTComponentIdT id;         /**< Component Id */
	uint32_t type;              /**< Component type (@ref kptapi_componenttypes.h)*/
	uint32_t version;           /**< Component version */
	KPTLanguageT language;      /**< Language - set if appropriate */
	intptr_t extraDetails;      /**< This field depends on the component type (@ref kptapi_componenttypes.h)*/
};

/** Structure describing the contents of an available package */
typedef struct KPTPackageAvailableInfoT KPTPackageAvailableInfoT;
struct KPTPackageAvailableInfoT
{
	const KPTSysCharT* packageName;              /**< Name of package file (including path) */
	const KPTPackageComponentInfoT* components;  /**< List of components in package */
	size_t componentCount;                       /**< Number of components in list */
};

/** Structure containing a list of details of available packages */
typedef struct KPTPackageAvailableListAllocT KPTPackageAvailableListAllocT;
struct KPTPackageAvailableListAllocT
{
	KPTPackageAvailableInfoT* packages;     /**< List of package details */
	size_t count;                           /**< Number of items in list */
};

/** Structure describing the contents of an installed package */
typedef struct KPTPackageInstalledInfoT KPTPackageInstalledInfoT;
struct KPTPackageInstalledInfoT
{
	KPTPackageInstalledIdT packageId;            /**< Installed package identifier */
	const KPTSysCharT* packageName;              /**< Original filename of package file */
	KPTPackageComponentInfoT* components;  /**< List of components in package */
	size_t componentCount;                       /**< Number of components in list */
};

/** Structure containing a list of details of installed packages */
typedef struct KPTPackageInstalledListAllocT KPTPackageInstalledListAllocT;
struct KPTPackageInstalledListAllocT
{
	KPTPackageInstalledInfoT* packages;     /**< List of package details */
	size_t count;                           /**< Number of items in list */
};

#endif /* #ifndef H_KPTAPI_PACKAGE_H */
