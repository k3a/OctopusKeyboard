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
 * @file    kptunicodetable.h
 *
 * @brief   Unicode table interface.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTUNICODETABLE_IMP_H
#define H_KPTUNICODETABLE_IMP_H

#include "kptlibsystem.h"
#include "kptapi.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Expands table implementation */
struct KPTUExpandsT 
{
	KPTUniCharT Code;
	KPTUniCharT FirstConversion;
	KPTUniCharT SecondConversion;
};
typedef struct KPTUExpandsT KPTUExpandsT;

/* Mapping table implementation */
struct KPTUMappingT 
{
	KPTUniCharT Code;
	KPTUniCharT Mapping;
};
typedef struct KPTUMappingT KPTUMappingT;

/* Character category */
enum KPTUCategoryT
{
	eKPTUInvalidCategory = 0x0,
	eKPTUUpperCase       = 0x2,
	eKPTULowerCase       = 0x4,
	eKPTUTitleCase       = 0x8,
	eKPTUAlpha           = 0x10,
	eKPTUDigit           = 0x20,
	eKPTUPunct           = 0x40,
	eKPTUSymbol          = 0x80,
	eKPTUMark            = 0x100,
	eKPTUSpace           = 0x200,
	eKPTUControl         = 0x400,
	eKPTUDigitOther      = 0x800,
	eKPTUNewLine		 = 0x1000
};
typedef enum KPTUCategoryT KPTUCategoryT;

/* Unicode table pointer */
struct KPTPalUnicodeTableT
{
	size_t	kptUlowerToUpperSize;
	size_t  kptUUpperToLowerSize;
	size_t  kptUCaseFullMappingSize;
	size_t  kptUUpperToLowerUniqueSize;
	size_t  kptULowerToTitleSize;
	size_t  kptUTitleToLowerSize;
	size_t  kptUUpperToTitleFullMappingSize;
	size_t  kptUCaseExpandsSize;
	size_t  kptUTitleExpandsSize;
	size_t  kptUAlphaSize;
	size_t  kptUDigitSize;
	size_t  kptUPunctSize;
	size_t  kptUSymbolSize;
	size_t  kptUSpaceSize;
	size_t  kptUControlSize;
	size_t  kptUMirrorSize;
	size_t  kptUSpecialGreekCharToUpperSize;
	size_t  kptUMultipleLowerSize;

	KPTUMappingT*	kptUlowerToUpper;
	KPTUMappingT*	kptUUpperToLower;
	KPTUMappingT*	kptUCaseFullMapping;
	KPTUMappingT*	kptUUpperToLowerUnique;
	KPTUMappingT*	kptULowerToTitle;
	KPTUMappingT*	kptUTitleToLower;
	KPTUMappingT*	kptUUpperToTitleFullMapping;

	KPTUExpandsT*	kptUCaseExpands;
	KPTUExpandsT*	kptUTitleExpands;

	KPTUniCharT*	kptUAlpha;
	KPTUniCharT*	kptUDigit;
	KPTUniCharT*	kptUPunct;
	KPTUniCharT*	kptUSymbol;
	KPTUniCharT*	kptUSpace;
	KPTUniCharT*	kptUControl;

	KPTUMappingT*	kptUMirror;
	KPTUMappingT*	kptUSpecialGreekCharToUpper;
	KPTUMappingT*	kptUMultipleLower;
};
typedef struct KPTPalUnicodeTableT KPTPalUnicodeTableT;

KPT_LIB_SYSTEM
const KPTPalUnicodeTableT*
KPT_CALL
KPTPalGetUnicodeTable();

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* H_KPTUNICODETABLE_IMP_H */
