//
//  examples.cpp
//  CoreRegressSystem
//
//  Created by K3A on 5/19/12.
//  Copyright (c) 2012 K3A. All rights reserved.
//

#include "examples.h"

#include <unistd.h> // size_t etc
#include <stdio.h> // printf
#include <stddef.h> // ptrdiff_t

#include "kptapi_framework.h"
#include "kptapi_dict.h"
#include "kptapi_lang.h"
#include "kptapi_suggs.h"
#include "kptapi_inputmgr.h"
#include "kptapi_keymap.h"
#include "kptapi_componenttypes.h"

#include "kptstrings.h"
#include "kptunicode.h"

#include "TextInput.h"
#include "main.h"
#include <stdlib.h>

#pragma mark - HELPERS --------------------------------------------------------------------------------------------------------------------

size_t UniToSys(KPTSysCharT* &outMem, const KPTUniCharT* inpMem)
{
    size_t inpLen = 0;
    KPTStrLenU(inpMem,&inpLen);
    if (!inpLen)
    {
        outMem = (KPTSysCharT*)malloc(4);
        outMem[0] = 0;
    }
    
    KPTSysCharT* sysBuff = (KPTSysCharT*)malloc(2 * (inpLen+1));
    sysBuff[0] = 0;
    unsigned uniNum = UniCharToSysChar(sysBuff, 2 * (inpLen+1), inpMem, inpLen);
    
    outMem = sysBuff;
    return uniNum;
}

#define SysPrintF(x, ...) printf(x, ##__VA_ARGS__)
#define UniPrint(x, ...) { char* xSys; UniToSys(xSys, x); printf(xSys, ##__VA_ARGS__); free(xSys); }


#pragma mark - DICTIONARY -----------------------------------------------------------------------------------------------------------------

static void ShowList(KPTLangListAllocT* aList);
static void ShowDictList(KPTDictListAllocT* aList);

/*
 * Example function for KPTCMD_DICTIONARY_GETLIST.
 * This example gets a list of all the installed dictionaries and prints
 * information about each one.
 * The example code then repeats the process using language matching.
 *
 * SysPrintF represents a system printf function.
 */
KPTResultT
Example_KPTCMD_DICTIONARY_GETLIST(void)
{
	KPTResultT result;
	KPTDictListAllocT dictionaryList = {0};  /* Must initialise all AllocT structures. */
	KPTLanguageMatchingT langFilter = {eKPTLangFiltering, {"en-*-x-dict", NULL}};
	KPTLanguageMatchingT langLookup = {eKPTLangLookup, {"en-*-x-dict", NULL}};
    
	/* Get the list with no matching */
	SysPrintF(KPT_TS("KPTCMD_DICTIONARY_GETLIST: No matching\n"));
	result = KPTFwkRunCmd(KPTCMD_DICTIONARY_GETLIST, (intptr_t)&dictionaryList, (intptr_t)NULL);
	if (KPTRESULT_FAILED(result))
	{
		return result;
	}
	ShowDictList(&dictionaryList);
    
	/* Try again using language filtering */
	SysPrintF(KPT_TS("KPTCMD_DICTIONARY_GETLIST: eKPTLangFiltering\n"));
	result = KPTFwkRunCmd(KPTCMD_DICTIONARY_GETLIST, (intptr_t)&dictionaryList, (intptr_t)&langFilter);
	if (KPTRESULT_FAILED(result))
	{
		return result;
	}
	ShowDictList(&dictionaryList);
    
	/* Try again using language lookup */
	SysPrintF(KPT_TS("KPTCMD_DICTIONARY_GETLIST: eKPTLangLookup\n"));
	result = KPTFwkRunCmd(KPTCMD_DICTIONARY_GETLIST, (intptr_t)&dictionaryList, (intptr_t)&langLookup);
	if (KPTRESULT_FAILED(result))
	{
		return result;
	}
	ShowDictList(&dictionaryList);
    
	/* Only need to release the list once */
	result = KPTFwkReleaseAlloc(&dictionaryList);
	return result;
}


/*
 * Example function for KPTCMD_DICTIONARY_GETLANGLIST.
 * This example gets a list of all the languages for the loaded dictionaries.
 * The example code then repeats the process using language matching.
 *
 * SysPrintF represents a system printf function.
 */
