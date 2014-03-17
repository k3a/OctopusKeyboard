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
 * @file    kptapi_lang.h
 *
 * @brief   Structures for API language operations.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTAPI_LANG_H
#define H_KPTAPI_LANG_H

/** 
 * Language information (BCP47) with following format
 *
 * language-extlang-script-region-variants-extensions-privateuse
 *
 * language     : language subtag 
 *
 * extlang      : extended language subtag 
 *
 * script       : script subtag 
 *
 * region       : region subtag 
 *
 * variants     : variant subtag 
 *
 * extensions   : extensions subtag
 *
 * privateuse   : privateuse subtag
 */
typedef struct KPTLanguageT KPTLanguageT;
struct KPTLanguageT
{
    const char* language;   /**< BCP47 language tag */
    const char* script;     /**< BCP47 script tag */
};

typedef uint32_t KPTLanguageIdT; /**< Runtime Language identifier */

/**
 * Language information structure
 */
typedef struct KPTLanguageInfoT KPTLanguageInfoT;
struct KPTLanguageInfoT
{
	KPTLanguageIdT id;      /**< runtime id for the language */
	KPTLanguageT language;  /**< BCP47 value for the language */
};

/** List of languages (runtime id and BCP47 value) */
typedef struct KPTLangListAllocT KPTLangListAllocT;
struct KPTLangListAllocT
{
	KPTLanguageInfoT* languages;    /**< language entries */
	size_t count;                   /**< number of items in list */
};

/**
 * Language matching type
 */
enum KPTLanguageMatchingTypeT
{
	eKPTLangFiltering = 0,      /**< return zero or more than one if matched */
	eKPTLangLookup              /**< return zero or only one if matched*/
};
typedef enum KPTLanguageMatchingTypeT KPTLanguageMatchingTypeT;

/**
 * Language matching structure
 */
typedef struct KPTLanguageMatchingT KPTLanguageMatchingT;
struct KPTLanguageMatchingT
{
	KPTLanguageMatchingTypeT type;  /**< filtering or lookup type */   
	KPTLanguageT language;          /**< language to match */    
};

#endif /* #ifndef H_KPTAPI_LANG_H */
