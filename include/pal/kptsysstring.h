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
 * @file    kptsysstring.h
 *
 * @brief   String object interface for system characters.
 *
 * @details 
 * 
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTSYSSTRING_H
#define H_KPTSYSSTRING_H

#include "kptlibsystem.h"
#include "kptapi.h"
#include "kptheap.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

DECLARE_KPTHANDLE(KPTSysStringT)

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringCreateEmpty(KPTSysStringT** aHandle,
                        KPTHeapT* aHeap);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringFromString(KPTSysStringT** aHandle,
                       KPTHeapT* aHeap,
                       const KPTSysCharT* aString);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringFromBlock(KPTSysStringT** aHandle, 
                      KPTHeapT* aHeap,
                      const KPTSysCharT* aString, 
                      size_t aStringLen);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringCopyCreate(KPTSysStringT** aHandle, 
                       KPTHeapT* aHeap, 
                       const KPTSysStringT* aString);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringDestroy(KPTSysStringT** aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringIsEmpty(const KPTSysStringT* aHandle,
                    KPTBoolT* aIsEmpty);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringGetLen(const KPTSysStringT* aHandle,
                   size_t* aStrLen);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringGetReservedLen(const KPTSysStringT* aHandle,
                           size_t* aResLen);

KPT_LIB_SYSTEM
const KPTSysCharT*
KPT_CALL
KPTSysStringGetText(const KPTSysStringT* aHandle);

KPT_LIB_SYSTEM
const KPTSysCharT
KPT_CALL
KPTSysStringGetChar(const KPTSysStringT* aHandle, 
                    size_t aCharPos);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringClear(KPTSysStringT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringAppendChar(KPTSysStringT* aHandle,
                       KPTSysCharT aCharacter);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringAppendString(KPTSysStringT* aHandle,
                         const KPTSysCharT* aString);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringSetUpper(KPTSysStringT* aHandle, 
                     const KPTSysCharT* aString);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringSetBlockUpper(KPTSysStringT* aHandle,
                          const KPTSysCharT* aString,
                          size_t aStrLen);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringSetLower(KPTSysStringT* aHandle, 
                     const KPTSysCharT* aString);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringSetBlockLower(KPTSysStringT* aHandle, 
                          const KPTSysCharT* aString,
                          size_t aStrLen);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringInsertChar(KPTSysStringT* aHandle,
                       KPTSysCharT aCharacter,
                       size_t aInsertPos);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringInsertString(KPTSysStringT* aHandle, 
                         const KPTSysCharT* aString,
                         size_t aInsertPos);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringReplaceChar(KPTSysStringT* aHandle,
                        KPTSysCharT aCharacter,
                        size_t aInsertPos);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringReplaceString(KPTSysStringT* aHandle,
                          const KPTSysCharT* aString,
                          size_t aInsertPos);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringResize(KPTSysStringT* aHandle,
                   size_t aNewSize);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringTruncate(KPTSysStringT* aHandle,
                     size_t aNewLen);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringRemoveChar(KPTSysStringT* aHandle,
                       size_t aCharPos);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringRemoveString(KPTSysStringT* aHandle,
                         size_t aCharPos,
                         size_t aStrLen);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringTrimRight(KPTSysStringT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringTrimLeft(KPTSysStringT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringTrimAll(KPTSysStringT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringCmp(const KPTSysStringT* aHandle,
                const KPTSysStringT* aString,
                int* aResult);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringNCmp(const KPTSysStringT* aHandle,
                 const KPTSysStringT* aString,
                 size_t aNumChar,
                 int* aResult);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringICmp(const KPTSysStringT* aHandle,
                 const KPTSysStringT* aString,
                 int* aResult);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringNICmp(const KPTSysStringT* aHandle,
                  const KPTSysStringT* aString,
                  size_t aNumChar,
                  int* aResult);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringChr(const KPTSysStringT* aHandle,
                KPTSysCharT aChar,
                int aOffset,
                KPTSysCharT** aResultStr);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringRChr(const KPTSysStringT* aHandle,
                 KPTSysCharT aChar,
                 int aOffset,
                 KPTSysCharT** aResultStr);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringStr(const KPTSysStringT* aHandle,
                const KPTSysCharT* aString,
                int aOffset,
                KPTSysCharT** aResultStr);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringFindReplace(KPTSysStringT* aHandle,
                        const KPTSysCharT* aOldStr,
                        const KPTSysCharT* aNewStr);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringToUpper(KPTSysStringT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTSysStringToLower(KPTSysStringT* aHandle);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALLV
KPTSysStringFormat(KPTSysStringT* aHandle,
                   size_t aOutBuffer,
                   const KPTSysCharT* aFormatString,
                   ...);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* H_KPTSYSSTRING_H */