KPTResultT
Example_KPTCMD_DICTIONARY_GETLANGLIST(void)
{
	KPTResultT result;
	KPTLangListAllocT languageList = {0};  /* Must initialise all AllocT structures. */
	KPTLanguageMatchingT langFilter = {eKPTLangFiltering, {"en-*-x-dict", NULL}};
	KPTLanguageMatchingT langLookup = {eKPTLangLookup, {"en-*-x-dict", NULL}};
    
	/* Get the list with no matching */
	SysPrintF(KPT_TS("KPTCMD_DICTIONARY_GETLANGLIST: No matching\n"));
	result = KPTFwkRunCmd(KPTCMD_DICTIONARY_GETLANGLIST, (intptr_t)&languageList, (intptr_t)NULL);
	if (KPTRESULT_FAILED(result))
	{
		return result;
	}
	ShowList(&languageList);
    
	/* Try again using language filtering */
	SysPrintF(KPT_TS("KPTCMD_DICTIONARY_GETLANGLIST: eKPTLangFiltering\n"));
	result = KPTFwkRunCmd(KPTCMD_DICTIONARY_GETLANGLIST, (intptr_t)&languageList, (intptr_t)&langFilter);
	if (KPTRESULT_FAILED(result))
	{
		return result;
	}
	ShowList(&languageList);
    
	/* Try again using language lookup */
	SysPrintF(KPT_TS("KPTCMD_DICTIONARY_GETLANGLIST: eKPTLangLookup\n"));
	result = KPTFwkRunCmd(KPTCMD_DICTIONARY_GETLANGLIST, (intptr_t)&languageList, (intptr_t)&langLookup);
	if (KPTRESULT_FAILED(result))
	{
		return result;
	}
	ShowList(&languageList);
    
	/* Only need to release the list once */
	result = KPTFwkReleaseAlloc(&languageList);
	return result;
}

/*
 * Local function to display the contents of a language list.
 */
static
void ShowList(KPTLangListAllocT* aList)
{
	if (0 == aList->count)
	{
		SysPrintF(KPT_TS("No languages\n"));
	}
	else
	{
		size_t index;
		SysPrintF(KPT_TS("Languages are:\n"));
		for (index = 0; index < aList->count; ++index)
		{
            SysPrintF(KPT_TS("language id: 0x%X; "),
                      aList->languages[index].id);
            SysPrintF("BCP47: %s\n", aList->languages[index].language.language);
		}
		SysPrintF(KPT_TS("Done.\n"));
	}
}


/*
 * Local function to display the contents of a dictionary list.
 */
static
void ShowDictList(KPTDictListAllocT* aList)
{
	if (0 == aList->count)
	{
		SysPrintF(KPT_TS("No dictionaries\n"));
	}
	else
	{
		size_t index;
		SysPrintF(KPT_TS("Name\tVersion\tId\tLoaded\tActive\tPriority\n"));
		for (index = 0; index < aList->count; ++index)
		{
			UniPrint(aList->dictInfo[index].dictDisplayName);
			SysPrintF(KPT_TS("\t%d\t0x%X\t%d\t%d\t%d\n"),
                      aList->dictInfo[index].dictVersion,
                      aList->dictState[index].componentId,
                      aList->dictState[index].dictLoaded,
                      aList->dictState[index].dictActive,
                      aList->dictState[index].dictPriority);
		}
		SysPrintF(KPT_TS("Done.\n"));
	}
}


#pragma mark - SUGGESTIONS ----------------------------------------------------------------------------------------------------------------

/*
 * Example function for KPTCMD_SUGGS_GETSUGGESTIONS.
 * SysPrintF prints a system string to the output.
 * UniPrint prints a unicode string to the output.
 */
