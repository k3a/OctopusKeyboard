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
 * @file    kptlibutil.h
 *
 * @brief   Include file for the KPT util library
 *
 * @details This file is contains windows specific pragmas that will link to 
 *          the correct util library.
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "kptcompile.h"

#ifndef H_KPT_LIBUTIL_H
#define H_KPT_LIBUTIL_H

#if defined KPT_LIBUTIL_SOURCE

	/* Using the util directly */
	#define KPT_LIB_UTIL

#elif defined KPT_LIBUTIL_DLL

	/* Using library as a DLL */
	#define KPT_LIB_UTIL __declspec(dllimport)

	#if defined _MT

		/* /MD or /MDd (Multithreaded DLL) or /MT or /MTd (Multithreaded) is specified. */
		#if defined _DLL

			/* Defined when /MD or /MDd (Multithread DLL) is specified. */
			#if defined(_DEBUG) || defined(KPT_LIBUTIL_DEBUG)
				#pragma comment(lib, "kptutilDMDd.lib")
			#else
				#pragma comment(lib, "kptutilDMD.lib")
			#endif

		#else

			#if defined(_DEBUG) || defined(KPT_LIBUTIL_DEBUG)
				#pragma comment(lib, "kptutilDMTd.lib")
			#else
				#pragma comment(lib, "kptutilDMT.lib")
			#endif

		#endif

	#endif

#elif defined KPT_LIBUTIL_CREATEDLL

	/* Creating library as a DLL */
	#define KPT_LIB_UTIL __declspec(dllexport)

#elif defined KPT_LIBUTIL_CREATELIB

	/* Creating library as a static library */
	#define KPT_LIB_UTIL

#else

	/* Using library as a static library */
	#define KPT_LIB_UTIL

	#if defined _MT

		/* /MD or /MDd (Multithreaded DLL) or /MT or /MTd (Multithreaded) is specified. */
		#if defined _DLL

			/* Defined when /MD or /MDd (Multithread DLL) is specified. */
			#if defined(_DEBUG) || defined(KPT_LIBUTIL_DEBUG)
				#pragma comment(lib, "kptutilSMDd.lib")
			#else
				#pragma comment(lib, "kptutilSMD.lib")
			#endif

		#else

			#if defined(_DEBUG) || defined(KPT_LIBUTIL_DEBUG)
				#pragma comment(lib, "kptutilSMTd.lib")
			#else
				#pragma comment(lib, "kptutilSMT.lib")
			#endif

		#endif

	#endif

#endif

/* Compile categories for the Library */
#ifndef KPT_LIBUTIL_CATEGORY
	#ifdef NDEBUG
		#define KPT_LIBUTIL_CATEGORY \
				KPTCAT_ERROR \
				| KPTCAT_WARNING
	#else
		#define KPT_LIBUTIL_CATEGORY \
				KPTCAT_ERROR \
				| KPTCAT_WARNING \
				| KPTCAT_INFORMATION \
				| KPTCAT_DEBUG \
				| KPTCAT_PERFORMANCE \
				| KPTCAT_ALGORITHM
	#endif
#endif

#endif /* #ifndef H_KPT_LIBUTIL_H */
