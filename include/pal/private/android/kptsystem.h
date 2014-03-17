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
 * @brief   Platform specific defines and includes for Android.
 *
 * @details This file contains platform defines that are used internally.
 *  - Each core source file should include this file.
 *  - Each project should set the include path for the appropriate platform.
 *  - This file should not be included by any other header file.
 *
 *****************************************************************************/

#ifndef H_KPTYSTEM_H
#define H_KPTYSTEM_H

/*
 * Platform includes
 */

#include <wchar.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>
#include <ctype.h>
#include <sys/types.h>

/* KPT headers */
#include "kptid.h"
#include "kptapi.h"
#include "kptstatus.h"
#include "kptbyte.h"
#include "kptout.h"
#include "kpterrorstack.h"
#include "kpterr.h"
#include "kptassert.h"

#endif /* H_KPTYSTEM_H */