KPTResultT
Example_KPTCMD_SUGGS_GETSUGGESTIONS(void)
{
	KPTResultT result;
	KPTSuggWordsRequestT suggRequest;
	KPTSuggWordsReplyT suggReply = {0};
	size_t sugLoop;
    
	//KPTUniCharT insert[] = {'T','h', 'e', ' '};
	KPTUniCharT insert[] = {'W','i', 'l', 'l', ' '};
    KPTInpMgrInsertStringT stringToInsert = {0};
    
	stringToInsert.insertString = insert;
	stringToInsert.length = sizeof(insert) / sizeof(KPTUniCharT);
	stringToInsert.attributes = eKPTInsertCapSentence;
	stringToInsert.ids = NULL;
	
	SysPrintF(KPT_TS("Preparing to get Suggestions\n"));
    
	SysPrintF(KPT_TS("Clearing Input Buffer\n"));
	result = KPTFwkRunCmd(KPTCMD_INPUTMGR_RESET, (intptr_t)NULL, 0);
	if (KPTRESULT_FAILED(result))
	{
		return result;
	}
    
	SysPrintF(KPT_TS("Populating Input Buffer\n"));
	result = KPTFwkRunCmd(KPTCMD_INPUTMGR_INSERTSTRING, (intptr_t)&stringToInsert, 0);
	if (KPTRESULT_FAILED(result))
	{
		return result;
	}
    
	suggRequest.suggestionTag = 0; /* No filtering */
    
	SysPrintF(KPT_TS("Requesting Suggestions\n"));
	result = KPTFwkRunCmd(KPTCMD_SUGGS_GETSUGGESTIONS, 
                          (intptr_t)&suggRequest,
                          (intptr_t)&suggReply);
    
    
	if (KPTRESULT_FAILED(result))
	{
		SysPrintF(KPT_TS("Failed to get Suggestions\n"));
		return result;
	}
    
	SysPrintF(KPT_TS("Returned Suggestions\n"));
	for (sugLoop = 0; sugLoop < suggReply.count; sugLoop++)
	{
		SysPrintF(KPT_TS("\t"));
		//UniPrint(suggReply.suggestions[sugLoop].suggestionString);
        //ATXStatusT UniCharToSysChar(KPTSysCharT* OutWord, size_t OutWordSize, KPTUniCharT* InWord, size_t len)
        char o[512];
        UniCharToSysChar(o, 511, const_cast<KPTUniCharT*>(suggReply.suggestions[sugLoop].suggestionString), suggReply.suggestions[sugLoop].suggestionLength);
        SysPrintF("%s", o);
		SysPrintF(KPT_TS("\n"));
	}
    
	return result;
}

#pragma mark - KEYMAP ----------------------------------------------------------------------------------------------------------------

/*
 * Example function for KPTCMD_KEYMAP_GETAVAILABLE.
 * This code gets a list of all disk based keymaps.
 *
 * SysPrintF represents a system printf function.
 */
KPTResultT
Example_KPTCMD_KEYMAP_GETAVAILABLE(void)
{
	KPTResultT result;
	KPTKeyMapIdListAllocT list = {0};  /* Must initialise all AllocT structures. */
	size_t index=0;
    
	result = KPTFwkRunCmd(KPTCMD_KEYMAP_GETAVAILABLE, (intptr_t)&list, 0);
	if (KPTRESULT_FAILED(result))
	{
		return result;
	}
    
	SysPrintF(KPT_TS("Available Keymaps:\n"));
	for (; index<list.count; ++index)
	{
		KPTKeyMapIdT* id = list.ids + index;
		printf("\tManufacturer=%s\n", id->manufacturer);
		printf("\tDevice=%s\n", id->device);
		printf("\tLanguage=%s, %s\n", id->language.language, id->language.script);
		SysPrintF(KPT_TS("\tLanguageId=%d\n"), (int)id->languageId);
		SysPrintF(KPT_TS("\tGroup=%d\n"), (int)id->group);
		SysPrintF(KPT_TS("~\n"));
	}
    
	result = KPTFwkReleaseAlloc(&list);
	return result;
}

/*
 * Example function for KPTCMD_KEYMAP_GETLAYOUT.
 * This code examines the contents of a key mapping layout.
 *
 * SysPrintF represents a system printf function.
 */
