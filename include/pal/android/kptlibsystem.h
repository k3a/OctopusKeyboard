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
 * @file    kptlibsystem.h
 *
 * @brief   Include file for KPT System library
 *
 * @details This file is contains android specific defines to allow the library to be used.
 *
 *****************************************************************************/

#include "kptcompile.h"

#ifndef H_KPT_LIBSYSTEM_H
#define H_KPT_LIBSYSTEM_H

#if defined KPT_LIBSYSTEM_SOURCE

	/* Using the code directly */
	#define KPT_LIB_SYSTEM

#elif defined KPT_LIBSYSTEM_DLL

	/* Using library as a DLL */
	#define KPT_LIB_SYSTEM __declspec(dllimport)
    
#elif defined KPT_LIBSYSTEM_CREATEDLL

	/* Creating library as a DLL */
	#define KPT_LIB_SYSTEM __declspec(dllexport)

#elif defined KPT_LIBSYSTEM_CREATELIB

	/* Creating library as a static library */
	#define KPT_LIB_SYSTEM

#else

	/* Using library as a static library */
	#define KPT_LIB_SYSTEM


#endif

/* Byte order for the Library */
#ifndef KPT_BYTE_ORDER
	#define KPT_BYTE_ORDER KPT_ENDIAN_LITTLE
#endif

#define KPTBINARYFILE_USE_STD

/* Compile categories for the Library */
#ifndef KPT_LIBSYSTEM_CATEGORY
	#ifdef NDEBUG
		#define KPT_LIBSYSTEM_CATEGORY \
				KPTCAT_ERROR \
				| KPTCAT_WARNING
	#else
		#define KPT_LIBSYSTEM_CATEGORY \
				KPTCAT_ERROR \
				| KPTCAT_WARNING \
				| KPTCAT_INFORMATION \
				| KPTCAT_DEBUG \
				| KPTCAT_PERFORMANCE \
				| KPTCAT_ALGORITHM
				/* | KPTCAT_DISALLOWSTATIC */
	#endif
#endif

#endif /* #ifndef H_KPT_LIBSYSTEM_H */
