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
 * @brief   Platform specific defines and includes for Win Smart Device.
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

/*
 * Platform includes
 */

/* Disable Level 4 warnings from the windows headers. */
#pragma warning(push, 3)

#pragma comment(linker, "/nodefaultlib:libc.lib")
#pragma comment(linker, "/nodefaultlib:libcd.lib")

/* NOTE - this value is not strongly correlated to the Windows CE OS version being targeted */
#define WINVER _WIN32_WCE

#include <ceconfig.h>
#if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
#define SHELL_AYGSHELL
#endif

#ifdef _CE_DCOM
#define _ATL_APARTMENT_THREADED
#endif

#ifdef SHELL_AYGSHELL
#include <aygshell.h>
#pragma comment(lib, "aygshell.lib") 
#endif


/* Windows Header Files: */
#include <windows.h>
#include <winbase.h>

#if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
#ifndef _DEVICE_RESOLUTION_AWARE
#define _DEVICE_RESOLUTION_AWARE
#endif
#endif

#ifdef _DEVICE_RESOLUTION_AWARE
#ifdef __cplusplus
    #include "DeviceResolutionAware.h"
#endif
#endif

#if _WIN32_WCE < 0x500 && ( defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP) )
	#pragma comment(lib, "ccrtrtti.lib")
	#ifdef _X86_	
		#if defined(_DEBUG)
			#pragma comment(lib, "libcmtx86d.lib")
		#else
			#pragma comment(lib, "libcmtx86.lib")
		#endif
	#endif
#endif

#include <altcecrt.h>

/* Restore original warnings level. */
#pragma warning(pop)

/* Keep warnings for deprecated functions but show only once for each source file. */
#pragma warning( once : 4996 )

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
