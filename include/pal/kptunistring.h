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
 * @file    kptunistring.h
 *
 * @brief   String object interface for unicode charaters.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTUNISTRING_H
#define H_KPTUNISTRING_H

#include "kptlibsystem.h"
#include "kptapi.h"
#include "kptheap.h"
#include "kptunicode.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

DECLARE_KPTHANDLE(KPTUniStringT)

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringCreateEmpty(KPTUniStringT** aHandle,
                        KPTHeapT* aHeap);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringFromString(KPTUniStringT** aHandle,
                       KPTHeapT* aHeap,
                       const KPTUniCharT* aString);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringFromBlock(KPTUniStringT** aHandle,
                      KPTHeapT* aHeap,
                      const KPTUniCharT* aString,
                      size_t aStringLen);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringCopyCreate(KPTUniStringT** aHandle,
                       KPTHeapT* aHeap,
                       const KPTUniStringT* aString);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringDestroy(KPTUniStringT** aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringIsEmpty(const KPTUniStringT* aHandle,
                    KPTBoolT* aIsEmpty);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringGetLen(const KPTUniStringT* aHandle,
                   size_t* aStrLen);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringGetReservedLen(const KPTUniStringT* aHandle,
                           size_t* aResLen);

KPT_LIB_SYSTEM
const KPTUniCharT*
KPT_CALL
KPTUniStringGetText(const KPTUniStringT* aHandle);

KPT_LIB_SYSTEM
const KPTUniCharT
KPT_CALL
KPTUniStringGetChar(const KPTUniStringT* aHandle,
                    size_t aCharPos);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringClear(KPTUniStringT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringAppendChar(KPTUniStringT* aHandle,
                       KPTUniCharT aCharacter);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringAppendString(KPTUniStringT* aHandle,
                         const KPTUniCharT* aString);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringSetUpper(KPTUniStringT* aHandle,
                     const KPTUniCharT* aString,
                     KPTUnicodeLangInUseT aLangInUse);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringSetBlockUpper(KPTUniStringT* aHandle,
                          const KPTUniCharT* aString,
                          size_t aStrLen,
                          KPTUnicodeLangInUseT aLangInUse);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringSetLower(KPTUniStringT* aHandle,
                     const KPTUniCharT* aString,
                     KPTUnicodeLangInUseT aLangInUse);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringSetBlockLower(KPTUniStringT* aHandle,
                          const KPTUniCharT* aString,
                          size_t aStrLen,
                          KPTUnicodeLangInUseT aLangInUse);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringInsertChar(KPTUniStringT* aHandle,
                       KPTUniCharT aCharacter,
                       size_t aInsertPos);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringInsertString(KPTUniStringT* aHandle,
                         const KPTUniCharT* aString,
                         size_t aInsertPos);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringReplaceChar(KPTUniStringT* aHandle,
                        KPTUniCharT aCharacter,
                        size_t aInsertPos);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringReplaceString(KPTUniStringT* aHandle,
                          const KPTUniCharT* aString,
                          size_t aInsertPos);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringResize(KPTUniStringT* aHandle,
                   size_t aNewSize);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringTruncate(KPTUniStringT* aHandle,
                     size_t aNewLen);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringRemoveChar(KPTUniStringT* aHandle,
                       size_t aCharPos);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringRemoveString(KPTUniStringT* aHandle,
                         size_t aCharPos,
                         size_t aStrLen);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringTrimRight(KPTUniStringT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringTrimLeft(KPTUniStringT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringTrimAll(KPTUniStringT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringCmp(const KPTUniStringT* aHandle,
                const KPTUniStringT* aString,
                int* aResult);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringNCmp(const KPTUniStringT* aHandle,
                 const KPTUniStringT* aString,
                 size_t aNumChar,
                 int* aResult);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringICmp(const KPTUniStringT* aHandle,
                 const KPTUniStringT* aString,
                 KPTUnicodeLangInUseT aLangInUse,
                 int* aResult);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringNICmp(const KPTUniStringT* aHandle,
                  const KPTUniStringT* aString,
                  size_t aNumChar,
                  KPTUnicodeLangInUseT aLangInUse,
                  int* aResult);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringChr(const KPTUniStringT* aHandle,
                KPTUniCharT aChar,
                int aOffset,
                KPTUniCharT** aResultStr);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringRChr(const KPTUniStringT* aHandle,
                 KPTUniCharT aChar,
                 int aOffset,
                 KPTUniCharT** aResultStr);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringStr(const KPTUniStringT* aHandle,
                const KPTUniCharT* aString,
                int aOffset,
                KPTUniCharT** aResultStr);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringFindReplace(KPTUniStringT* aHandle,
                        const KPTUniCharT* aOldStr,
                        const KPTUniCharT* aNewStr);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringToUpper(KPTUniStringT* aHandle,
                    KPTUnicodeLangInUseT aLangInUse);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTUniStringToLower(KPTUniStringT* aHandle,
                    KPTUnicodeLangInUseT aLangInUse);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* H_KPTUNISTRING_H */
