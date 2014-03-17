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
 * @file    kptlibapi.h
 *
 * @brief   Include file for the KPT API library (Win32)
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "kptcompile.h"

#ifndef H_KPT_LIBAPI_H
#define H_KPT_LIBAPI_H

#if defined KPT_LIBAPI_DLL

	/* Using library as a DLL */
	#define KPT_LIB_API __declspec(dllimport)

	#if defined _MT

		/* /MD or /MDd (Multithreaded DLL) or /MT or /MTd (Multithreaded) is specified. */
		#if defined _DLL

			/* Defined when /MD or /MDd (Multithread DLL) is specified. */
			#if defined(_DEBUG)
				#pragma comment(lib, "kptframeworkv2DMDd.lib")
			#else
				#pragma comment(lib, "kptframeworkv2DMD.lib")
			#endif

		#else

			#if defined(_DEBUG)
				#pragma comment(lib, "kptframeworkv2DMTd.lib")
			#else
				#pragma comment(lib, "kptframeworkv2DMT.lib")
			#endif

		#endif

	#endif

#elif defined KPT_LIBAPI_CREATEDLL

	/* Creating library as a DLL */
	#define KPT_LIB_API __declspec(dllexport)

#elif defined KPT_LIBAPI_LIB

	/* Using library as a static library */
	#define KPT_LIB_API

	#if defined _MT

		/* /MD or /MDd (Multithreaded DLL) or /MT or /MTd (Multithreaded) is specified. */
		#if defined _DLL

			/* Defined when /MD or /MDd (Multithread DLL) is specified. */
			#if defined(_DEBUG)
				#pragma comment(lib, "kptframeworkv2SMDd.lib")
			#else
				#pragma comment(lib, "kptframeworkv2SMD.lib")
			#endif

		#else

			#if defined(_DEBUG)
				#pragma comment(lib, "kptframeworkv2SMTd.lib")
			#else
				#pragma comment(lib, "kptframeworkv2SMT.lib")
			#endif

		#endif

	#endif

#elif defined KPT_LIBAPI_CREATELIB

	/* Creating library as a static library */
	#define KPT_LIB_API

#else

	/* No specification */
	#define KPT_LIB_API

#endif

#endif /* #ifndef H_KPT_LIBAPI_H */
