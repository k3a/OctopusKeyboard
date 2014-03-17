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
 * @file    kptstrings.h
 *
 * @brief   Safer string routines.
 *
 * @details
 * 
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTSTRINGS_H
#define H_KPTSTRINGS_H

#include "kptlibsystem.h"
#include "kptapi.h"
#include "kptunicode.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus*/


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrLenU(const KPTUniCharT* aString,
           size_t* aLength);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrLenS(const KPTSysCharT* aString,
           size_t* aLength);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrUpperLenU(const KPTUniCharT* aString,
                KPTUnicodeLangInUseT aLangInUse,
                size_t* aLength);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrLowerLenU(const KPTUniCharT* aString,
                KPTUnicodeLangInUseT aLangInUse,
                size_t* aLength);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrCpyU(KPTUniCharT* aDestStr,
           size_t aDestSize,
           const KPTUniCharT* aSourceStr);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrCpyS(KPTSysCharT* aDestStr,
           size_t aDestSize,
           const KPTSysCharT* aSourceStr);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrNCpyU(KPTUniCharT* aDestStr,
            size_t aDestSize,
            const KPTUniCharT* aSourceStr,
            size_t aNum);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrNCpyS(KPTSysCharT* aDestStr,
            size_t aDestSize,
            const KPTSysCharT* aSourceStr,
            size_t aNum);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrAppendU(KPTUniCharT* aDestStr,
              size_t aDestSize,
              const KPTUniCharT* aSourceStr);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrAppendS(KPTSysCharT* aDestStr,
              size_t aDestSize,
              const KPTSysCharT* aSourceStr);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrCmpU(const KPTUniCharT* aString1,
           const KPTUniCharT* aString2,
           int* aResult);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrCmpS(const KPTSysCharT* aString1,
           const KPTSysCharT* aString2,
           int* aResult);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrICmpU(const KPTUniCharT* aString1,
            const KPTUniCharT* aString2,
            KPTUnicodeLangInUseT aLangInUse,
            int* aResult);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrICmpS(const KPTSysCharT* aString1,
            const KPTSysCharT* aString2,
            int* aResult);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrNCmpU(const KPTUniCharT* aString1,
            const KPTUniCharT* aString2,
            size_t aNum,
            int* aResult);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrNCmpS(const KPTSysCharT* aString1,
            const KPTSysCharT* aString2,
            size_t aNum,
            int* aResult);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrNICmpU(const KPTUniCharT* aString1,
             const KPTUniCharT* aString2,
             size_t aNum,
             KPTUnicodeLangInUseT aLangInUse,
             int* aResult);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrNICmpS(const KPTSysCharT* aString1,
             const KPTSysCharT* aString2,
             size_t aNum,
             int* aResult);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrStartsWithU(const KPTUniCharT* aString,
                  const KPTUniCharT* aStrPrefix,
                  KPTBoolT* aStarts);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrStartsWithS(const KPTSysCharT* aString,
                  const KPTSysCharT* aStrPrefix,
                  KPTBoolT* aStarts);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrIStartsWithU(const KPTUniCharT* aString,
                   const KPTUniCharT* aStrPrefix,
                   KPTUnicodeLangInUseT aLangInUse,
                   KPTBoolT* aStarts);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrIStartsWithS(const KPTSysCharT* aString,
                   const KPTSysCharT* aStrPrefix,
                   KPTBoolT* aStarts);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrEndsWithU(const KPTUniCharT* aString,
                const KPTUniCharT* aStrPostfix,
                KPTBoolT* aEnds);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrEndsWithS(const KPTSysCharT* aString,
                const KPTSysCharT* aStrPostfix,
                KPTBoolT* aEnds);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrIEndsWithU(const KPTUniCharT* aString,
                 const KPTUniCharT* aStrPostfix,
                 KPTUnicodeLangInUseT aLangInUse,
                 KPTBoolT* aEnds);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrIEndsWithS(const KPTSysCharT* aString,
                 const KPTSysCharT* aStrPostfix,
                 KPTBoolT* aEnds);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrToUpperU(KPTUniCharT* aDestStr,
               size_t aDestSize,
               const KPTUniCharT* aSourceStr,
               KPTUnicodeLangInUseT aLangInUse);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrToUpperS(KPTSysCharT* aDestStr,
               size_t aDestSize,
               const KPTSysCharT* aSourceStr);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrToLowerU(KPTUniCharT* aDestStr,
               size_t aDestSize,
               const KPTUniCharT* aSourceStr,
               KPTUnicodeLangInUseT aLangInUse);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrToLowerS(KPTSysCharT* aDestStr,
               size_t aDestSize,
               const KPTSysCharT* aSourceStr);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrIsUpperU(const KPTUniCharT* aString,
               KPTBoolT* aIsUpper);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrIsUpperS(const KPTSysCharT* aString,
               KPTBoolT* aIsUpper);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrIsLowerU(const KPTUniCharT* aString,
               KPTBoolT* aIsLower);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrIsLowerS(const KPTSysCharT* aString,
               KPTBoolT* aIsLower);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrChrU(const KPTUniCharT* aString,
           KPTUniCharT aChar,
           int aOffset,
           KPTUniCharT** aResult);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrChrS(const KPTSysCharT* aString,
           KPTSysCharT aChar,
           int aOffset,
           KPTSysCharT** aResult);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrIChrU(const KPTUniCharT* aString,
            KPTUniCharT aChar,
            int aOffset,
            KPTUnicodeLangInUseT aLangInUse,
            KPTUniCharT** aResult);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrIChrS(const KPTSysCharT* aString,
            KPTSysCharT aChar,
            int aOffset,
            KPTSysCharT** aResult);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrRChrU(const KPTUniCharT* aString,
            KPTUniCharT aChar,
            int aOffset,
            KPTUniCharT** aResult);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrRChrS(const KPTSysCharT* aString,
            KPTSysCharT aChar,
            int aOffset,
            KPTSysCharT** aResult);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrIRChrU(const KPTUniCharT* aString,
             KPTUniCharT aChar,
             int aOffset,
             KPTUnicodeLangInUseT aLangInUse,
             KPTUniCharT** aResult);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrIRChrS(const KPTSysCharT* aString,
             KPTSysCharT aChar,
             int aOffset,
             KPTSysCharT** aResult);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrStrU(const KPTUniCharT* aString,
           const KPTUniCharT* aSubString,
           int aOffset,
           KPTUniCharT** aResult);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrStrS(const KPTSysCharT* aString,
           const KPTSysCharT* aSubString,
           int aOffset,
           KPTSysCharT** aResult);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrIStrU(const KPTUniCharT* aString,
            const KPTUniCharT* aSubString,
            int aOffset,
            KPTUnicodeLangInUseT aLangInUse,
            KPTUniCharT** aResult);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrIStrS(const KPTSysCharT* aString,
            const KPTSysCharT* aSubString,
            int aOffset,
            KPTSysCharT** aResult);


KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrToInt32S(const KPTSysCharT* aString,
               int32_t* aValue,
               int aBase);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrToUint32S(const KPTSysCharT* aString,
                uint32_t* aValue,
                int aBase);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrToInt32U(const KPTUniCharT* aString,
               int32_t* aValue,
               int aBase);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTStrToUint32U(const KPTUniCharT* aString,
                uint32_t* aValue,
                int aBase);
#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* #ifndef H_KPTSTRINGS_H*/
