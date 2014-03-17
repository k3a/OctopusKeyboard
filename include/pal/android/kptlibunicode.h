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
 * @file    kptlibunicode.h
 *
 * @brief   Platform specific defines and includes for Android.
 *
 * @brief   Include file for KPT unicode library
 *
 * @details This file is contains windows specific pragmas that will link to 
 *          the correct unicode library.
 *
 *****************************************************************************/

#include "kptcompile.h"
#ifndef H_KPT_LIBUNICODE_H
#define H_KPT_LIBUNICODE_H

#if defined KPT_LIBUNICODE_SOURCE

	/* Using the code directly */
	#define KPT_LIB_UNICODE

#elif defined KPT_LIBUNICODE_DLL

	/* Using library as a DLL */
	#define KPT_LIB_UNICODE __declspec(dllimport)
	

#elif defined KPT_LIBUNICODE_CREATEDLL

	/* Creating library as a DLL */
	#define KPT_LIB_UNICODE __declspec(dllexport)

#elif defined KPT_LIBUNICODE_CREATELIB

	/* Creating library as a static library */
	#define KPT_LIB_UNICODE

#else

	/* Using library as a static library */
	#define KPT_LIB_UNICODE
	
#endif

/* Compile categories for the Library */
#ifndef KPT_LIBUNICODE_CATEGORY
	#ifdef NDEBUG
		#define KPT_LIBUNICODE_CATEGORY \
				KPTCAT_ERROR \
				| KPTCAT_WARNING
	#else
		#define KPT_LIBUNICODE_CATEGORY \
				KPTCAT_ERROR \
				| KPTCAT_WARNING \
				| KPTCAT_INFORMATION \
				| KPTCAT_DEBUG \
				| KPTCAT_PERFORMANCE
				/* | KPTCAT_DISALLOWSTATIC */
	#endif
#endif

#endif /* #ifndef H_KPT_LIBUNICODE_H */
