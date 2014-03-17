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
 * @file    kptfmtspec.h
 *
 * @brief   Portable format specifiers (Windows)
 *
 * @details This file contains portable defines that can be used with 
 * printf style format strings. It includes a subset of the C99 inttypes.h 
 * standard defines.
 * There shall be a format for each type in kptint.h.
 * There shall also be formats for strings.
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTFMTSPEC_H
#define H_KPTFMTSPEC_H

/* Define H_INTTYPES_H if the platform has stdint.h support */
#ifndef H_INTTYPES_H

/* 8-bit signed decimal */ 
#define PRId8       "d"
#define PRIi8       "i"
#define PRIdLEAST8  "d"
#define PRIiLEAST8  "i"
#define PRIdFAST8   "d"
#define PRIiFAST8   "i"

/* 16-bit signed decimal */ 
#define PRId16       "hd"
#define PRIi16       "hi"
#define PRIdLEAST16  "hd"
#define PRIiLEAST16  "hi"
#define PRIdFAST16   "hd"
#define PRIiFAST16   "hi"

/* 32-bit signed decimal */ 
#define PRId32       "I32d"
#define PRIi32       "I32i"
#define PRIdLEAST32  "I32d"
#define PRIiLEAST32  "I32i"
#define PRIdFAST32   "I32d"
#define PRIiFAST32   "I32i"

/* 64-bit signed decimal */ 
#define PRId64       "I64d"
#define PRIi64       "I64i"
#define PRIdLEAST64  "I64d"
#define PRIiLEAST64  "I64i"
#define PRIdFAST64   "I64d"
#define PRIiFAST64   "I64i"

/* Max int signed decimal */ 
#define PRIdMAX      "I64d"
#define PRIiMAX      "I64i"

/* Pointer signed decimal */ 
#define PRIdPTR      "Id"
#define PRIiPTR      "Ii"

/* 8-bit unsigned */ 
#define PRIo8        "o"
#define PRIu8        "u"
#define PRIx8        "x"
#define PRIX8        "X"
#define PRIoLEAST8   "o"
#define PRIuLEAST8   "u"
#define PRIxLEAST8   "x"
#define PRIXLEAST8   "X"
#define PRIoFAST8    "o"
#define PRIuFAST8    "u"
#define PRIxFAST8    "x"
#define PRIXFAST8    "X"

/* 16-bit unsigned */ 
#define PRIo16       "ho"
#define PRIu16       "hu"
#define PRIx16       "hx"
#define PRIX16       "hX"
#define PRIoLEAST16  "ho"
#define PRIuLEAST16  "hu"
#define PRIxLEAST16  "hx"
#define PRIXLEAST16  "hX"
#define PRIoFAST16   "ho"
#define PRIuFAST16   "hu"
#define PRIxFAST16   "hx"
#define PRIXFAST16   "hX"

/* 32-bit unsigned */ 
#define PRIo32       "I32o"
#define PRIu32       "I32u"
#define PRIx32       "I32x"
#define PRIX32       "I32X"
#define PRIoLEAST32  "I32o"
#define PRIuLEAST32  "I32u"
#define PRIxLEAST32  "I32x"
#define PRIXLEAST32  "I32X"
#define PRIoFAST32   "I32o"
#define PRIuFAST32   "I32u"
#define PRIxFAST32   "I32x"
#define PRIXFAST32   "I32X"

/* 64-bit unsigned */ 
#define PRIo64       "I64o"
#define PRIu64       "I64u"
#define PRIx64       "I64x"
#define PRIX64       "I64X"
#define PRIoLEAST64  "I64o"
#define PRIuLEAST64  "I64u"
#define PRIxLEAST64  "I64x"
#define PRIXLEAST64  "I64X"
#define PRIoFAST64   "I64o"
#define PRIuFAST64   "I64u"
#define PRIxFAST64   "I64x"
#define PRIXFAST64   "I64X"

/* Max int unsigned */ 
#define PRIoMAX      "I64o"
#define PRIuMAX      "I64u"
#define PRIxMAX      "I64x"
#define PRIXMAX      "I64X"

#ifdef _WIN64 
	/* Pointer unsigned */ 
	#define PRIoPTR      PRIo64
	#define PRIuPTR      PRIu64
	#define PRIxPTR      PRIx64
	#define PRIXPTR      PRIX64

#else
	/* Pointer unsigned */ 
	#define PRIoPTR      PRIo32
	#define PRIuPTR      PRIu32
	#define PRIxPTR      PRIx32
	#define PRIXPTR      PRIX32
#endif

#endif /* #ifndef H_INTTYPES_H */

#ifdef _WIN64 
	/* size_t */
	#define PRIoSIZE     PRIo64
	#define PRIuSIZE     PRIu64
	#define PRIxSIZE     PRIx64
	#define PRIXSIZE     PRIX64
#else
	/* size_t */
	#define PRIoSIZE     PRIo32
	#define PRIuSIZE     PRIu32
	#define PRIxSIZE     PRIx32
	#define PRIXSIZE     PRIX32
#endif

/** Portable format specifier for char* strings */
#define PRIs         "hs"
#define PRIsn        "hs"

/** Portable format specifier for wchar_t* strings */
#define PRIls        "ls"
#define PRIsw        "ls"

/** Portable format specifier for end-of-line */
#define PRIeol       "\n"

#if KPT_TSYSCHAR_ISWIDE

	/** Portable format specifier for KPTSysCharT* strings */
	#define PRIsys    "ls"

#else

	/** Portable format specifier for KPTSysCharT* strings */
	#define PRIsys    "hs"

#endif

#endif /* #ifndef H_KPTFMTSPEC_H */
