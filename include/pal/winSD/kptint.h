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
 * @file    kptint.h
 *
 * @brief   subset of stdint.h implementation.
 *
 * @details 
 *  
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTINT_H
#define H_KPTINT_H

/* Define H_STDINT_H if the platform has stdint.h support */
#ifndef H_STDINT_H

/* Exact-width integer types */
typedef signed char         int8_t;     /**< 8-bit signed integer */
typedef signed short int    int16_t;    /**< 16-bit signed integer */ 
typedef signed long int     int32_t;    /**< 32-bit signed integer */
typedef signed long long    int64_t;    /**< 64-bit signed integer */

typedef unsigned char       uint8_t;    /**< 8-bit unsigned integer */
typedef unsigned short int  uint16_t;   /**< 16-bit unsigned integer */
typedef unsigned long int   uint32_t;   /**< 32-bit unsigned integer */
typedef unsigned long long  uint64_t;   /**< 64-bit unsigned integer */

/* Fastest-width integer types */
typedef int8_t              int_fast8_t;   /**< fastest signed integer for 8-bits */
typedef int16_t             int_fast16_t;  /**< fastest signed integer for 16-bits */
typedef int32_t             int_fast32_t;  /**< fastest signed integer for 32-bits */
typedef int64_t             int_fast64_t;  /**< fastest signed integer for 64-bits */

typedef uint8_t             uint_fast8_t;   /**< fastest unsigned integer for 8-bits */
typedef uint16_t            uint_fast16_t;  /**< fastest unsigned integer for 16-bits */
typedef uint32_t            uint_fast32_t;  /**< fastest unsigned integer for 32-bits */
typedef uint64_t            uint_fast64_t;  /**< fastest unsigned integer for 64-bits */

/* Greatest-width integer types */
typedef int64_t             intmax_t;       /**< greatest signed integer type */
typedef uint64_t            uintmax_t;      /**< greatest unsigned integer type */


/* Constant declarations */
#ifndef INT8_C
#define INT8_C(c)   ((int8_t)c)
#endif

#ifndef INT16_C
#define INT16_C(c)   ((int16_t)c)
#endif

#ifndef INT32_C
#define INT32_C(c)   ((int32_t)c)
#endif

#ifndef INT64_C
#define INT64_C(c)   ((int64_t)c)
#endif

#ifndef UINT8_C
#define UINT8_C(c)   ((uint8_t)c##U)
#endif

#ifndef UINT16_C
#define UINT16_C(c)   ((int16_t)c##U)
#endif

#ifndef UINT32_C
#define UINT32_C(c)   ((int32_t)c##U)
#endif

#ifndef UINT64_C
#define UINT64_C(c)   ((int64_t)c##U)
#endif

#ifndef INTMAX_C
#define INTMAX_C(c)   ((intmax_t)c##U)
#endif

#ifndef UINTMAX_C
#define UINTMAX_C(c)   ((uintmax_t)c##U)
#endif


/* Limits of specified-width integer types */
#ifndef INT8_MIN
#define INT8_MIN 0x80
#endif

#ifndef INT8_MAX
#define INT8_MAX 0x7f
#endif

#ifndef INT16_MIN
#define INT16_MIN 0x8000
#endif

#ifndef INT16_MAX
#define INT16_MAX 0x7fff
#endif

#ifndef INT32_MIN
#define INT32_MIN 0x80000000L
#endif

#ifndef INT32_MAX
#define INT32_MAX 0x7fffffffL
#endif

#ifndef INT64_MIN
#define INT64_MIN 0x8000000000000000
#endif

#ifndef INT64_MAX
#define INT64_MAX 0x7fffffffffffffff
#endif

#ifndef UINT8_MAX
#define UINT8_MAX 0xff
#endif

#ifndef UINT16_MAX
#define UINT16_MAX 0xffff
#endif

#ifndef UINT32_MAX
#define UINT32_MAX 0xffffffff
#endif

#ifndef UINT64_MAX
#define UINT64_MAX 0xffffffffffffffff
#endif

/* Limits of fastest minimum-width integer types */
#ifndef INT_FAST8_MIN
#define INT_FAST8_MIN INT8_MIN
#endif

#ifndef INT_FAST8_MAX
#define INT_FAST8_MAX INT8_MAX
#endif

#ifndef INT_FAST16_MIN
#define INT_FAST16_MIN INT16_MIN
#endif

#ifndef INT_FAST16_MAX
#define INT_FAST16_MAX INT16_MAX
#endif

#ifndef INT_FAST32_MIN
#define INT_FAST32_MIN INT32_MIN
#endif

#ifndef INT_FAST32_MAX
#define INT_FAST32_MAX INT32_MAX
#endif

#ifndef INT_FAST64_MIN
#define INT_FAST64_MIN INT64_MIN
#endif

#ifndef INT_FAST64_MAX
#define INT_FAST64_MAX INT64_MAX
#endif

#ifndef UINT_FAST8_MAX
#define UINT_FAST8_MAX UINT8_MAX
#endif

#ifndef UINT_FAST16_MAX
#define UINT_FAST16_MAX UINT16_MAX
#endif

#ifndef UINT_FAST32_MAX
#define UINT_FAST32_MAX UINT32_MAX
#endif

#ifndef UINT_FAST64_MAX
#define UINT_FAST64_MAX UINT64_MAX
#endif

/* Limits of integer types capable of holding object pointers */
#ifndef INTPTR_MIN
#define INTPTR_MIN INT64_MIN
#endif

/* Limits of greatest-width integer types */
#ifndef INTMAX_MIN
#define INTMAX_MIN INT64_MIN
#endif

#ifndef INTMAX_MAX
#define INTMAX_MAX INT64_MAX
#endif

#ifndef UINTMAX_MAX
#define UINTMAX_MAX UINT64_MAX
#endif

#endif /* #ifndef H_STDINT_H */

/** File offset value */
#ifndef _OFF_T_DEFINED
	typedef long off_t;
#endif

#endif /* #ifndef H_KPTINT_H */