KPTResultT
Example_KPTCMD_KEYMAP_GETLAYOUT(void)
{
	KPTResultT result;
	KPTKeyMapLayoutListAllocT layoutList = {0};  /* Must initialise all AllocT structures. */
	KPTKeyMapIdT* keyMap = NULL;
    KPTKeyMapActiveIdListAllocT activeList = {0};
	size_t keyIndex;
	size_t itemIndex;
	KPTKeyMapLayoutT* layoutData = NULL;
    
	/* Get the active list */
	result = KPTFwkRunCmd(KPTCMD_KEYMAP_GETACTIVE, (intptr_t)&activeList, 0);
	if ( KPTRESULT_FAILED(result))
	{
		return result;
	}
    
    if (!activeList.ids || activeList.count == 0)
    {
        return KPTRESULT_ERROR(0, KPT_SC_ERROR);
    }
    
    /* get the first keymapid from the list */
    keyMap = activeList.ids[0];
    
	/* Get the layout for this keymap */
	result = KPTFwkRunCmd(KPTCMD_KEYMAP_GETLAYOUT, (intptr_t)keyMap, (intptr_t)&layoutList);
	
	if (KPTRESULT_FAILED(result) || layoutList.count == 0)
	{
		SysPrintF(KPT_TS("No Layout Information\n"));
        result = KPTFwkReleaseAlloc(&activeList);
		return result;
	}
    
	SysPrintF(KPT_TS("Active Keymap:\n"));
	printf("\tManufacturer=%s\n", keyMap->manufacturer);
	printf("\tDevice=%s\n", keyMap->device);
	printf("\tLanguage=%s, %s\n", keyMap->language.language, keyMap->language.script);
	SysPrintF(KPT_TS("\tLanguageId=%d\n"), (int)keyMap->languageId);
	SysPrintF(KPT_TS("\tGroup=%d\n"), (int)keyMap->group);
	SysPrintF(KPT_TS("\n"));
    
	layoutData = layoutList.layouts;
	SysPrintF(KPT_TS("Keys:\n"));
	for (keyIndex=0; keyIndex<layoutData->keyCount; ++keyIndex)
	{
		KPTKeyMapKeyT* keyData = layoutData->keys + keyIndex;
        
		SysPrintF(KPT_TS("\tID = %d\n"), keyData->id);
		SysPrintF(KPT_TS("\tVID = %d\n"), keyData->vId);
		SysPrintF(KPT_TS("\tNumber of Items = %u\n"), (unsigned)keyData->itemCount);
		SysPrintF(KPT_TS("\tItems:\n"));
		for (itemIndex=0; itemIndex<keyData->itemCount; ++itemIndex)
		{
			KPTKeyMapItemT* item = keyData->items + itemIndex;
			SysPrintF(KPT_TS("\t\tCode = 0x%0x\n"), (int)item->code);
			SysPrintF(KPT_TS("\t\tAttributes = 0x%0x\n"), (int)item->attributes);
		}
	}
    
    result = KPTFwkReleaseAlloc(&activeList);
	result = KPTFwkReleaseAlloc(&layoutList);
    
	return result;
}

KPTResultT
Example_KPTCMD_KEYMAP_QUERY(void)
{
	KPTResultT result;
	KPTKeyMapQueryT query;
	KPTKeyMapResultAllocT queryResult = {0};  /* Must initialise all AllocT structures. */
	size_t index = 0;
	
	/* This value and the query.layout field can be used to specify any loaded layout */
	query.useLayout = eKPTFalse;
	
	/* Find the keys with the '2' character */
	SysPrintF(KPT_TS("Searching for the character...\n"));
	query.useLayout = eKPTFalse;
	query.value = (uint32_t)'l';
	query.search = eKPTKeyMapSearchCode;
	result = KPTFwkRunCmd(KPTCMD_KEYMAP_QUERY, (intptr_t)&query, (intptr_t)&queryResult);
	if (KPTRESULT_FAILED(result))
	{
		return result;
	}
	for (index=0; index<queryResult.count; ++index)
	{
		const KPTKeyMapKeyT* key = queryResult.keys + index;
		SysPrintF(KPT_TS("character found on key %d\n"), (int)key->id);
		SysPrintF(KPT_TS("character found on pos %d,%d - %d,%d\n"), (int)key->position.x, key->position.y, key->position.width, key->position.height);
	}
}


#pragma mark - COMPONENTS ----------------------------------------------------------------------------------------------------------------

/*
 * Example function for KPTCMD_COMPONENT_GETAVAILABLE.
 * This example gets a list of all the installed components and prints
 * information about each one.
 *
 * SysPrintF represents a system printf function.
 */
