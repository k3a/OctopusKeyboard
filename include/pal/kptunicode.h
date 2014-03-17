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
 * @file    kptunicode.h
 *
 * @brief   KPT Unicode UTF-16 defined API that allows us to perform the expected 
 * string manipulation routines on NULL terminated 16bit character strings.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTUNICODE_H
#define H_KPTUNICODE_H

#include "kptlibunicode.h"
#include "kptapi.h"
#include "kptheap.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Number of data bytes required to identify a utf8 character */
#define KPT_UTF8_MAX_BYTES 4

/* Converting a character from one encoding to another may generate an
   increase in number of datums - this will be big enough
*/
#define KPT_UTF_CONVERT_OUT_SIZE 5

/* maximum size to which an unicode character can expand */
#define KPTUC_MAX_CASE_CONVERSION_CHAR_BUFFER_SIZE 2

enum KPTUnicodeLangInUseT
{
	eKPTLangDefault = 1,
    eKPTLangTukishAndAzeri = 2,
	eKPTLangGreek =3,
    eKPTLangLithuanian = 4
};
typedef enum KPTUnicodeLangInUseT KPTUnicodeLangInUseT;

KPT_LIB_UNICODE
KPTBoolT
KPT_CALL
KPTUnicodeIsAlpha(KPTUniCharT aChar);

KPT_LIB_UNICODE
KPTBoolT
KPT_CALL
KPTUnicodeIsAlphaNum(KPTUniCharT aChar);

KPT_LIB_UNICODE
KPTBoolT
KPT_CALL
KPTUnicodeIsDigit(KPTUniCharT aChar);

KPT_LIB_UNICODE
KPTBoolT
KPT_CALL
KPTUnicodeIsPunct(KPTUniCharT aChar);

KPT_LIB_UNICODE
KPTBoolT
KPT_CALL
KPTUnicodeIsSpace(KPTUniCharT aChar);

KPT_LIB_UNICODE
KPTBoolT
KPT_CALL
KPTUnicodeIsSymbol(KPTUniCharT aChar);

KPT_LIB_UNICODE
KPTBoolT
KPT_CALL
KPTUnicodeIsNewLine(KPTUniCharT aChar);

KPT_LIB_UNICODE
KPTBoolT
KPT_CALL
KPTUnicodeIsControl(KPTUniCharT aChar);

KPT_LIB_UNICODE
KPTBoolT
KPT_CALL
KPTUnicodeIsUpper(KPTUniCharT aChar);

KPT_LIB_UNICODE
KPTBoolT
KPT_CALL
KPTUnicodeIsLower(KPTUniCharT aChar);

KPT_LIB_UNICODE
KPTBoolT
KPT_CALL
KPTUnicodeIsTitle(KPTUniCharT aChar);

KPT_LIB_UNICODE
uint32_t
KPT_CALL
KPTUnicodeGetCharCategory(KPTUniCharT aChar);

KPT_LIB_UNICODE
KPTResultT
KPT_CALL
KPTUnicodeGetStrLen(const KPTUniCharT* aString, 
                    size_t* aLength);

KPT_LIB_UNICODE
KPTResultT
KPT_CALL
KPTUnicodeGetStrLenAndUpperLen(const KPTUniCharT* aString, 
                               size_t* aStrLength, 
                               size_t* aUpperLength, 
                               KPTUnicodeLangInUseT aLanguageInUse);

KPT_LIB_UNICODE
KPTResultT
KPT_CALL
KPTUnicodeGetUpperLen(const KPTUniCharT* aString, 
                      size_t* aUpperLength, 
                      KPTUnicodeLangInUseT aLanguageInUse);


KPT_LIB_UNICODE
KPTResultT
KPT_CALL
KPTUnicodeGetLowerLen(const KPTUniCharT* aString, 
                      size_t* aLowerLength, 
                      KPTUnicodeLangInUseT aLanguageInUse);

KPT_LIB_UNICODE
KPTResultT 
KPT_CALL
KPTUnicodeCharToUpper(const KPTUniCharT aInputChar,
                      KPTUniCharT* aOutput, 
                      size_t* aNumCharsInOutput,
                      KPTUnicodeLangInUseT aLanguageInUse);

KPT_LIB_UNICODE
KPTUniCharT 
KPT_CALL
KPTUnicodeCharToLower(const KPTUniCharT aInputChar,
                      KPTUnicodeLangInUseT aLanguageInUse);

KPT_LIB_UNICODE
KPTResultT
KPT_CALL
KPTUnicodeCharToTitle(const KPTUniCharT aInputChar,
                      KPTUniCharT *aOutput, 
                      size_t* aNumCharsInOutput,
                      KPTUnicodeLangInUseT aLanguageInUse);

KPT_LIB_UNICODE
KPTResultT
KPT_CALL
KPTUnicodeStrToUpper(const KPTUniCharT* aInputString, 
                     KPTUniCharT** aOutputString,
                     KPTHeapT* aKptHeap,
                     KPTUnicodeLangInUseT aLanguageInUse);

