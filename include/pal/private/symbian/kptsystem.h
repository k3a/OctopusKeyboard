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
 *
 * @file    kptsystem.h
 * 
 * @brief   Platform specific defines and includes for Win32.
 *
 * @details This file contains platform defines that are used internally.
 *  - Each core source file should include this file.
 *  - Each project should set the include path for the appropriate platform.
 *  - This file should not be included by any other header file.
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


#ifndef H_KPTYSTEM_H
#define H_KPTYSTEM_H

#pragma cplusplus on
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stddef.h>
#include <assert.h>
#include <wchar.h>
#include <ctype.h>

/* KPT headers */
#include "kptid.h"
#include "kptapi.h"
#include "kptstatus.h"
#include "kptbyte.h"
#include "kptout.h"
#include "kpterrorstack.h"
#include "kpterr.h"
#include "kptassert.h"

/* __offsetof__ is a GCC built in macro which is not defined in WINSCW 
 * So define __offsetof for WINSCW without __offsetof__ macro. 
 */
#if defined(__WINS__) || defined(__WINSCW__) 
#ifndef __offsetof__
#undef __offsetof
#define __offsetof(type, field)					\
  ( (reinterpret_cast <size_t>			\
                 (&reinterpret_cast <const volatile char &>	\
                  (static_cast<type *> (0)->field))))

#endif 
#endif

#endif /* H_KPTYSTEM_H */
