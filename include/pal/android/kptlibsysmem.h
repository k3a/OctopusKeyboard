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
 * @file    kptlibsysmem.h
 *
 * @brief   Include file for the KPT system memory library
 *
 * @details This file is contains android specific defines to allow the library to be used.
 *
 *****************************************************************************/

#include "kptcompile.h"

#ifndef H_KPT_LIBSYSMEM_H
#define H_KPT_LIBSYSMEM_H

#if defined KPT_LIBSYSMEM_SOURCE

	/* Using the code directly */
	#define KPT_LIB_SYSMEM

#elif defined KPT_LIBSYSMEM_DLL

	/* Using library as a DLL */
	#define KPT_LIB_SYSMEM __declspec(dllimport)

#elif defined KPT_LIBSYSMEM_CREATEDLL

	/* Creating library as a DLL */
	#define KPT_LIB_SYSMEM __declspec(dllexport)

#elif defined KPT_LIBSYSMEM_CREATELIB

	/* Creating library as a static library */
	#define KPT_LIB_SYSMEM

#else

	/* Using library as a static library */
	#define KPT_LIB_SYSMEM

#endif

/* Compile categories for the Library */
#ifndef KPT_LIBSYSMEM_CATEGORY
	#ifdef NDEBUG
		#define KPT_LIBSYSMEM_CATEGORY \
				KPTCAT_ERROR \
				| KPTCAT_WARNING
	#else
		#define KPT_LIBSYSMEM_CATEGORY \
				KPTCAT_ERROR \
				| KPTCAT_WARNING \
				| KPTCAT_INFORMATION \
				| KPTCAT_DEBUG \
				| KPTCAT_PERFORMANCE \
				| KPTCAT_ALGORITHM
	#endif
#endif

#endif /* #ifndef H_KPT_LIBSYSMEM_H */
