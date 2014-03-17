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
 * @file    kptapi_inputmgr.h
 *
 * @brief   Input Manager Types and Structures.
 *
 * @details 
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTAPI_INPUTMGR_H
#define H_KPTAPI_INPUTMGR_H

#include "kptapi_suggs.h"

/*
 *****************************************************************************/
/** Specifies the number of characters to remove from the input. */
typedef struct KPTInpMgrRemoveCharsT KPTInpMgrRemoveCharsT;
struct KPTInpMgrRemoveCharsT
{
	size_t numBeforeCursor;     /**< Number of characters to remove before the cursor */
	size_t numAfterCursor;      /**< Number of characters to remove after the cursor */
};

/*****************************************************************************
 * Insertion
 *****************************************************************************/

/** Insert attributes enum type. */
enum KPTInpMgrInsertAttribT
{
	eKPTInsertAmbiguous = KPTBIT(0),    /**< Insert character or text as ambiguous  */
	eKPTInsertCapSentence = KPTBIT(1),  /**< The character or text should respect sentence casing if appropriate */
	eKPTInsertCap = KPTBIT(2),          /**< The character or text should be inserted capitalised */
	eKPTInsertNoLearning = KPTBIT(3),   /**< The character or text should not cause any learning of words to occur */	
	eKPTInsertMapKeyID = KPTBIT(4),     /**< The id is to be match against a key ID in a key map */
	eKPTInsertMapKeyVID = KPTBIT(5),    /**< The id is to be match against a vkey ID in a key map */
	eKPTInsertSymbol = KPTBIT(6),       /**< The character or text is fixed with-in the composition object */
};
typedef enum KPTInpMgrInsertAttribT KPTInpMgrInsertAttribT;

/** Defines a character to be inserted. */
typedef struct KPTInpMgrInsertCharT KPTInpMgrInsertCharT;
struct KPTInpMgrInsertCharT
{
	KPTUniCharT insertChar;     /**< The character to insert */
	uint32_t attributes;        /**< The type of character to insert (combination of @ref KPTInpMgrInsertAttribT flags) */
	uint32_t id;                /**< The id value associated with the item */
};

/** Defines a string to be inserted. */
typedef struct KPTInpMgrInsertStringT KPTInpMgrInsertStringT;
struct KPTInpMgrInsertStringT
{
	const KPTUniCharT* insertString;    /**< The string to insert */
	size_t length;                      /**< The number of characters in the string to insert */
	KPTInpMgrRemoveCharsT toRemove;     /**< Counts of characters to remove before inserting string */
	uint32_t attributes;                /**< The attributes to apply to each character inserted 
                                        (combination of @ref KPTInpMgrInsertAttribT flags)*/
	const uint32_t* ids;                /**< The ids of each character */
};

/** Specifies a suggestion object to be inserted. */
typedef struct KPTInpMgrInsertSuggRequestT KPTInpMgrInsertSuggRequestT;
struct KPTInpMgrInsertSuggRequestT
{
	uint32_t suggestionSet;     /**< SuggestionSet identifier */
	uint32_t suggestionId;      /**< Identifier of suggestion to be inserted */
	KPTBoolT appendSpace;       /**< Whether a space should be inserted at the end of the suggestion */
};

/** Defines the operations performed by the core when inserting a suggestion.
  This information can be used by the caller to synchronise user interfaces. */
typedef struct KPTInpMgrInsertSuggReplyInfoT KPTInpMgrInsertSuggReplyInfoT;
struct KPTInpMgrInsertSuggReplyInfoT
{
	KPTInpMgrRemoveCharsT charactersRemoved;    /**< Details of the characters removed before text was added */
	KPTUniCharT* modificationString;            /**< String of text which was inserted after characters were removed */
	size_t modStringItemCount;                  /**< Length of modificationString. Includes terminating NULL character */
};

/** Reply structure for suggestion insertion */
typedef struct KPTInpMgrInsertSuggReplyAllocT KPTInpMgrInsertSuggReplyAllocT;
struct KPTInpMgrInsertSuggReplyAllocT
{
	KPTInpMgrInsertSuggReplyInfoT* insertReplyInfo;  /**< Reply to insertion */
	size_t count; /**< Always 1 */
};


