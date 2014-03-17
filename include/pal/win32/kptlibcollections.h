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
 * @file    kptlibcollections.h
 *
 * @brief   Platform specific defines and includes for Win32.
 *
 * @brief   Include file for KPT Collections library
 *
 * @details This file is contains windows specific pragmas that will link to 
 *          the correct collections library.
 *
 *****************************************************************************/
#pragma once
#ifndef H_KPT_LIBCOLLECTIONS_H
#define H_KPT_LIBCOLLECTIONS_H

#include "kptcompile.h"

#if defined KPT_LIBCOLLECTIONS_SOURCE

	/* Using the code directly */
	#define KPT_LIB_COLLECTIONS

#elif defined KPT_LIBCOLLECTIONS_DLL

	/* Using library as a DLL */
	#define KPT_LIB_COLLECTIONS __declspec(dllimport)

	#if defined _MT

		/* /MD or /MDd (Multithreaded DLL) or /MT or /MTd (Multithreaded) is specified. */
		#if defined _DLL

			/* Defined when /MD or /MDd (Multithread DLL) is specified. */
			#if defined(_DEBUG) || defined(KPT_LIBCOLLECTIONS_DEBUG)
				#pragma comment(lib, "kptcollectionsSMDd.lib")
			#else
				#pragma comment(lib, "kptcollectionsSMD.lib")
			#endif

		#else

			#if defined(_DEBUG) || defined(KPT_LIBCOLLECTIONS_DEBUG)
				#pragma comment(lib, "kptcollectionsSMTd.lib")
			#else
				#pragma comment(lib, "kptcollectionsSMT.lib")
			#endif

		#endif

	#endif

#elif defined KPT_LIBCOLLECTIONS_CREATEDLL

	/* Creating library as a DLL */
	#define KPT_LIB_COLLECTIONS __declspec(dllexport)

#elif defined KPT_LIBCOLLECTIONS_CREATELIB

	/* Creating library as a static library */
	#define KPT_LIB_COLLECTIONS

#else

	/* Using library as a static library */
	#define KPT_LIB_COLLECTIONS

	#if defined _MT

		/* /MD or /MDd (Multithreaded DLL) or /MT or /MTd (Multithreaded) is specified. */
		#if defined _DLL

			/* Defined when /MD or /MDd (Multithread DLL) is specified. */
			#if defined(_DEBUG) || defined(KPT_LIBCOLLECTIONS_DEBUG)
				#pragma comment(lib, "kptcollectionsSMDd.lib")
			#else
				#pragma comment(lib, "kptcollectionsSMD.lib")
			#endif

		#else

			#if defined(_DEBUG) || defined(KPT_LIBCOLLECTIONS_DEBUG)
				#pragma comment(lib, "kptcollectionsSMTd.lib")
			#else
				#pragma comment(lib, "kptcollectionsSMT.lib")
			#endif

		#endif

	#endif

#endif

#endif /* #ifndef H_KPT_LIBCOLLECTIONS_H */
