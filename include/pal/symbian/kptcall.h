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
 * @file    kptcall.h
 *
 * @brief   Calling conventions in this KPT implementation.
 *
 * @details 
 *  
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTCALL_H
#define H_KPTCALL_H

#ifndef __stdcall
# ifdef __i386__
#  ifdef __GNUC__
#   define __stdcall __attribute__((__stdcall__))
#  endif
# else  /* __i386__ */
#  define __stdcall
# endif  /* __i386__ */
#endif /* __stdcall */


#ifndef __cdecl
# if defined(__i386__) && defined(__GNUC__)
#  define __cdecl __attribute__((__cdecl__))
# elif !defined(_MSC_VER)
#  define __cdecl
# endif
#endif /* __stdcall */

/** Calling convention for library functions */
#ifndef KPT_CALL
#define KPT_CALL __stdcall
#endif

/** Calling convention for variadic library functions */
#ifndef KPT_CALLV
#define KPT_CALLV __cdecl
#endif

/** Calling convention for callback functions */
#ifndef KPT_CALLB
#define KPT_CALLB __stdcall
#endif

/** Defines functions that perform no operation in a given configuration */
#ifndef KPT_NOP_FUNCTION
	#if _MSC_VER >= 1210
		#define KPT_NOP_FUNCTION __noop
	#else
		#define KPT_NOP_FUNCTION ((void)0)
	#endif
#endif

/** Operation that exists in debug mode only */
#ifdef NDEBUG
	#define KPT_DEBUG_ONLY(x)	KPT_NOP_FUNCTION
#else
	#define KPT_DEBUG_ONLY(x)	(x)
#endif

/** Perform \a action if \a condition is met. */
#define KPT_IFCONDITION(condition, action) ((condition)?action:0);

/** Reduces compiler warnings for parameters that are deliberately unused */
#ifdef _WIN32
#define KPT_UNREFERENCED_PARAMETER(p) (p)
#else
#define KPT_UNREFERENCED_PARAMETER(p)
#endif
/** Literal identifying a function. */
#ifndef KPTFUNCTION
	#define KPTFUNCTION __FUNCTION__
#endif

/** Location literal used in debugging functions. */
#ifdef KPTLOC_USE_FUNCTION
	#define KPTLOC KPTFUNCTION
#else
	#define KPTLOC __FILE__
#endif

/** Location integer used in debugging functions. */
#ifdef KPTLINE_USE_NONE
	#define KPTLINE 0
#else
	#define KPTLINE __LINE__
#endif

/** Inline support */
#ifndef KPTINLINE
	#define KPTINLINE __inline
#endif

/** forced inline support */
#ifndef KPTINLINE_FORCE
	#if (_MSC_VER >= 1200)
		#define KPTINLINE_FORCE __forceinline
	#else
		#define KPTINLINE_FORCE __inline
	#endif
#endif

/** Macro used to place a single statement scope around a compound macro.
	This hides the start of the familiar do{ }while(0) construct */
#define KPTMACRO_SCOPE_START do {

/** Macro used to place a single statement scope around a compound macro.
	This hides the end of the familiar do{ }while(0) construct */
#define KPTMACRO_SCOPE_END } while(0)

#endif /* #ifndef H_KPTCALL_H */
