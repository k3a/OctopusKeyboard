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
 * @brief   Platform specific defines and includes for Win32.
 *
 * @brief   Include file for KPT unicode library
 *
 * @details This file is contains windows specific pragmas that will link to 
 *          the correct unicode library.
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif
#include "kptcompile.h"
#ifndef H_KPT_LIBUNICODE_H
#define H_KPT_LIBUNICODE_H

#if defined KPT_LIBUNICODE_SOURCE

	/* Using the code directly */
	#define KPT_LIB_UNICODE

#elif defined KPT_LIBUNICODE_DLL

	/* Using library as a DLL */
	#define KPT_LIB_UNICODE __declspec(dllimport)

	#if defined _MT

		/* /MD or /MDd (Multithreaded DLL) or /MT or /MTd (Multithreaded) is specified. */
		#if defined _DLL

			/* Defined when /MD or /MDd (Multithread DLL) is specified. */
			#if defined(_DEBUG) || defined(KPT_LIBUNICODE_DEBUG)
				#pragma comment(lib, "kptunicodeSMDd.lib")
			#else
				#pragma comment(lib, "kptunicodeSMD.lib")
			#endif

		#else

			#if defined(_DEBUG) || defined(KPT_LIBUNICODE_DEBUG)
				#pragma comment(lib, "kptunicodeSMTd.lib")
			#else
				#pragma comment(lib, "kptunicodeSMT.lib")
			#endif

		#endif

	#endif

#elif defined KPT_LIBUNICODE_CREATEDLL

	/* Creating library as a DLL */
	#define KPT_LIB_UNICODE __declspec(dllexport)

#elif defined KPT_LIBUNICODE_CREATELIB

	/* Creating library as a static library */
	#define KPT_LIB_UNICODE

#else

	/* Using library as a static library */
	#define KPT_LIB_UNICODE

	#if defined _MT

		/* /MD or /MDd (Multithreaded DLL) or /MT or /MTd (Multithreaded) is specified. */
		#if defined _DLL

			/* Defined when /MD or /MDd (Multithread DLL) is specified. */
			#if defined(_DEBUG) || defined(KPT_LIBUNICODE_DEBUG)
				#pragma comment(lib, "kptunicodeSMDd.lib")
			#else
				#pragma comment(lib, "kptunicodeSMD.lib")
			#endif

		#else

			#if defined(_DEBUG) || defined(KPT_LIBUNICODE_DEBUG)
				#pragma comment(lib, "kptunicodeSMTd.lib")
			#else
				#pragma comment(lib, "kptunicodeSMT.lib")
			#endif

		#endif

	#endif

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
	#endif
#endif

#endif /* #ifndef H_KPT_LIBUNICODE_H */