KPT_LIB_UNICODE
KPTResultT
KPT_CALL
KPTUnicodeStrToUpperBuffer(const KPTUniCharT* aInputString,
                           size_t aCharsToConvert,
                           KPTUniCharT* aOutputBuffer,
                           size_t aOutputBufferSize,
                           KPTUnicodeLangInUseT aLanguageInUse);

KPT_LIB_UNICODE
KPTResultT
KPT_CALL
KPTUnicodeStrToLower(const KPTUniCharT* aInputString, 
                     KPTUniCharT** aOutputString,
                     KPTHeapT* aKptHeap,
                     KPTUnicodeLangInUseT aLanguageInUse);

KPT_LIB_UNICODE
KPTResultT
KPT_CALL
KPTUnicodeStrToLowerBuffer(const KPTUniCharT* aInputString,
                           size_t aCharsToConvert,
                           KPTUniCharT* aOutputBuffer,
                           size_t aOutputBufferSize,
                           KPTUnicodeLangInUseT aLanguageInUse);


KPT_LIB_UNICODE
KPTResultT
KPT_CALL
KPTUnicodeStrICmp(const KPTUniCharT* aString1, 
                  const KPTUniCharT* aString2,
                  KPTUnicodeLangInUseT aLanguageInUse, 
                  int* aCompResult);

KPT_LIB_UNICODE
KPTResultT
KPT_CALL
KPTUnicodeStrCmp(const KPTUniCharT* aString1, 
                 const KPTUniCharT* aString2, 
                 int* aCompResult);

KPT_LIB_UNICODE
KPTResultT
KPT_CALL
KPTUnicodeStrNICmp(const KPTUniCharT* aString1, 
                   const KPTUniCharT* aString2,
                   size_t aNumCharsToCompare,
                   KPTUnicodeLangInUseT aLanguageInUse, 
                   int* aCompResult);

KPT_LIB_UNICODE
KPTResultT
KPT_CALL
KPTUnicodeStrNCmp(const KPTUniCharT* aString1, 
                  const KPTUniCharT* aString2, 
                  size_t aNumCharsToCompare,
                  int* aCompResult);

KPT_LIB_UNICODE
KPTUniCharT
KPT_CALL
KPTUnicodeGetMirrorChar(KPTUniCharT aChar);



KPT_LIB_UNICODE
KPTResultT 
KPT_CALL
KPTUnicodeConvertUTF8toUTF16(const KPTUtf8CharT** aSourceStart, 
                             const KPTUtf8CharT* aSourceEnd, 
                             KPTUtf16CharT** aDestStart, 
                             KPTUtf16CharT* aDestEnd, 
                             KPTBoolT aStrict);

KPT_LIB_UNICODE
KPTResultT 
KPT_CALL
KPTUnicodeConvertUTF16toUTF8(const KPTUtf16CharT** aSourceStart, 
                             const KPTUtf16CharT* aSourceEnd,
                             KPTUtf8CharT** aDestStart, 
                             KPTUtf8CharT* aDestEnd, 
                             KPTBoolT aStrict);

KPT_LIB_UNICODE
KPTResultT 
KPT_CALL
KPTUnicodeConvertUTF8toUTF32(const KPTUtf8CharT** aSourceStart, 
                             const KPTUtf8CharT* aSourceEnd, 
                             KPTUtf32CharT** aTargetStart, 
                             KPTUtf32CharT* aTargetEnd, 
                             KPTBoolT aStrict);

KPT_LIB_UNICODE
KPTResultT 
KPT_CALL
KPTUnicodeConvertUTF32toUTF8(const KPTUtf32CharT** aSourceStart, 
                             const KPTUtf32CharT* aSourceEnd, 
                             KPTUtf8CharT** aTargetStart, 
                             KPTUtf8CharT* aTargetEnd, 
                             KPTBoolT aStrict);

KPT_LIB_UNICODE		
KPTResultT 
KPT_CALL
KPTUnicodeConvertUTF16toUTF32(const KPTUtf16CharT** aSourceStart, 
                              const KPTUtf16CharT* aSourceEnd, 
                              KPTUtf32CharT** aTargetStart, 
                              KPTUtf32CharT* aTargetEnd, 
                              KPTBoolT aStrict);

KPT_LIB_UNICODE
KPTResultT 
KPT_CALL
KPTUnicodeConvertUTF32toUTF16(const KPTUtf32CharT** aSourceStart, 
                              const KPTUtf32CharT* aSourceEnd, 
                              KPTUtf16CharT** aTargetStart, 
                              KPTUtf16CharT* aTargetEnd, 
                              KPTBoolT aStrict);


KPT_LIB_UNICODE
KPTBoolT 
KPT_CALL
KPTUnicodeIsLegalUTF8(const KPTUtf8CharT* aSource, 
                      size_t aLength);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTUNICODE_H */
