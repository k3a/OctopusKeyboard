//
//  Layouts.cpp
//  OctopusDaemon
//
//  Created by K3A on 5/20/12.
//  Copyright (c) 2012 K3A. All rights reserved.
//

#include "Layouts.h"

#include "kptapi_framework.h"

/*-----------------------------------------------------------------------------
 iPhone en_US key layout
 -----------------------------------------------------------------------------*/
/*static KPTKeyMapItemT s_E161_1[] = 
{
    {KPT_TW('@'), eKPTKeyItemIsMultiTap|eKPTKeyItemIsPunct},
    {KPT_TW('.'), eKPTKeyItemIsMultiTap|eKPTKeyItemIsPunct},
    {KPT_TW('?'), eKPTKeyItemIsMultiTap|eKPTKeyItemIsPunct},
    {KPT_TW(','), eKPTKeyItemIsMultiTap|eKPTKeyItemIsPunct},
    {KPT_TW('!'), eKPTKeyItemIsMultiTap|eKPTKeyItemIsPunct},
    {KPT_TW('\''), eKPTKeyItemIsMultiTap|eKPTKeyItemIsPunct},
    {KPT_TW('1'), eKPTKeyItemIsMultiTap|eKPTKeyItemIsDigit|eKPTKeyItemIsPressHold}
};*/

static KPTKeyMapItemT s_iphone_en_US_11[] = 
{
    {KPT_TW('q'), 0},
};

static KPTKeyMapItemT s_iphone_en_US_12[] = 
{
    {KPT_TW('w'), 0},
};

static KPTKeyMapItemT s_iphone_en_US_13[] = 
{
    {KPT_TW('e'), 0},
    {KPT_TW('è'), eKPTKeyItemIsPressHold},
    {KPT_TW('é'), eKPTKeyItemIsPressHold},
    {KPT_TW('ê'), eKPTKeyItemIsPressHold},
    {KPT_TW('ë'), eKPTKeyItemIsPressHold},
    {KPT_TW('ē'), eKPTKeyItemIsPressHold},
    {KPT_TW('ė'), eKPTKeyItemIsPressHold},
    {KPT_TW('ę'), eKPTKeyItemIsPressHold},
};

static KPTKeyMapItemT s_iphone_en_US_14[] = 
{
    {KPT_TW('r'), 0},
};

static KPTKeyMapItemT s_iphone_en_US_15[] = 
{
    {KPT_TW('t'), 0},
};

static KPTKeyMapItemT s_iphone_en_US_16[] = 
{
    {KPT_TW('y'), 0},
    {KPT_TW('Ÿ'), eKPTKeyItemIsPressHold},
};

static KPTKeyMapItemT s_iphone_en_US_17[] = 
{
    {KPT_TW('u'), 0},
    {KPT_TW('û'), eKPTKeyItemIsPressHold},
    {KPT_TW('ü'), eKPTKeyItemIsPressHold},
    {KPT_TW('ù'), eKPTKeyItemIsPressHold},
    {KPT_TW('ú'), eKPTKeyItemIsPressHold},
    {KPT_TW('ū'), eKPTKeyItemIsPressHold},
};

static KPTKeyMapItemT s_iphone_en_US_18[] = 
{
    {KPT_TW('i'), 0},
    {KPT_TW('î'), eKPTKeyItemIsPressHold},
    {KPT_TW('ï'), eKPTKeyItemIsPressHold},
    {KPT_TW('í'), eKPTKeyItemIsPressHold},
    {KPT_TW('ī'), eKPTKeyItemIsPressHold},
    {KPT_TW('į'), eKPTKeyItemIsPressHold},
    {KPT_TW('ì'), eKPTKeyItemIsPressHold},
};

static KPTKeyMapItemT s_iphone_en_US_19[] = 
{
    {KPT_TW('o'), 0},
    {KPT_TW('ô'), eKPTKeyItemIsPressHold},
    {KPT_TW('ö'), eKPTKeyItemIsPressHold},
    {KPT_TW('ò'), eKPTKeyItemIsPressHold},
    {KPT_TW('ò'), eKPTKeyItemIsPressHold},
    {KPT_TW('ó'), eKPTKeyItemIsPressHold},
    {KPT_TW('œ'), eKPTKeyItemIsPressHold},
    {KPT_TW('ø'), eKPTKeyItemIsPressHold},
    {KPT_TW('ō'), eKPTKeyItemIsPressHold},
    {KPT_TW('õ'), eKPTKeyItemIsPressHold},
};

static KPTKeyMapItemT s_iphone_en_US_110[] = 
{
    {KPT_TW('p'), 0},
};

