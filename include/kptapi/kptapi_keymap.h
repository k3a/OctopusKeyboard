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
 * @file    kptapi_keymap.h
 *
 * @brief   Key mapping types and structures.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTAPI_KEYMAP_H
#define H_KPTAPI_KEYMAP_H

#include "kptapi_lang.h"

/** Key mapping identifier. */
typedef struct KPTKeyMapIdT KPTKeyMapIdT;
struct KPTKeyMapIdT
{
	KPTLanguageIdT languageId;      /**< The runtime languageId of the keymap */
	KPTLanguageT language;          /**< The language of the keymap */	
	const char* manufacturer;       /**< The manufacturer name */
	const char* device;             /**< The device name */
	uint32_t group;                 /**< The group identifier */
};

/** Key mapping identifier list. */
typedef struct KPTKeyMapIdListAllocT KPTKeyMapIdListAllocT;
struct KPTKeyMapIdListAllocT
{
	KPTKeyMapIdT* ids;      /**< List of keymap identifiers */
	size_t count;           /**< Number of items in list */
};


/*****************************************************************************
 * Key map items
 *****************************************************************************/

/**
 * Attributes for a key map items.
 * Each attribute is represented by a single bit. If the bit is set, the attribute is
 * true/enabled. If the bit is not set, the attribute is false/disabled.
 */
enum KPTKeyMapItemAttribT
{
	eKPTKeyItemIsPressHold = KPTBIT(0), /**< The item is the 'Press and Hold' code for the key */
	eKPTKeyItemIsMultiTap = KPTBIT(1),  /**< The character is included in multi-tap sequences */

	eKPTKeyItemIsUpper = KPTBIT(16),    /**< The character is upper case */
	eKPTKeyItemIsLower = KPTBIT(17),    /**< The character is lower case */
	eKPTKeyItemIsPunct = KPTBIT(18),    /**< The character is punctuation */
	eKPTKeyItemIsDigit = KPTBIT(19),    /**< The character is a digit */
	eKPTKeyItemIsSpace = KPTBIT(20)     /**< The character is a space */
};
typedef enum KPTKeyMapItemAttribT KPTKeyMapItemAttribT;


/** A single item on a key. */
typedef struct KPTKeyMapItemT KPTKeyMapItemT;
struct KPTKeyMapItemT
{
	KPTUniCharT code;       /**< The unicode value associated with the item */
	uint32_t attributes;    /**< The attributes associated with the item (combination of KPTKeyMapItemAttribT flags) */
};

/*****************************************************************************
 * Key map keys
 *****************************************************************************/

/**
 * The physical position of a key.
 * Positional information may be used in some forms of error correction.
 */
typedef struct KPTKeyMapPosT KPTKeyMapPosT;
struct KPTKeyMapPosT
{
	int x;          /**< The X co-ordinate of the key */
	int y;          /**< The Y co-ordinate of the key */
	int height;     /**< The height of the key */
	int width;      /**< The width of the key */
};

/** A single key. */
typedef struct KPTKeyMapKeyT KPTKeyMapKeyT;
struct KPTKeyMapKeyT
{
	uint32_t id;                /**< Unique identifier for the object */
	uint32_t vId;               /**< Unique identifier associated with the object (such as a virtual key code) */
	size_t itemCount;           /**< Number of items on the key */
	KPTKeyMapItemT* items;      /**< One code for each item */
	uint32_t attributes;        /**< The combined KPTKeyMapItemT::attributes for all items in the key.
                                This is a combination of @ref KPTKeyMapItemAttribT flags and is automatically generated. */
	KPTKeyMapPosT position;     /**< The position of the key in the layout */
};

/*****************************************************************************
 * Key map layouts
 *****************************************************************************/

/** Physical keyboard-layout. */
typedef struct KPTKeyMapLayoutT KPTKeyMapLayoutT;
struct KPTKeyMapLayoutT
{
	KPTKeyMapIdT id;        /**< Unique identifier for the layout */
	size_t keyCount;        /**< Number of keys in the layout */
	KPTKeyMapKeyT* keys;    /**< All the keys in the layout */
};

/** Physical keyboard-layout list. */
typedef struct KPTKeyMapLayoutListAllocT KPTKeyMapLayoutListAllocT;
struct KPTKeyMapLayoutListAllocT
{
	KPTKeyMapLayoutT* layouts;  /**< Keymap layouts */
	size_t count;               /**< Number of layouts */
};


/*****************************************************************************
 * Key map operations
 *****************************************************************************/

/*
 * Opening
 */

/** Key map open parameters. */
typedef struct KPTKeyMapOpenT KPTKeyMapOpenT;
struct KPTKeyMapOpenT
{
	KPTBoolT createIfRequired;  /**< [in] Creates the key mapping if it does not exist */
	KPTBoolT created;           /**< [out] True if the key mapping had to be created */
};

/*
 * Activating
 */


/** A list of active key mapppings. */
typedef struct KPTKeyMapActiveIdListT KPTKeyMapActiveIdListT;
struct KPTKeyMapActiveIdListT
{
	KPTKeyMapIdT *ids;          /**< Active keymap identifiers */
	size_t count;               /**< Number of identifiers */
};


/*
 * Searching
 */

/** The type of key information to search for. */
enum KPTKeyMapSearchT
{
	eKPTKeyMapSearchId = 1,         /**< Gets the key that matches KPTKeyMapKeyT::id */
	eKPTKeyMapSearchVId = 2,        /**< Gets the key that matches KPTKeyMapKeyT::vId */
	eKPTKeyMapSearchCode = 3        /**< Gets the key(s) that contain the exact Unicode value */
};
typedef enum KPTKeyMapSearchT KPTKeyMapSearchT;

/** Contains information used to query key map data. */
typedef struct KPTKeyMapQueryT KPTKeyMapQueryT;
struct KPTKeyMapQueryT
{
	KPTKeyMapIdT layout;            /**< The layout to search */
	KPTBoolT useLayout;             /**< Whether to search the KPTKeyMapQueryT::layout (uses active layout if false) */
	uint32_t value;                 /**< The value to search for */
	KPTKeyMapSearchT search;        /**< What the value represents */
};

/** Results of a key map query. */
typedef struct KPTKeyMapResultAllocT KPTKeyMapResultAllocT;
struct KPTKeyMapResultAllocT
{
	KPTKeyMapKeyT* keys;    /**< Matching key(s) */
	size_t count;           /**< Number of matching keys */
};

/** A list of active key mapppings. */
typedef struct KPTKeyMapActiveIdListAllocT KPTKeyMapActiveIdListAllocT;
struct KPTKeyMapActiveIdListAllocT
{
	KPTKeyMapIdT **ids;     /**< Active keymap identifiers */
	size_t count;           /**< Number of identifiers */
};

#endif /* #ifndef H_KPTAPI_KEYMAP_H */
