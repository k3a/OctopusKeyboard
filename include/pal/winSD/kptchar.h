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
 * @file    kptchar.h
 *
 * @brief   Character types in the KPT system (Windows).
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTCHAR_H
#define H_KPTCHAR_H

typedef uint8_t KPTUtf8CharT;      /**< UTF8 character type */
typedef uint16_t KPTUtf16CharT;  /**< UTF16 character type */
typedef uint32_t KPTUtf32CharT; /**< UTF32 character type */

typedef wchar_t	KPTSysCharT;    /**< System character type */
typedef wchar_t	KPTUniCharT;    /**< Internal Unicode character type */

#define KPT_TCHAR_BIT CHAR_BIT   /**< Number of bits in char */
#define KPT_TWCHAR_BIT 16        /**< Number of bits in wchar_t */
#define KPT_TUNICHAR_BIT 16      /**< Number of bits in KPTUniCharT */
#define KPT_TSYSCHAR_BIT 16      /**< Number of bits in KPTSysCharT */
#define KPT_TSYSCHAR_ISWIDE 1    /**< The system character uses wide characters */
#define KPT_TSYSCHAR_ISNARROW 0  /**< The system character uses narrow characters */

/** A character or string literal (narrow) */
#define KPT_TN(s)        s

/** Encloses an argument with double quotes (narrow) */
#define KPT_TQUOTEN(s)   #s

/** Combines file and line location into a literal (narrow) */
#define KPT_TLOCAN(file, line) \
                         file "(" KPT_TQUOTEN(line) ")"

/** __FILE__ and __LINE__ combined into a literal (narrow) */
#define KPT_TLOCN        KPT_TLOCAN(__FILE__, __LINE__)


/** Helper macro to concatenate the wide literal marker */
#define KPT_TW_L(s)      L##s

/** A character or string literal (wide) */
#define KPT_TW(s)        KPT_TW_L(s)

/** Encloses an argument with double quotes (wide) */
#define KPT_TQUOTEW(s)   KPT_TW(#s)

/** Combines file and line location into a literal (wide) */
#define KPT_TLOCAW(file, line) \
                         KPT_TW(file) KPT_TW("(") KPT_TQUOTEW(line) KPT_TW(")")

/** __FILE__ and __LINE__ combined into a literal (wide) */
#define KPT_TLOCW        KPT_TLOCAW(__FILE__, __LINE__)



#if KPT_TSYSCHAR_ISWIDE

	/** A character or string literal (system) */
	#define KPT_TS           KPT_TW

	/** Encloses an argument with double quotes (system) */
	#define KPT_TQUOTES      KPT_TQUOTEW

	/** Combines file and line location into a literal (system) */
	#define KPT_TLOCAS       KPT_TLOCAW

	/** __FILE__ and __LINE__ combined into a literal (system) */
	#define KPT_TLOCS        KPT_TLOCW

#else /* #if NOT KPT_TSYSCHAR_WIDE */

	/** A character or string literal (system) */
	#define KPT_TS           KPT_TN

	/** Encloses an argument with double quotes (system) */
	#define KPT_TQUOTES      KPT_TQUOTEN

	/** Combines file and line location into a literal (system) */
	#define KPT_TLOCAS       KPT_TLOCAN

	/** __FILE__ and __LINE__ combined into a literal (system) */
	#define KPT_TLOCS        KPT_TLOCN

#endif /* #if NOT KPT_TSYSCHAR_WIDE */

/**
 * A 16-bit character or string literal.
 * Warning: It is not possible to define 16-bit string literals for every compiler.
 * The string version of the macro KPT_TU is not portable and cannot always be defined.
 */
#define KPT_TU           KPT_TW

#endif /* #ifndef H_KPTCHAR_H */
