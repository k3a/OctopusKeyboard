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
 * @details This file is contains windows specific pragmas that will link to 
 *          the correct system memory library.
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "kptcompile.h"

#ifndef H_KPT_LIBSYSMEM_H
#define H_KPT_LIBSYSMEM_H

#if defined KPT_LIBSYSMEM_SOURCE

	/* Using the code directly */
	#define KPT_LIB_SYSMEM

#elif defined KPT_LIBSYSMEM_DLL

	/* Using library as a DLL */
	#define KPT_LIB_SYSMEM __declspec(dllimport)

	#if defined _MT

		/* /MD or /MDd (Multithreaded DLL) or /MT or /MTd (Multithreaded) is specified. */
		#if defined _DLL

			/* Defined when /MD or /MDd (Multithread DLL) is specified. */
			#if defined(_DEBUG) || defined(KPT_LIBSYSMEM_DEBUG)
				#pragma comment(lib, "kptsysmemDMDd.lib")
			#else
				#pragma comment(lib, "kptsysmemDMD.lib")
			#endif

		#else

			#if defined(_DEBUG) || defined(KPT_LIBSYSMEM_DEBUG)
				#pragma comment(lib, "kptsysmemDMTd.lib")
			#else
				#pragma comment(lib, "kptsysmemDMT.lib")
			#endif

		#endif

	#endif

#elif defined KPT_LIBSYSMEM_CREATEDLL

	/* Creating library as a DLL */
	#define KPT_LIB_SYSMEM __declspec(dllexport)

#elif defined KPT_LIBSYSMEM_CREATELIB

	/* Creating library as a static library */
	#define KPT_LIB_SYSMEM

#else

	/* Using library as a static library */
	#define KPT_LIB_SYSMEM

	#if defined _MT

		/* /MD or /MDd (Multithreaded DLL) or /MT or /MTd (Multithreaded) is specified. */
		#if defined _DLL

			/* Defined when /MD or /MDd (Multithread DLL) is specified. */
			#if defined(_DEBUG) || defined(KPT_LIBSYSMEM_DEBUG)
				#pragma comment(lib, "kptsysmemSMDd.lib")
			#else
				#pragma comment(lib, "kptsysmemSMD.lib")
			#endif

		#else

			#if defined(_DEBUG) || defined(KPT_LIBSYSMEM_DEBUG)
				#pragma comment(lib, "kptsysmemSMTd.lib")
			#else
				#pragma comment(lib, "kptsysmemSMT.lib")
			#endif

		#endif

	#endif

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
