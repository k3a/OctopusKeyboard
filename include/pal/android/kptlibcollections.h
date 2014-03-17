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
 * @brief   Platform specific defines and includes for Android.
 *
 * @brief   Include file for KPT Collections library
 *
 * @details This file is contains android specific defines to allow the library to be used.
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

#elif defined KPT_LIBCOLLECTIONS_CREATEDLL

	/* Creating library as a DLL */
	#define KPT_LIB_COLLECTIONS __declspec(dllexport)

#elif defined KPT_LIBCOLLECTIONS_CREATELIB

	/* Creating library as a static library */
	#define KPT_LIB_COLLECTIONS

#else

	/* Using library as a static library */
	#define KPT_LIB_COLLECTIONS

#endif

#endif /* #ifndef H_KPT_LIBCOLLECTIONS_H */
