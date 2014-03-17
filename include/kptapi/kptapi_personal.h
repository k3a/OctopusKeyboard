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
 * @file    kptapi_personal.h
 *
 * @brief   Structures for API personal dictionary operations.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTAPI_PERSONAL_H
#define H_KPTAPI_PERSONAL_H

/**
 * Enum for personal dictionary import/export format.
 */

enum KPTPDFormatT
{
	eKPTPDFormatWordList     = 1,   /**< A text file containing one entry per line */
};
typedef enum KPTPDFormatT KPTPDFormatT;


/** Structure used for an operation involving a word and tag */
typedef struct KPTPDWordTagOperationT KPTPDWordTagOperationT;
struct KPTPDWordTagOperationT
{
	KPTUniCharT* word;      /**< Word */
	uint32_t tag;           /**< Tag */
};


/** Structure used for an operation involving a word and identifier */
typedef struct KPTPDWordIdOperationT KPTPDWordIdOperationT;
struct KPTPDWordIdOperationT
{
	KPTUniCharT* word;      /**< Word */
	uint32_t id;            /**< Identifier */
};


/**
 * Structure used when querying the active personal dictionary by tag value
 */
typedef struct KPTPDTagQueryT KPTPDTagQueryT;
struct KPTPDTagQueryT
{
	size_t max;     /**< Maximum number of entries required (0 is unlimited) */
};


/**
 * Result of tag queries
 */
typedef struct KPTPDTagAllocT KPTPDTagAllocT;
struct KPTPDTagAllocT
{
	uint32_t* ids;   /**< Identifiers */
	size_t count;    /**< Number of entries in array */
};

/**
 * Enum for personal dictionary viewing options.
 */
enum KPTPDViewOptionT
{
	eKPTPDViewAlphaAscending     = 1,   /**< Alphabetical order */
	eKPTPDViewAlphaDescending    = 2,   /**< Reverse alphabetical order */
	eKPTPDViewMostFrequentFirst  = 3,   /**< Descending usage frequency order */
	eKPTPDViewLeastFrequentFirst = 4,   /**< Ascending usage frequency order */
	eKPTPDViewNewestFirst        = 5,   /**< Most recent additions first */
	eKPTPDViewOldestFirst        = 6    /**< Oldest additions first */
};
typedef enum KPTPDViewOptionT KPTPDViewOptionT;


/**
 * Enum for personal dictionary viewing filter
 */
enum KPTPDViewStateFilterT
{
	eKPTPDViewFilterCommitted   = 1,    /**< Committed words only */
	eKPTPDViewFilterUncommitted = 2,    /**< Uncommitted words only */
	eKPTPDViewFilterNone        = 3     /**< No filter applied */
};
typedef enum KPTPDViewStateFilterT KPTPDViewStateFilterT;

/**
 * Structure used when requesting a view on the active personal dictionary
 */
typedef struct KPTPDOpenViewRequestT KPTPDOpenViewRequestT;
struct KPTPDOpenViewRequestT
{
	KPTPDViewOptionT viewOption;    /**< Specify how contents are to be viewed */
	KPTPDViewStateFilterT state;    /**< State filter to be applied */
	const KPTUniCharT* query;       /**< Query string used for matching */
};


/** Handle to an open Personal Dictionary View */
typedef intptr_t KPTPDViewHandleT;

/** Structure containing reply to an OpenView request */
typedef struct KPTPDOpenViewReplyT KPTPDOpenViewReplyT;
struct KPTPDOpenViewReplyT
{
	KPTPDViewHandleT viewHandle;    /**< Handle to the view */
	uint32_t numWordsFound;         /**< Number of words found */
};


/** Structure used when viewing the active personal dictionary. The view is performed on an open view handle */ 
typedef struct KPTPDViewPageRequestT KPTPDViewPageRequestT;
struct KPTPDViewPageRequestT
{
	KPTPDViewHandleT viewHandle;    /**< Handle to the view */
	size_t offsetFromStart;         /**< 0=>from start */
	size_t numberToView;            /**< Maximum to return */
};


/** Structure containing the reply to a ViewPage request */
typedef struct KPTPDViewPageReplyT KPTPDViewPageReplyT;
struct KPTPDViewPageReplyT
{
	const KPTUniCharT** words;      /**< Array of words */
    size_t count;                   /**< How many were found */

};


/**
 * Structure used when committing words to the active personal dictionary.
 */
typedef struct KPTPDCommitWordT KPTPDCommitWordT;
struct KPTPDCommitWordT
{
	size_t numToCommit;  /**< Number of entries that are being committed */
	uint32_t* ids;       /**< Identifiers of words that are being committed */
};

/** Type to indicate which field will be used to search on when removing Personal Dictionary words */
enum KPTPDRemoveWordsFieldTypeT
{
	eKPTPDRemoveByWord = 1,     /**< Remove by word */
	eKPTPDRemoveById =   2,     /**< Remove by identifier */
	eKPTPDRemoveByTag =  3,     /**< Remove by tag */
};
typedef enum KPTPDRemoveWordsFieldTypeT KPTPDRemoveWordsFieldTypeT;


/**
 * Structure used when removing words from the active personal dictionary
 */
typedef struct KPTPDRemoveWordsT KPTPDRemoveWordsT;
struct KPTPDRemoveWordsT
{
	KPTPDRemoveWordsFieldTypeT fieldType;  /**< Specify how words are to be identified */
	size_t numToRemove;                    /**< Number to remove, not used with tag option */
	KPTUniCharT** wordsToRemove;           /**< The words that are to be removed */
	uint32_t* ids;                         /**< The identifiers of the words that are to be removed */
	uint32_t tag;                          /**< Remove all words with this tag */
};



/**
 * Structure used when adding words to the active personal dictionary
 */
typedef struct KPTPDAddWordsT KPTPDAddWordsT;
struct KPTPDAddWordsT
{
	size_t numToAdd;           /**< Number of words to be added */
	KPTUniCharT** wordsToAdd;  /**< Array of words to be added */
	uint32_t* tags;            /**< Array of tags, one for each word. NULL if none supplied */
};


/**
 * Structure used when setting or reading personal dictionary
 * configuration settings. External API.
 */
typedef struct KPTPDConfigT KPTPDConfigT;
struct KPTPDConfigT
{
	size_t maxEntries;      /**< Capacity, actual or desired */
};



/** Strcture containing the number of entries in the Personal Dictionary */
typedef struct KPTPDEntryCountDetailsT KPTPDEntryCountDetailsT;
struct KPTPDEntryCountDetailsT
{
	uint32_t uncommittedWordCount;  /**< Number of uncommitted words */
	uint32_t committedWordCount;    /**< Number of committed words */
};


/** Structure containing a requested Personal Dictionary word */
typedef struct KPTPDWordReplyT KPTPDWordReplyT;
struct KPTPDWordReplyT
{
	KPTUniCharT* word;  /**< The word's text */
	size_t itemCount;   /**< [in] Number of characters available (including NULL)
                             [out] number of required/written characters  (including NULL) */
};

#endif /* #ifndef H_KPTAPI_PERSONAL_H */
