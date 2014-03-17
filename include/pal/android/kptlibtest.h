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
 * @file    kpttestlib.h
 * 
 * @brief   Include file for KPT Test library
 *
 * @details This file is contains android specific defines to allow the library to be used.
 *
 *****************************************************************************/
#pragma once
#ifndef H_KPT_LIBTEST_H
#define H_KPT_LIBTEST_H

#include "kptcompile.h"

#if defined KPT_LIBTEST_DLL

	/* Using library as a DLL */
	#define KPT_LIB_TEST __declspec(dllimport)

#elif defined KPT_LIBTEST_CREATEDLL

	/* Creating library as a DLL */
	#define KPT_LIB_TEST __declspec(dllexport)

#elif defined KPT_LIBTEST_CREATELIB

	/* Creating library as a static library */
	#define KPT_LIB_TEST

#else

	/* Using library as a static library */
	#define KPT_LIB_TEST

#endif

#endif /* #ifndef H_KPT_LIBTEST_H */
