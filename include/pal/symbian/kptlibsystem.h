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
 * @details This file is contains windows specific pragmas that will link to 
 *          the correct system library.
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "kptcompile.h"

#ifndef H_KPT_LIBSYSTEM_H
#define H_KPT_LIBSYSTEM_H

#if defined KPT_LIBSYSTEM_SOURCE

	/* Using the code directly */
	#define KPT_LIB_SYSTEM

#elif defined KPT_LIBSYSTEM_DLL

	/* Using library as a DLL */
	#define KPT_LIB_SYSTEM __declspec(dllimport)

	#if defined _MT

		/* /MD or /MDd (Multithreaded DLL) or /MT or /MTd (Multithreaded) is specified. */
		#if defined _DLL

			/* Defined when /MD or /MDd (Multithread DLL) is specified. */
			#if defined(_DEBUG) || defined(KPT_LIBSYSTEM_DEBUG)
				#pragma comment(lib, "kptsystemDMDd.lib")
			#else
				#pragma comment(lib, "kptsystemDMD.lib")
			#endif

		#else

			#if defined(_DEBUG) || defined(KPT_LIBSYSTEM_DEBUG)
				#pragma comment(lib, "kptsystemDMTd.lib")
			#else
				#pragma comment(lib, "kptsystemDMT.lib")
			#endif

		#endif

	#endif

#elif defined KPT_LIBSYSTEM_CREATEDLL

	/* Creating library as a DLL */
	#define KPT_LIB_SYSTEM __declspec(dllexport)

#elif defined KPT_LIBSYSTEM_CREATELIB

	/* Creating library as a static library */
	#define KPT_LIB_SYSTEM

#else

	/* Using library as a static library */
	#define KPT_LIB_SYSTEM

	#if defined _MT

		/* /MD or /MDd (Multithreaded DLL) or /MT or /MTd (Multithreaded) is specified. */
		#if defined _DLL

			/* Defined when /MD or /MDd (Multithread DLL) is specified. */
			#if defined(_DEBUG) || defined(KPT_LIBSYSTEM_DEBUG)
				#pragma comment(lib, "kptsystemSMDd.lib")
			#else
				#pragma comment(lib, "kptsystemSMD.lib")
			#endif

		#else

			#if defined(_DEBUG) || defined(KPT_LIBSYSTEM_DEBUG)
				#pragma comment(lib, "kptsystemSMTd.lib")
			#else
				#pragma comment(lib, "kptsystemSMT.lib")
			#endif

		#endif

	#endif

#endif

/* Byte order for the Library */
#ifndef KPT_BYTE_ORDER
	#define KPT_BYTE_ORDER KPT_ENDIAN_LITTLE
#endif

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
				| KPTCAT_ALGORITHM \
				/* | KPTCAT_DISALLOWSTATIC */
	#endif
#endif

#endif /* #ifndef H_KPT_LIBSYSTEM_H */
