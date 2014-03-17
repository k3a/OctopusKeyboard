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
 * @file    kptapi_suggs.h
 *
 * @brief   Structures for API suggestion generation.
 *
 * @details 
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTAPI_SUGGS_H
#define H_KPTAPI_SUGGS_H

#include "kptapi_suggtypes.h"

/**
 * Structure use to configure suggestion generation.
 * These parameters are expected to change infrequently.
 */
typedef struct KPTSuggConfigT KPTSuggConfigT;
struct KPTSuggConfigT
{
	uint32_t fieldMask;             /**< Identifies fields in use (@ref KPTSuggConfigMaskT)*/
	size_t maxNumSuggestions;       /**< Maximum number of suggestions to be supplied */
	size_t numElisionCompletions;   /**< How many elision completions are allowed */

	/** 
	Threshold at which a word will be a potential suggestion.
	The Suggestion Engine can be asked to limit its suggestions to the most commonly used words 
	by specifying a threshold, in the range 0 to 100. A value of 0 means all words will be considered.
	The set of words from which suggestions will be drawn decreases as the threshold is increased.
	*/
	uint32_t suggestionThreshold;
	KPTBoolT proximitySuggestionOn;		/**< Enable or disable proximity suggestion */
	KPTBoolT errorCorrectionOn;         /**< Enable or disable error correction */
	/**
	Allow word completion. If disabled, the length of suggested words is 
	determined by the number of characters entered.
	*/
	KPTBoolT completionOn;
	KPTBoolT useStoredCaps;         /**< Use the capitalisation in the source dictionary */
	KPTBoolT forceLower;            /**< Suggest in lower case only */
	KPTBoolT forceUpper;            /**< Suggest in upper case only */
	KPTBoolT useSentenceCase;       /**< Use sentence case for first letter of suggested words */

	/** Use capitalisation as entered by the user */
	KPTBoolT honourUserCaps;

	KPTBoolT capNext;       /**<Capitalise the character after the IP.*/

};

/**
 * Field-in-use masks for KPTSuggConfigT::fieldMask
 */
enum KPTSuggConfigMaskT
{
	eKPTSuggsConfigMaxSuggestions = KPTBIT(0),      /**< KPTSuggConfigT::maxNumSuggestions is in use */
	eKPTSuggsConfigMaxElisions = KPTBIT(2),         /**< KPTSuggConfigT::numElisionCompletions is in use */
	eKPTSuggsConfigThreshold = KPTBIT(3),           /**< KPTSuggConfigT::suggestionThreshold is in use */
	eKPTSuggsConfigProximitySuggestions = KPTBIT(4),  /**< KPTSuggConfigT::proximitySuggestionOn is in use */
	eKPTSuggsConfigErrorCorrection = KPTBIT(5),     /**< KPTSuggConfigT::errorCorrectionOn is in use */
	eKPTSuggsConfigCompletion = KPTBIT(6),          /**< KPTSuggConfigT::completionOn is in use */
	eKPTSuggsConfigUseStoredCaps = KPTBIT(7),       /**< KPTSuggConfigT::useStoredCaps is in use */
	eKPTSuggsConfigForceLower = KPTBIT(8),          /**< KPTSuggConfigT::forceLower is in use */
	eKPTSuggsConfigForceUpper = KPTBIT(9),          /**< KPTSuggConfigT::forceUpper is in use */
	eKPTSuggsConfigSentenceCase = KPTBIT(10),       /**< KPTSuggConfigT::useSentenceCase is in use */
	eKPTSuggsConfigUserCaps = KPTBIT(11),           /**< KPTSuggConfigT::honourUserCaps is in use */
	eKPTSuggsConfigCapNext = KPTBIT(12),			/**< KPTSuggConfigT::CapNext is in use */

    /** All fields in the KPTSuggConfigT structure are in use*/
    eKPTSuggsConfigMaskAll = (eKPTSuggsConfigMaxSuggestions | eKPTSuggsConfigMaxElisions
                            | eKPTSuggsConfigThreshold  | eKPTSuggsConfigProximitySuggestions | eKPTSuggsConfigErrorCorrection
                            | eKPTSuggsConfigCompletion | eKPTSuggsConfigUseStoredCaps | eKPTSuggsConfigForceLower
                            | eKPTSuggsConfigForceUpper | eKPTSuggsConfigSentenceCase | eKPTSuggsConfigUserCaps
							| eKPTSuggsConfigCapNext)

};
typedef enum KPTSuggConfigMaskT KPTSuggConfigMaskT;

/**
 *	Structure containing suggestion information
 */
typedef struct KPTSuggEntryT KPTSuggEntryT;
struct KPTSuggEntryT
{
	uint32_t suggestionId;                  /**< Suggestion identifier */
	uint32_t suggestionType;                /**< Describes the source of the suggestion (@ref kptapi_suggtypes.h)*/
	const KPTUniCharT* suggestionString;    /**< Suggestion string */
	size_t suggestionLength;                /**< Length of suggestion (not including NULL character) */
	intptr_t extraDetails;                  /**< This field depends on the suggestion type (@ref kptapi_suggtypes.h)*/
};

/** Structure used when requesting a suggestion */
typedef struct KPTSuggWordsRequestT KPTSuggWordsRequestT;
struct KPTSuggWordsRequestT
{
	uint32_t suggestionTag; /**< Tag used to filter suggestions (use 0 for no filtering) */
};

/** Structure containing a list of suggestion words */
typedef struct KPTSuggWordsReplyT KPTSuggWordsReplyT;
struct KPTSuggWordsReplyT
{
	uint32_t suggestionSet;             /**< Identfier for the set of suggestions */
	const KPTSuggEntryT* suggestions;   /**< List of suggestions */
	size_t count;                       /**< Number of suggestions in the list */
};



#endif /* #ifndef H_KPTAPI_SUGGS_H */