KPTResultT
Example_KPTCMD_COMPONENT_GETAVAILABLE(void)
{
	KPTResultT result;
	size_t index;
	KPTComponentListAllocT available = {0};  /* Must initialise all AllocT structures. */
	const KPTComponentExtraDictionaryT* details = NULL;
    
	/* Get a list of the installed components */
	result = KPTFwkRunCmd(KPTCMD_COMPONENT_GETAVAILABLE, (intptr_t)&available, 0);
	if (KPTRESULT_FAILED(result))
	{
		return result;
	}
	
	/* Access details for component */
	for (index = 0; index<available.count; ++index)
	{
		/* Out put the details using a system printf function.*/
		SysPrintF(KPT_TS("component %d = "), (int)index);
		switch (available.components[index].componentType)
		{
            case KPT_COMPONENTTYPE_ADAPTXTENGINE:
                SysPrintF(KPT_TS("engine"));
                break;
                
            case KPT_COMPONENTTYPE_DICTIONARY:
                details = (const KPTComponentExtraDictionaryT*)available.components[index].extraDetails;
                if (details)
                {
                    SysPrintF(KPT_TS("dictionary %s"), details->dictInfo.dictFileName);
                }
                else
                {
                    SysPrintF(KPT_TS("dictionary with no details"));
                }
                break;
                
            default:
                SysPrintF(KPT_TS("other"));
                break;
		}
        
		if (available.components[index].isLoaded)
		{
			SysPrintF(KPT_TS(" Loaded\n"));
		}
		else
		{
			SysPrintF(KPT_TS(" Not Loaded\n"));
		}
	} /* for (index = 0; index<available.count; ++index) */
	
	result = KPTFwkReleaseAlloc(&available);
	return result;
}

#pragma mark - ERRORS ----------------------------------------------------------------------------------------------------------------

#include "kptapi_error.h"

#define EXAMPLE_ERRORSTRING_BUFFSIZE 30

/*
 * Example function for KPTCMD_ERROR_POPSTACK.
 * This example traverses the error stack.
 *
 * SysPrintF represents a system printf function.
 */
KPTResultT
Example_KPTCMD_ERROR_POPSTACK(void)
{
	KPTResultT result;
	KPTErrorPopStackT popStack = {0};
	KPTSysCharT errString[EXAMPLE_ERRORSTRING_BUFFSIZE] = { 0 };
    
	/* Get the stack */
	popStack.fieldMask = eKPTErrorReadCodesAndPartialString;
	popStack.errorDetails.errorString = errString;
	popStack.errorDetails.buffLen = EXAMPLE_ERRORSTRING_BUFFSIZE;
    
    SysPrintF("\n\nERROR STACK:\n");
    
	for (;;)
	{
		result = KPTFwkRunCmd(KPTCMD_ERROR_POPSTACK, (intptr_t)&popStack, 0);
		if (KPTRESULT_FAILED(result))
		{
			if (KPT_SC_SOURCEEXHAUSTED != KPTRESULT_GETSTATUS(result))
			{
				SysPrintF(KPT_TS("Error Getting Details\n"));
				return result;
			}
			break;
		}
        
		SysPrintF(KPT_TS("Stack Item\n"));
		SysPrintF(KPT_TS("\tResult\t0x%X\n"), popStack.errorDetails.resultCode);
		SysPrintF(KPT_TS("\tAdditional Code\t%d\n"), popStack.errorDetails.additionalErrorCode);
		SysPrintF(KPT_TS("\tText\t"));
		if (popStack.errorDetails.errorString)
		{
			SysPrintF("%s", popStack.errorDetails.errorString);
		}
		else
		{
			SysPrintF(KPT_TS("N/A"));
		}
		SysPrintF(KPT_TS("\n\n"));
	};
    
	return KPTFwkRunCmd(KPTCMD_ERROR_CLEARSTACK, 0, 0);
}

#pragma mark - INPUT MANAGER ------------------------------------------------------------------------------------------------------------

/* System identifiers for the keys ona a 12-key device */
#define KEYMAP_KEY1 1
#define KEYMAP_KEY2 2
#define KEYMAP_KEY3 3
#define KEYMAP_KEY4 4
#define KEYMAP_KEY5 5
#define KEYMAP_KEY6 6
#define KEYMAP_KEY7 7
#define KEYMAP_KEY8 8
#define KEYMAP_KEY9 9
#define KEYMAP_KEY10 10
#define KEYMAP_KEY11 11
#define KEYMAP_KEY12 12

void DisplayCurrentWord(KPTInpMgrCurrentWordT* aWord);

/*
 * Example function for KPTCMD_INPUTMGR_GETCURRWORD.
 * This example inserts some characters then gets the current word.
 *
 * SysPrintF represents a system printf function.
 */