static KPTKeyMapItemT s_iphone_en_US_21[] = 
{
    {KPT_TW('a'), 0},
    {KPT_TW('à'), eKPTKeyItemIsPressHold},
    {KPT_TW('á'), eKPTKeyItemIsPressHold},
    {KPT_TW('â'), eKPTKeyItemIsPressHold},
    {KPT_TW('ä'), eKPTKeyItemIsPressHold},
    {KPT_TW('æ'), eKPTKeyItemIsPressHold},
    {KPT_TW('ã'), eKPTKeyItemIsPressHold},
    {KPT_TW('å'), eKPTKeyItemIsPressHold},
    {KPT_TW('ā'), eKPTKeyItemIsPressHold},
	{KPT_TW('ą'), eKPTKeyItemIsPressHold},
};

static KPTKeyMapItemT s_iphone_en_US_22[] = 
{
    {KPT_TW('s'), 0},
    {KPT_TW('ß'), eKPTKeyItemIsPressHold},
    {KPT_TW('ś'), eKPTKeyItemIsPressHold},
    {KPT_TW('š'), eKPTKeyItemIsPressHold},
};

static KPTKeyMapItemT s_iphone_en_US_23[] = 
{
    {KPT_TW('d'), 0},
};

static KPTKeyMapItemT s_iphone_en_US_24[] = 
{
    {KPT_TW('f'), 0},
};

static KPTKeyMapItemT s_iphone_en_US_25[] = 
{
    {KPT_TW('g'), 0},
};

static KPTKeyMapItemT s_iphone_en_US_26[] = 
{
    {KPT_TW('h'), 0},
};

static KPTKeyMapItemT s_iphone_en_US_27[] = 
{
    {KPT_TW('j'), 0},
};

static KPTKeyMapItemT s_iphone_en_US_28[] = 
{
    {KPT_TW('k'), 0},
};

static KPTKeyMapItemT s_iphone_en_US_29[] = 
{
    {KPT_TW('l'), 0},
    {KPT_TW('ł'), eKPTKeyItemIsPressHold},
};

static KPTKeyMapItemT s_iphone_en_US_31[] = 
{
    {KPT_TW('z'), 0},
    {KPT_TW('ž'), eKPTKeyItemIsPressHold},
    {KPT_TW('ź'), eKPTKeyItemIsPressHold},
    {KPT_TW('ż'), eKPTKeyItemIsPressHold},
};

static KPTKeyMapItemT s_iphone_en_US_32[] = 
{
    {KPT_TW('x'), 0},
};

static KPTKeyMapItemT s_iphone_en_US_33[] = 
{
    {KPT_TW('c'), 0},
    {KPT_TW('ç'), eKPTKeyItemIsPressHold},
    {KPT_TW('ć'), eKPTKeyItemIsPressHold},
    {KPT_TW('č'), eKPTKeyItemIsPressHold},
};

static KPTKeyMapItemT s_iphone_en_US_34[] = 
{
    {KPT_TW('v'), 0},
};

static KPTKeyMapItemT s_iphone_en_US_35[] = 
{
    {KPT_TW('b'), 0},
};

static KPTKeyMapItemT s_iphone_en_US_36[] = 
{
    {KPT_TW('n'), 0},
    {KPT_TW('ñ'), eKPTKeyItemIsPressHold},
    {KPT_TW('ń'), eKPTKeyItemIsPressHold},
};

static KPTKeyMapItemT s_iphone_en_US_37[] = 
{
    {KPT_TW('m'), 0},
};

static KPTKeyMapItemT s_iphone_en_US_space[] = 
{
    {KPT_TW(' '), eKPTKeyItemIsSpace},
};

/*
 Note that the combined attributes field is left at zero, this information can be
 be automatically generated by KPTCMD_KEYMAP_SETLAYOUT.
 */