/** Defines the details of a Reset operation. */
typedef struct KPTInpMgrResetT KPTInpMgrResetT;
struct KPTInpMgrResetT
{
	uint32_t options;           /**< Reserved (must be zero) */
	const KPTUniCharT* text;    /**< New contents of the Input Buffer */
};



/** Defines the details of a Replace Contents operation. */
typedef struct KPTInpMgrReplaceContentsT KPTInpMgrReplaceContentsT;
struct KPTInpMgrReplaceContentsT
{
	int32_t firstCharIndex;                 /**< Index of first character to replace */
	int32_t lastCharIndex;                  /**< Index of last character to replace */
	const KPTUniCharT* replacementText;     /**< Text to insert  */
	size_t replacementLength;               /**< Maximum length to insert, or 0 to write up to terminating NULL character */
};



/** Options for insertion point information. */
enum KPTInpMgrIPOptionsT
{
	eKPTInsertionPointGetEndOfText = KPTBIT(0),			/**< Only whitespace follows */
	eKPTInsertionPointGetStartOfSentence = KPTBIT(1),	/**< Start of the sentence */
};
typedef enum KPTInpMgrIPOptionsT KPTInpMgrIPOptionsT;

enum KPTInpMgrIPStateT
{
	eKPTInsertionPointEndOfText = KPTBIT(0),			/**< Only whitespace follows */
	eKPTInsertionPointStartOfSentence = KPTBIT(1),		/**< Start of the sentence */
};
typedef enum KPTInpMgrIPStateT KPTInpMgrIPStateT;

typedef struct KPTInpMgrGetIPInfoT KPTInpMgrGetIPInfoT;
struct KPTInpMgrGetIPInfoT
{
	uint32_t options;		/**< Insertion point options */
	uint32_t state;			/**<Insertion point state */
};
/** Character Attribute enum type. */
enum KPTInpMgrCharacterAttribT
{
	eKPTCharacterAmbiguous = KPTBIT(0), /**< Ambiguous character (fixed if not set) */
	eKPTCharacterUpper = KPTBIT(1),     /**< Uppercase character (lower if not set) */
	eKPTCharacterSymbol = KPTBIT(2),    /**< Symbol character */
};
typedef enum KPTInpMgrCharacterAttribT KPTInpMgrCharacterAttribT;

/** Specifies the attributes to update during an Update Current Word operation. */
typedef struct KPTInpMgrUpdateCurrWordAttribT KPTInpMgrUpdateCurrWordAttribT;
struct KPTInpMgrUpdateCurrWordAttribT
{
	const uint32_t* attributes;     /**< New attributes for each character, combination of @ref KPTInpMgrCharacterAttribT flags */
	size_t offset;                  /**< The offset within the current word at which to begin updating attributes */
	size_t count;                   /**< The number of characters to update */
};


/** Defines the contents of a Composition. */
typedef struct KPTInpMgrCompositionT KPTInpMgrCompositionT;
struct KPTInpMgrCompositionT
{
	uint32_t fieldMask;                     /**< Identifies fields in use (@ref KPTInpMgrCompositionMaskT)*/
	const KPTUniCharT* compString;          /**< The current composition string */
	const uint32_t* ids;                    /**< The ids of each current composition string character (e.g. key code) */
	const uint32_t* attributes;             /**< The attributes of each current composition string character (e.g. is ambiguous etc). Combination of @ref KPTInpMgrCharacterAttribT flags */
	size_t compStringLength;                /**< The number of characters in the composition string, NOT including the NULL character */
	const KPTUniCharT* originalCompString;  /**< The original composition string (to remember case etc) */
	size_t originalCompStringLength;        /**< The number of characters in the original composition string, NOT including the NULL character */
};

/**
 * Field-in-use masks for KPTInpMgrCompositionT::fieldMask.
 */
enum KPTInpMgrCompositionMaskT
{
	/** KPTInpMgrCompositionT::compString, KPTInpMgrCompositionT::compStringLength are in use*/
	eKPTCompositionMaskCompString = KPTBIT(0),

	/** KPTInpMgrCompositionT::ids is in use*/
	eKPTCompositionMaskIds = KPTBIT(1),

	/** KPTInpMgrCompositionT::attributes is in use*/
	eKPTCompositionMaskAttributes = KPTBIT(2),

	/** KPTInpMgrCompositionT::originalCompString,  KPTInpMgrCompositionT::originalCompStringLength are in use*/
	eKPTCompositionMaskOrigCompString = KPTBIT(3),