KPTResultT
Example_KPTCMD_INPUTMGR_GETCURRWORD(void)
{
	KPTResultT result;
	KPTInpMgrInsertCharT insertChar = { 0 };
	KPTInpMgrCurrentWordT currentWord = { 0 };
    
	/* Insert a fixed character and make it upper case at the start of a sentence. */
	insertChar.attributes = eKPTInsertCapSentence|eKPTInsertMapKeyID;
	insertChar.id = KEYMAP_KEY4;
	insertChar.insertChar = 'h';
	result = KPTFwkRunCmd(KPTCMD_INPUTMGR_INSERTCHAR, (intptr_t)&insertChar, 0);
	if (KPTRESULT_FAILED(result))
	{
		return result;
	}
    
	/* Insert a fixed character and make it upper case. */
	insertChar.attributes = eKPTInsertCap|eKPTInsertMapKeyID;
	insertChar.id = KEYMAP_KEY6;
	insertChar.insertChar = 'o';
	result = KPTFwkRunCmd(KPTCMD_INPUTMGR_INSERTCHAR, (intptr_t)&insertChar, 0);
	if (KPTRESULT_FAILED(result))
	{
		return result;
	}
    
	/* Insert an ambiguous character. */
//	insertChar.attributes = eKPTInsertCapSentence|eKPTInsertMapKeyID|eKPTInsertAmbiguous;
//	insertChar.id = KEYMAP_KEY6; /* The character can be any Unicode value on key '6' */
//	insertChar.insertChar = 'm'; /* The default value for the character */
//	result = KPTFwkRunCmd(KPTCMD_INPUTMGR_INSERTCHAR, (intptr_t)&insertChar, 0);
//	if (KPTRESULT_FAILED(result))
//	{
//		return result;
//	}
    
	/* Insert an ambiguous character. */
//	insertChar.attributes = eKPTInsertCapSentence|eKPTInsertMapKeyID|eKPTInsertAmbiguous;
//	insertChar.id = KEYMAP_KEY3; /* The character can be any Unicode value on key '6' */
//	insertChar.insertChar = 0;   /* The command will pick a default value from the keymap */
//	result = KPTFwkRunCmd(KPTCMD_INPUTMGR_INSERTCHAR, (intptr_t)&insertChar, 0);
//	if (KPTRESULT_FAILED(result))
//	{
//		return result;
//	}
    
	/* Get the current word */
	currentWord.composition.fieldMask = eKPTCompositionMaskAll;
	currentWord.fieldMask = eKPTCurrentWordMaskAll;
	result = KPTFwkRunCmd(KPTCMD_INPUTMGR_GETCURRWORD, (intptr_t)&currentWord, 0);
	if (KPTRESULT_FAILED(result))
	{
		return result;
	}
    
	DisplayCurrentWord(&currentWord);

	return result;
}

/*
 * Function to display the contents of a current word structure.
 */
void DisplayCurrentWord(KPTInpMgrCurrentWordT* aWord)
{
	size_t index = 0;
    
	SysPrintF(KPT_TS("\nPrefix:\n"));
    
    char strx[512];
    UniCharToSysChar(strx, 512, aWord->fixedPrefix, 0);
    SysPrintF("%s", strx);
    
	SysPrintF(KPT_TS("\nComposition:\n"));
	for (index=0; index<aWord->composition.compStringLength; ++index)
	{
		SysPrintF(KPT_TS("%c "), aWord->composition.compString[index]);
		if (aWord->composition.fieldMask & eKPTCompositionMaskIds)
		{
			uint32_t id = aWord->composition.ids[index];
			SysPrintF(KPT_TS("id=%d "), id);
		}
        
		if (aWord->composition.fieldMask & eKPTCompositionMaskAttributes)
		{
			uint32_t attributes = aWord->composition.attributes[index];
			if (attributes & eKPTCharacterAmbiguous)
			{
				SysPrintF(KPT_TS("Ambiguous "));
			}
			else
			{
				SysPrintF(KPT_TS("Fixed "));
			}
            
			if (attributes & eKPTCharacterUpper)
			{
				SysPrintF(KPT_TS("Upper "));
			}
			else
			{
				SysPrintF(KPT_TS("Lower "));
			}
			SysPrintF(KPT_TS("\n"));
		}
	}
    
	if (0 == (aWord->composition.fieldMask & eKPTCompositionMaskOrigCompString))
	{
		SysPrintF(KPT_TS("\nOriginal Composition NOT Set.\n"));
	}
	else
	{
		SysPrintF(KPT_TS("\nOriginal Composition:\n"));
        char str[512];
        UniCharToSysChar(str, 512, aWord->composition.originalCompString, 0);
		SysPrintF("%s", str);
	}
    
	SysPrintF(KPT_TS("\nSuffix:\n"));
    char str[512];
    UniCharToSysChar(str, 512, aWord->fixedSuffix, 0);
    SysPrintF("%s", str);
	SysPrintF(KPT_TS("\nDone.\n"));
}