static KPTKeyMapKeyT s_iphone_en_US_keys[] = 
{
    {1, 'q', sizeof(s_iphone_en_US_11) / sizeof(KPTKeyMapItemT), s_iphone_en_US_11,    0, {0,	0,	1, 1}},
    {2, 'w', sizeof(s_iphone_en_US_12) / sizeof(KPTKeyMapItemT), s_iphone_en_US_12,    0, {0,	1,	1, 1}},
    {3, 'e', sizeof(s_iphone_en_US_13) / sizeof(KPTKeyMapItemT), s_iphone_en_US_13,    0, {0,	2,	1, 1}},
    {4, 'r', sizeof(s_iphone_en_US_14) / sizeof(KPTKeyMapItemT), s_iphone_en_US_14,    0, {0,	3,	1, 1}},
    {5, 't', sizeof(s_iphone_en_US_15) / sizeof(KPTKeyMapItemT), s_iphone_en_US_15,    0, {0,	4,	1, 1}},
    {6, 'y', sizeof(s_iphone_en_US_16) / sizeof(KPTKeyMapItemT), s_iphone_en_US_16,    0, {0,	5,	1, 1}},
    {7, 'u', sizeof(s_iphone_en_US_17) / sizeof(KPTKeyMapItemT), s_iphone_en_US_17,    0, {0,	6,	1, 1}},
    {8, 'i', sizeof(s_iphone_en_US_18) / sizeof(KPTKeyMapItemT), s_iphone_en_US_18,    0, {0,	7,	1, 1}},
    {9, 'o', sizeof(s_iphone_en_US_19) / sizeof(KPTKeyMapItemT), s_iphone_en_US_19,    0, {0,	8,	1, 1}},
    {10, 'p', sizeof(s_iphone_en_US_110) / sizeof(KPTKeyMapItemT), s_iphone_en_US_110, 0, {0,	9,	1, 1}},
    
    {11, 'a', sizeof(s_iphone_en_US_21) / sizeof(KPTKeyMapItemT), s_iphone_en_US_21,    0, {1,	0,	1, 1}},
    {12, 's', sizeof(s_iphone_en_US_22) / sizeof(KPTKeyMapItemT), s_iphone_en_US_22,    0, {1,	1,	1, 1}},
    {13, 'd', sizeof(s_iphone_en_US_23) / sizeof(KPTKeyMapItemT), s_iphone_en_US_23,    0, {1,	2,	1, 1}},
    {14, 'f', sizeof(s_iphone_en_US_24) / sizeof(KPTKeyMapItemT), s_iphone_en_US_24,    0, {1,	3,	1, 1}},
    {15, 'g', sizeof(s_iphone_en_US_25) / sizeof(KPTKeyMapItemT), s_iphone_en_US_25,    0, {1,	4,	1, 1}},
    {16, 'h', sizeof(s_iphone_en_US_26) / sizeof(KPTKeyMapItemT), s_iphone_en_US_26,    0, {1,	5,	1, 1}},
    {17, 'j', sizeof(s_iphone_en_US_27) / sizeof(KPTKeyMapItemT), s_iphone_en_US_27,    0, {1,	6,	1, 1}},
    {18, 'k', sizeof(s_iphone_en_US_28) / sizeof(KPTKeyMapItemT), s_iphone_en_US_28,    0, {1,	7,	1, 1}},
    {19, 'l', sizeof(s_iphone_en_US_29) / sizeof(KPTKeyMapItemT), s_iphone_en_US_29,    0, {1,	8,	1, 1}},
    
    {20, 'z', sizeof(s_iphone_en_US_31) / sizeof(KPTKeyMapItemT), s_iphone_en_US_31,    0, {2, 1,	1, 1}},
    {21, 'x', sizeof(s_iphone_en_US_32) / sizeof(KPTKeyMapItemT), s_iphone_en_US_32,    0, {2, 2,	1, 1}},
    {22, 'c', sizeof(s_iphone_en_US_33) / sizeof(KPTKeyMapItemT), s_iphone_en_US_33,    0, {2, 3,	1, 1}},
    {23, 'v', sizeof(s_iphone_en_US_34) / sizeof(KPTKeyMapItemT), s_iphone_en_US_34,    0, {2, 4,	1, 1}},
    {24, 'b', sizeof(s_iphone_en_US_35) / sizeof(KPTKeyMapItemT), s_iphone_en_US_35,    0, {2, 5,	1, 1}},
    {25, 'n', sizeof(s_iphone_en_US_36) / sizeof(KPTKeyMapItemT), s_iphone_en_US_36,    0, {2, 6,	1, 1}},
    {26, 'm', sizeof(s_iphone_en_US_37) / sizeof(KPTKeyMapItemT), s_iphone_en_US_37,    0, {2, 7,	1, 1}},
    
    {27, ' ', sizeof(s_iphone_en_US_space) / sizeof(KPTKeyMapItemT), s_iphone_en_US_space, 0, {3, 3, 4, 4}},
};

/* Define a grouping for the keymap to support merging */
#define GROUP_IOS_KEYS 27

/* Define the keymap layout */
const struct KPTKeyMapLayoutT s_layout_iphone_en_US = 
{
	{												/* Key Map Identifier */
		0,											/* No runtime language identifier yet */
		{"en", "Latn"},								/* Keymap Language and script */
		"K3A",										/* Keymap Manufacturer */
		"iDevice",									/* Device name */
		GROUP_IOS_KEYS								/* Key map compatability group */
	},
	sizeof(s_iphone_en_US_keys) / sizeof(KPTKeyMapKeyT),	/* Number of keys */
	s_iphone_en_US_keys										/* Pointer to key data */
};