	/** All fields in the KPTInpMgrCompositionT structure are in use */
	eKPTCompositionMaskAll = (eKPTCompositionMaskCompString | eKPTCompositionMaskIds | eKPTCompositionMaskAttributes | eKPTCompositionMaskOrigCompString)
};
typedef enum KPTInpMgrCompositionMaskT KPTInpMgrCompositionMaskT;

/** Defines the contents of a Current Word Object. */
typedef struct KPTInpMgrCurrentWordT KPTInpMgrCurrentWordT;
struct KPTInpMgrCurrentWordT
{
	uint32_t fieldMask;                 /**< Identifies fields in use (@ref KPTInpMgrCurrentWordMaskT)*/
	const KPTUniCharT* fixedPrefix;     /**< The fixed prefix string */
	size_t fixedPrefixLength;           /**< The number of elements in the fixed prefix string, NOT including the NULL character */
	const KPTUniCharT* fixedSuffix;     /**< The fixed suffix string */
	size_t fixedSuffixLength;           /**< The number of elements in the fixed suffix string, NOT including the NULL character */
	size_t suggestionOffset;			/**< The offset into the current word where the suggestion starts */
	KPTInpMgrCompositionT composition;  /**< The composition object */
};

/**
 * Field-in-use masks for KPTInpMgrCurrentWordT::fieldMask.
 */
enum KPTInpMgrCurrentWordMaskT
{
	/** KPTInpMgrCurrentWordT::fixedPrefix, KPTInpMgrCurrentWordT::fixedPrefixLength are in use*/
	eKPTCurrentWordMaskFixedPrefix = KPTBIT(0),

	/** KPTInpMgrCurrentWordT::fixedSuffix, KPTInpMgrCurrentWordT::fixedSuffixLength are in use*/
	eKPTCurrentWordMaskFixedSuffix = KPTBIT(1),
	
	/** KPTInpMgrCurrentWordT::composition is in use*/
	eKPTCurrentWordMaskComposition = KPTBIT(2),

	/** All fields in the KPTInpMgrCurrentWordT structure are in use*/
	eKPTCurrentWordMaskAll = (eKPTCurrentWordMaskFixedPrefix | eKPTCurrentWordMaskFixedSuffix | eKPTCurrentWordMaskComposition)
};
typedef enum KPTInpMgrCurrentWordMaskT KPTInpMgrCurrentWordMaskT;

/*****************************************************************************
 * Navigation
 *****************************************************************************/

/** Information about the input Cursor. */
typedef struct KPTInpMgrCursorDetailsT KPTInpMgrCursorDetailsT;
struct KPTInpMgrCursorDetailsT
{
	size_t cursorPos;       /**< Current cursor position */
	size_t totalLength;     /**< Total length of data entity */
};

/** Cursor Movement Type. */
enum KPTInpMgrCursorMoveT
{
	eKPTSeekStart =    0,  /**< Move Cursor relative from start of data entity */
	eKPTSeekEnd =      1,  /**< Move Cursor relative from end of data entity */
	eKPTSeekRelative = 2   /**< Move Cursor relative from current cursor position: positive values are towards the end of the data entity; negative values are towards the beginning of the data entity */
};
typedef enum KPTInpMgrCursorMoveT KPTInpMgrCursorMoveT;


/**
 * Structure use to configure the input manager.
 */
typedef struct KPTInpMgrConfigT KPTInpMgrConfigT;
struct KPTInpMgrConfigT
{
	uint32_t fieldMask;                     /**< Identifies fields in use (@ref KPTInpMgrConfigMaskT) */
	KPTBoolT mergeCRLFOn;                   /**< Whether to merge CRLF sequences to a single character */
};

/**
 * Field-in-use masks for KPTInpMgrConfigT::fieldMask.
 */
enum KPTInpMgrConfigMaskT
{
	/** KPTInpMgrConfigT::mergeCRLFOn sets, or gets, a value that indicates the line-endings behaviour */
	eKPTInpMgrConfigMaskMergeCRLF = KPTBIT(0),

	/** All fields in the KPTInpMgrConfigT structure are in use*/
	eKPTInpMgrConfigMaskAll = (eKPTInpMgrConfigMaskMergeCRLF )
};

#endif /* #ifndef H_KPTAPI_INPUTMGR_H */
