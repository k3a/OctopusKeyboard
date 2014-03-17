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
 * @file    kptlibcode.h
 *
 * @brief   Include file for the KPT code library
 *
 * @details This file is contains windows specific pragmas that will link to 
 *          the correct code library.
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "kptcompile.h"

#ifndef H_KPT_LIBCODE_H
#define H_KPT_LIBCODE_H

#if defined KPT_LIBCODE_SOURCE

	/* Using the code directly */
	#define KPT_LIB_CODE

#elif defined KPT_LIBCODE_DLL

	/* Using library as a DLL */
	#define KPT_LIB_CODE __declspec(dllimport)

	#if defined _MT

		/* /MD or /MDd (Multithreaded DLL) or /MT or /MTd (Multithreaded) is specified. */
		#if defined _DLL

			/* Defined when /MD or /MDd (Multithread DLL) is specified. */
			#if defined(_DEBUG) || defined(KPT_LIBCODE_DEBUG)
				#pragma comment(lib, "kptcodeDMDd.lib")
			#else
				#pragma comment(lib, "kptcodeDMD.lib")
			#endif

		#else

			#if defined(_DEBUG) || defined(KPT_LIBCODE_DEBUG)
				#pragma comment(lib, "kptcodeDMTd.lib")
			#else
				#pragma comment(lib, "kptcodeDMT.lib")
			#endif

		#endif

	#endif

#elif defined KPT_LIBCODE_CREATEDLL

	/* Creating library as a DLL */
	#define KPT_LIB_CODE __declspec(dllexport)

#elif defined KPT_LIBCODE_CREATELIB

	/* Creating library as a static library */
	#define KPT_LIB_CODE

#else

	/* Using library as a static library */
	#define KPT_LIB_CODE

	#if defined _MT

		/* /MD or /MDd (Multithreaded DLL) or /MT or /MTd (Multithreaded) is specified. */
		#if defined _DLL

			/* Defined when /MD or /MDd (Multithread DLL) is specified. */
			#if defined(_DEBUG) || defined(KPT_LIBCODE_DEBUG)
				#pragma comment(lib, "kptcodeSMDd.lib")
			#else
				#pragma comment(lib, "kptcodeSMD.lib")
			#endif

		#else

			#if defined(_DEBUG) || defined(KPT_LIBCODE_DEBUG)
				#pragma comment(lib, "kptcodeSMTd.lib")
			#else
				#pragma comment(lib, "kptcodeSMT.lib")
			#endif

		#endif

	#endif

#endif

/* Compile categories for the Library */
#ifndef KPT_LIBCODE_CATEGORY
	#ifdef NDEBUG
		#define KPT_LIBCODE_CATEGORY \
				KPTCAT_ERROR \
				| KPTCAT_WARNING
	#else
		#define KPT_LIBCODE_CATEGORY \
				KPTCAT_ERROR \
				| KPTCAT_WARNING \
				| KPTCAT_INFORMATION \
				| KPTCAT_DEBUG \
				| KPTCAT_PERFORMANCE \
				| KPTCAT_ALGORITHM
	#endif
#endif

#endif /* #ifndef H_KPT_LIBCODE_H */
