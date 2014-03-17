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
 * @brief   Portable format specifiers (Android)
 *
 * @details This file contains portable defines that can be used with 
 * printf style format strings. It includes a subset of the C99 inttypes.h 
 * standard defines.
 * There shall be a format for each type in kptint.h.
 * There shall also be formats for strings.
 *
 *****************************************************************************/

#ifndef H_KPTFMTSPEC_H
#define H_KPTFMTSPEC_H

/* Define H_INTTYPES_H if the platform has stdint.h support */
#ifndef _INTTYPES_H_

/* 8-bit signed decimal */ 
#define PRId8       "d"
#define PRIi8       "i"
#define PRIdLEAST8  "d"
#define PRIiLEAST8  "i"
#define PRIdFAST8   "d"
#define PRIiFAST8   "i"

/* 16-bit signed decimal */ 
#define PRId16       "d"
#define PRIi16       "i"
#define PRIdLEAST16  "d"
#define PRIiLEAST16  "i"
#define PRIdFAST16   "d"
#define PRIiFAST16   "i"

/* 32-bit signed decimal */ 
#define PRId32       "d"
#define PRIi32       "i"
#define PRIdLEAST32  "d"
#define PRIiLEAST32  "i"
#define PRIdFAST32   "d"
#define PRIiFAST32   "i"

/* 64-bit signed decimal */ 
#define PRId64       "lld"
#define PRIi64       "lli"
#define PRIdLEAST64  "lld"
#define PRIiLEAST64  "lli"
#define PRIdFAST64   "lld"
#define PRIiFAST64   "lli"

/* Max int signed decimal */ 
#define PRIdMAX      "lld"
#define PRIiMAX      "lli"

/* Pointer signed decimal */ 
#define PRIdPTR      "ld"
#define PRIiPTR      "li"

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
#define PRIo16       "o"
#define PRIu16       "u"
#define PRIx16       "x"
#define PRIX16       "X"
#define PRIoLEAST16  "o"
#define PRIuLEAST16  "u"
#define PRIxLEAST16  "x"
#define PRIXLEAST16  "X"
#define PRIoFAST16   "o"
#define PRIuFAST16   "u"
#define PRIxFAST16   "x"
#define PRIXFAST16   "X"

/* 32-bit unsigned */ 
#define PRIo32       "o"
#define PRIu32       "u"
#define PRIx32       "x"
#define PRIX32       "X"
#define PRIoLEAST32  "o"
#define PRIuLEAST32  "u"
#define PRIxLEAST32  "x"
#define PRIXLEAST32  "X"
#define PRIoFAST32   "o"
#define PRIuFAST32   "u"
#define PRIxFAST32   "x"
#define PRIXFAST32   "X"

/* 64-bit unsigned */ 
#define PRIo64       "llo"
#define PRIu64       "llu"
#define PRIx64       "llx"
#define PRIX64       "llX"
#define PRIoLEAST64  "llo"
#define PRIuLEAST64  "llu"
#define PRIxLEAST64  "llx"
#define PRIXLEAST64  "llX"
#define PRIoFAST64   "llo"
#define PRIuFAST64   "llu"
#define PRIxFAST64   "llx"
#define PRIXFAST64   "llX"

/* Max int unsigned */ 
#define PRIoMAX      "llo"
#define PRIuMAX      "llu"
#define PRIxMAX      "llx"
#define PRIXMAX      "llX"

/* Pointer unsigned */ 
#define PRIoPTR      "lo"
#define PRIuPTR      "lu"
#define PRIxPTR      "lx"
#define PRIXPTR      "lX"

#endif /* #ifndef H_INTTYPES_H */

/* size_t */
#define PRIoSIZE     "zo"
#define PRIuSIZE     "zu"
#define PRIxSIZE     "zx"
#define PRIXSIZE     "zX"

/** Portable format specifier for char* strings */
#define PRIs         "hs"
#define PRIsn        "hs"

/** Portable format specifier for wchar_t* strings */
#define PRIls        "ls"
#define PRIsw        "ls"

/** Portable format specifier for end-of-line */
#define PRIeol       "\n\0"

#if KPT_TSYSCHAR_ISWIDE

	/** Portable format specifier for KPTSysCharT* strings */
	#define PRIsys    "ls"

#else

	/** Portable format specifier for KPTSysCharT* strings */
	#define PRIsys    "hs"

#endif

#endif /* #ifndef H_KPTFMTSPEC_H */
