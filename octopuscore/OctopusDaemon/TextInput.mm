//
//  TextInput.cpp
//  OctopusDaemon
//
//  Created by K3A on 5/19/12.
//  Copyright (c) 2012 K3A. All rights reserved.
//

#include "TextInput.h"

#include <stdio.h>
#include <stdarg.h>
#include <string>

#include "main.h"

#include "kptapi_framework.h"
#include "kptapi_dict.h"
#include "kptapi_lang.h"
#include "kptapi_suggs.h"
#include "kptapi_inputmgr.h"
#include "kptapi_keymap.h"
#include "kptapi_learn.h"
#include "kptapi_personal.h"
#include "kptapi_componenttypes.h"
#include "kptapi_output.h"

#include "Layouts.h"

static const char* OKPTComponent(KPTResultT r)
{
    switch (KPTRESULT_GETCOMPONENT(r))
    {
        case KPT_CC_FRAMEWORK:
            return "KPT_CC_FRAMEWORK";
        case KPT_CC_APIMGMT:
            return "KPT_CC_APIMGMT";
        case KPT_CC_CONFIG:
            return "KPT_CC_CONFIG";
        case KPT_CC_DICTIONARIES:
            return "KPT_CC_DICTIONARIES";
        case KPT_CC_ERRORMGR:
            return "KPT_CC_ERRORMGR";
        case KPT_CC_INPUTMGR:
            return "KPT_CC_INPUTMGR";
        case KPT_CC_KEYMAP:
            return "KPT_CC_KEYMAP";
        case KPT_CC_LEARNING:
            return "KPT_CC_LEARNING";
        case KPT_CC_COMPONENTS:
            return "KPT_CC_COMPONENTS";
        case KPT_CC_OUTPUT:
            return "KPT_CC_OUTPUT";
        case KPT_CC_PACKAGEMGMT:
            return "KPT_CC_PACKAGEMGMT";
        case KPT_CC_PERSONAL:
            return "KPT_CC_PERSONAL";
        case KPT_CC_SUGGESTIONS:
            return "KPT_CC_SUGGESTIONS";
        case KPT_CC_FILE:
            return "KPT_CC_FILE";
        case KPT_CC_LANGUAGE:
            return "KPT_CC_LANGUAGE";
        case KPT_CC_TEMPV2SUPPORT:
            return "KPT_CC_TEMPV2SUPPORT";
        default:
            return "UNKNOWN";
    }
}

static const char* OKPTError(KPTResultT r)
{
    switch((r) & 0xFFFF)
    {
        case KPT_SC_NOTFOUND:
            return "KPT_SC_NOTFOUND";
            
        case KPT_SC_INVALIDOPERATION:
            return "KPT_SC_INVALIDOPERATION";
            
        case KPT_SC_INVALIDARGUMENT:
            return "KPT_SC_INVALIDARGUMENT";
            
        case KPT_SC_OPENFAILED:
            return "KPT_SC_OPENFAILED";
            
        case KPT_SC_WRITEFAILED:
            return "KPT_SC_WRITEFAILED";
            
        case KPT_SC_READFAILED:
            return "KPT_SC_READFAILED";
            
        case KPT_SC_OUTOFMEMORY:
            return "KPT_SC_OUTOFMEMORY";
            
        case KPT_SC_INVALIDPOINTER:
            return "KPT_SC_INVALIDPOINTER";
            
        case KPT_SC_NOTIMPLEMENTED:
            return "KPT_SC_NOTIMPLEMENTED";
            
        case KPT_SC_LENGTHERROR:
            return "KPT_SC_LENGTHERROR";
            
        case KPT_SC_OUTOFRANGE:
            return "KPT_SC_OUTOFRANGE";
            
        case KPT_SC_BADSCHEMA:
            return "KPT_SC_BADSCHEMA";
            
        case KPT_SC_EXPIRED:
            return "KPT_SC_EXPIRED";
            
        case KPT_SC_COPYFAILED:
            return "KPT_SC_COPYFAILED";
            
        case KPT_SC_MOVEFAILED:
            return "KPT_SC_MOVEFAILED";
            
        case KPT_SC_DELETEFAILED:
            return "KPT_SC_DELETEFAILED";
            
        case KPT_SC_RENAMEFAILED:
            return "KPT_SC_RENAMEFAILED";
            
        case KPT_SC_BUFFERTOOSMALL:
            return "KPT_SC_BUFFERTOOSMALL";
            
        case KPT_SC_BUFFERFULL:
            return "KPT_SC_BUFFERFULL";
            
        case KPT_SC_OSERROR:
            return "KPT_SC_OSERROR";
            
        default:
            return "UNKNOWN";
            
    }
}

static
KPTResultT
KPT_CALLB
KPTCustomOutput(const KPTOutTextT* aText,
                     intptr_t aContext)
{
    const KPTSysCharT* label = (const KPTSysCharT*)aContext;
	
	const char* typet = "W";
	if (aText->categories & KPTCAT_DEBUG)
		typet = "D";
	else if (aText->categories & KPTCAT_INFORMATION)
		typet = "I";
	else if (aText->categories & KPTCAT_ERROR)
		typet = "E";
	
	OLog(3, "[%s] %s : %s%s", typet, label, aText->text, (aText->info & eKPTOutInfoNewLine)?"\n":"");
	
    return KPTRESULT_SUCCESS;
}

#define OAssert(cond, returnCode, format, ...) if (!( cond )){ OErr( format ,  ##__VA_ARGS__ ) ; returnCode ; }

#pragma mark - TEXT HELPERS -----------------------------------------------------------------------------------------------------------

/**
 * Converts From KPTSysCharT (8/16/32 bit) string to KPTUniCharT (16 bit) string.
 * Currently it is being assumed that even if KPTSysCharT is 32 bit all the characters 
 * are from Basic Multilingual Plane(BMP) and thus using the same array size as InWord for Outword
 * return ATXFailure 
 * -if the destination buffer is not large enough 
 * -if unable to convert from 32 bit to 16 bit (for 32 bit KPTSysCharT)
 * If len == 0, will copy the entire InWord String 
 * 
 * @param[in] OutWord		  Pointer to the converted KPTUnicharT string
 * @param[in] OutWordSize      length of the destination buffer
 * @param[in] InWord			  input string
 * @param[in] len			  length of the input string, if len == 0, convertes the entire null terminated InWord string
 * 
 * @return    num of charactes converted or 0 on error or no input
 */

unsigned SysCharToUniChar(KPTUniCharT* OutWord, size_t OutWordSize, const KPTSysCharT* InWord, size_t len)
{
	if (!OutWord || !InWord)
        return 0;
    if (len == 0)
        KPTStrLenS(InWord,&len);
    if (OutWordSize <= len)
    {
        return 0;
    }
	
#if (KPT_TSYSCHAR_BIT == 8)
	KPTResultT result;
    const KPTUtf8CharT *pStart8 = (KPTUtf8CharT *)&InWord[0];
    const KPTUtf8CharT *pEnd8 = (KPTUtf8CharT *)&InWord[len];
    KPTUtf16CharT *pStart16 = (KPTUtf16CharT *)&OutWord[0];
    KPTUtf16CharT *pEnd16 = (KPTUtf16CharT *)&OutWord[len];
    
    result = KPTUnicodeConvertUTF8toUTF16(&pStart8, 
								 pEnd8, 
								 &pStart16, 
								 pEnd16, 
								 eKPTTrue);
	
	if (!KPTRESULT_SUCCEEDED(result))
		return 0;
	else
	{
        int numconverted = (int)(pStart16 - (KPTUtf16CharT *)&OutWord[0]);
        OutWord[numconverted] = 0x0000;
        return numconverted;
	}
	
#elif (KPT_TSYSCHAR_BIT == 16)
    unsigned int k=0;
    for (k = 0; k < len; k++)
        OutWord[k] = KPTUniCharT(InWord[k]);
    OutWord[k] = 0x0000;
    return k;
#elif (KPT_TSYSCHAR_BIT == 32)
    
	KPTResultT result;
    const KPTUtf32CharT *pStart32 = (KPTUtf32CharT *)&InWord[0];
    const KPTUtf32CharT *pEnd32 = (KPTUtf32CharT *)&InWord[len];
    KPTUtf16CharT *pStart16 = (KPTUtf16CharT *)&OutWord[0];
    KPTUtf16CharT *pEnd16 = (KPTUtf16CharT *)&OutWord[len];
    
    result = KPTUnicodeConvertUTF32toUTF16(&pStart32, 
                                           pEnd32, 
                                           &pStart16, 
                                           pEnd16, 
                                           eKPTTrue);
	if (!KPTRESULT_SUCCEEDED(result))
		return 0;
	else
	{
        int numconverted = (int)(pStart16 - (KPTUtf16CharT *)&OutWord[0]);
        OutWord[numconverted] = 0x0000;
        return numconverted;
	}
#endif
} 

/**
 * Converts From KPTUniCharT (16 bit) string to KPTSysCharT (8/16/32 bit) string.
 * If (KPTSYSCHAR_BIT == 16 or 32) we just do a copy character by character
 * if (KPTSYSCHAR_BIT == 8) we convert from utf16 to utf8, outwordsize should be atleast double the len value
 * return ATXFailure 
 * -if the destination buffer is not large enough 
 * -if unable to convert from 16 bit to 8 bit (for 8 bit KPTSysCharT)
 * If len == 0, will copy the entire InWord String 
 * 
 * @param[in] OutWord		  Pointer to the converted KPTSysCharT string
 * @param[in] OutWordSize      length of the destination buffer
 * @param[in] InWord			  input string
 * @param[in] len			  length of the input string, if len == 0, convertes the entire null terminated InWord string
 * 
 * @return    num of charactes converted or 0 on error or no input
 */

unsigned UniCharToSysChar(KPTSysCharT* OutWord, size_t OutWordSize, const KPTUniCharT* InWord, size_t len)
{
	if (!OutWord || !InWord)
        return 0;
    if (len == 0)
        KPTStrLenU(InWord,&len);
#if ((KPT_TSYSCHAR_BIT == 16) || (KPT_TSYSCHAR_BIT == 32))
    unsigned int k=0;
    if (OutWordSize <= len)
    {
        return 0;
    }
    for (k = 0; k < len; k++)
        OutWord[k] = KPTSysCharT(InWord[k]);
    OutWord[k] = 0x0000;  
    return k;
#elif (KPT_TSYSCHAR_BIT == 8)  
    size_t req_len = 2 * len + 1;
    if (OutWordSize <= req_len)
    {
        return 0;
    }
	const KPTUtf16CharT *pStart16 = (KPTUtf16CharT *)&InWord[0];
	const KPTUtf16CharT *pEnd16 = (KPTUtf16CharT *)&InWord[len];
    
    KPTUtf8CharT *pStart8 = (KPTUtf8CharT *)&OutWord[0];
	KPTUtf8CharT *pEnd8 = (KPTUtf8CharT *)&OutWord[OutWordSize];
    
	KPTResultT result;
    
    result = KPTUnicodeConvertUTF16toUTF8(&pStart16, 
                                          pEnd16, 
                                          &pStart8, 
                                          pEnd8, 
                                          eKPTTrue);
	if (!KPTRESULT_SUCCEEDED(result))
		return 0;
	else
	{
        int numconverted = (int)(pStart8 - (KPTUtf8CharT *)&OutWord[0]);
        OutWord[numconverted] = 0x0000;
        return numconverted;
	}
#endif
}

#pragma mark - INPUT SYSTEM -----------------------------------------------------------------------------------------------------------

OTextInputSystem::OTextInputSystem(const char* profilePath)
{
    mInited = false;
    
    KPTInitT initItems[] =
	{
		{ KPT_CC_FRAMEWORK, 0, KPT_INIT_FRAMEWORK_LOCKINGENABLED, (intptr_t)eKPTTrue},
		{ KPT_CC_FRAMEWORK, 0, KPT_INIT_FRAMEWORK_BASEPATH,       (intptr_t)profilePath},
	};
    
	KPTCreateParamsT createParams = { 0 };
	createParams.initItems = initItems;
	createParams.initItemCount = sizeof(initItems) / sizeof(*initItems);
    
	//initItems[1].value = (intptr_t)GetPathToFrameworkFiles();
    
	// Create framework
	KPTResultT result = KPTFwkCreate(&createParams);
    OAssert(result == KPT_SC_SUCCESS, return, "Failed to initialize KTP! %s:%s", OKPTComponent(result), OKPTError(result));
    
	// Set logging
#ifdef DEBUG
	KPTOutAddCustomT insert;
    KPTOutCustomIdT cid;
	
    insert.callback = KPTCustomOutput;
    insert.context = (intptr_t)KPT_TS("");
	
	/* Add the callback */
    result = KPTFwkRunCmd(KPTCMD_OUTPUT_ADDCUSTOMOUTPUT,
						  (intptr_t)&insert,
						  (intptr_t)&cid);
	
    if (KPTRESULT_FAILED(result))
        OErr("Failed to add custom output callback!");
	
    /* Enable the output category */
    result = KPTFwkRunCmd(KPTCMD_OUTPUT_SETCATEGORIES,
						  (intptr_t)KPTCAT_ALL,//KPTCAT_INFORMATION,
						  0);
	
    if (KPTRESULT_FAILED(result))
		OErr("Failed to set categories of custom output callback!");
	
	KPTOutEnableBuiltInT output;
	
	/* Use the console */
	output.context = 0;
	output.type = eKPTOutBuiltInDefault;
	
	/* Enable the output */
	result = KPTFwkRunCmd(KPTCMD_OUTPUT_ENABLEOUTPUT,
						  (intptr_t)&output,
						  (intptr_t)0);
	
	if (KPTRESULT_FAILED(result))
		OErr("Failed to enable output!");
#endif
	
    // Set default layout
    SetKeyLayout(KL_iphone_en_US);
    
    // merge CRLF characters into one character
    KPTInpMgrConfigT newConfig = {0};
    newConfig.fieldMask = eKPTInpMgrConfigMaskMergeCRLF;
	newConfig.mergeCRLFOn = eKPTTrue;
	result = KPTFwkRunCmd(KPTCMD_INPUTMGR_SETCONFIG, (intptr_t)&newConfig, 0);
	OAssert(result == KPT_SC_SUCCESS, return, "Failed to set inpmgr congig! %s:%s", OKPTComponent(result), OKPTError(result));
    
    //Clears Input Buffer, in other words language node are reset
	InputClear();
    
    //DictClear();
    
    // Get max user dict words
    unsigned maxW = 0;
    UserDictGetMaxWords(maxW);
    
    // limit too low -> increase
    if (maxW < 3000) UserDictSetMaxWords(3000);
    
	unsigned numW=0;
	UserDictGetNumWords(numW);
    OLog(3, "Num words in personal dict: %u", numW);
}

bool OTextInputSystem::UserDictGetMaxWords(unsigned& numWords)
{
    KPTPDConfigT dictConf;
	if (KPTRESULT_FAILED( KPTFwkRunCmd(KPTCMD_PERSONAL_GETCONFIG, (intptr_t)&dictConf, (intptr_t)NULL) ))
    {
        numWords = 0;
        return false;
    }
    
    numWords = dictConf.maxEntries;
    return true;
}
bool OTextInputSystem::UserDictSetMaxWords(unsigned numWords)
{
    KPTPDConfigT dictConf;
    dictConf.maxEntries = numWords;
    return KPTRESULT_SUCCEEDED( KPTFwkRunCmd(KPTCMD_PERSONAL_SETCONFIG, (intptr_t)&dictConf, (intptr_t)NULL) );
}

OTextInputSystem::~OTextInputSystem()
{
    OLog(0, "Destroying KPT");
    
    // release the framework
    KPTResultT result = KPTFwkDestroy();
    OAssert(result == KPT_SC_SUCCESS, return, "Faled to destroy KPT!");
}

bool OTextInputSystem::SetKeyLayout(eKeyLayout kl)
{
    const KPTKeyMapLayoutT* layout = NULL;
    
    switch (kl) {
        case KL_iphone_en_US:
            layout = &s_layout_iphone_en_US;
            break;
            
        default:
            OErr("Unknown keyboard layout #%d", kl);
            break;
    }
    
    if (!layout) return false;
    
    KPTKeyMapOpenT open;
    KPTResultT result; 
    
    open.createIfRequired = eKPTTrue;
    result = KPTFwkRunCmd(KPTCMD_KEYMAP_OPEN, (intptr_t)&(layout->id), (intptr_t)&open);
	switch (KPTRESULT_GETSTATUS(result))
	{
        case KPT_SC_SUCCESS:
            if (open.created)
                OLog(0, "Key map has been created.");
            else
                OLog(0, "Key map has been loaded.");
            break;
            
        case KPT_SC_ALREADYINITIALISED:
            OLog(0, "Key map already open.");
            break;
            
        default:
            OErr("Failed to open key map! %s:%s", OKPTComponent(result), OKPTError(result));
            break;
	}
    
	// Set or replace the data for the key mapping
	result = KPTFwkRunCmd(KPTCMD_KEYMAP_SETLAYOUT, (intptr_t)layout, 0);
	if (KPTRESULT_FAILED(result))
    {
        OErr("Failed to set key map! %s:%s", OKPTComponent(result), OKPTError(result));
		return false;
	}
	
	// Set the keymap as active 
	KPTKeyMapActiveIdListT keymapList;
	keymapList.ids = (KPTKeyMapIdT*)&(layout->id);
	keymapList.count = 1;
	result = KPTFwkRunCmd(KPTCMD_KEYMAP_SETACTIVE, (intptr_t)&keymapList, 0);
	if (KPTRESULT_FAILED(result))
	{
		OErr("Failed to activate key map! %s:%s", OKPTComponent(result), OKPTError(result));
		return false;
	}
    
    return true;
}

bool OTextInputSystem::LearnBuffer(const char* utf8Buff)
{
    if (!utf8Buff || !*utf8Buff) return false;
    
    KPTUniCharT* uniBuff; 
    unsigned uniNum = SysToUni(uniBuff, utf8Buff);
    
    KPTResultT result;
	KPTLearnBufferT learn;
    
	learn.buffer = uniBuff;
	learn.bufferSize = uniNum;
	learn.language = 0;
	learn.stage = eKPTLearnSingle;     /* There is only one call */
	learn.progress = NULL;             /* No progress handler (See See Example_KPTCMD_LEARNFILE_RUN) */
	learn.progressContext = 0;         /* No progress context */
    
	/* Learn the buffer */
	result = KPTFwkRunCmd(KPTCMD_LEARN_BUFFER, (intptr_t)&learn, 0);
	if (KPTRESULT_FAILED(result))
	{
        OErr("Failed to learn buffer! %s:%s", OKPTComponent(result), OKPTError(result));
        free(uniBuff);
		return result;
	}
    
    free(uniBuff);
    return true;
}

bool OTextInputSystem::EnableAutoLearning(bool enable)
{
    uint32_t options = enable?eKPTLearnEnabled:0;
    uint32_t oldOptions = 0;
	KPTResultT result;
    
    result = KPTFwkRunCmd(KPTCMD_LEARN_SETOPTIONS, (intptr_t)options, (intptr_t)&oldOptions);
	if (KPTRESULT_FAILED(result))
	{
        OErr("Failed to set autolearn options! %s:%s", OKPTComponent(result), OKPTError(result));
		return result;
	}
    
    return true;
}

bool OTextInputSystem::EnableAutoCorrection(bool enable, bool errorCorrections, bool spaceCorrections)
{
    KPTResultT result;
    KPTSuggConfigT suggConfig = {0};
    
	// have to enable error correction
	suggConfig.errorCorrectionOn = enable?eKPTTrue:eKPTFalse;
	suggConfig.fieldMask = eKPTSuggsConfigErrorCorrection;
	result = KPTFwkRunCmd(KPTCMD_SUGGS_SETCONFIG, (intptr_t)&suggConfig, (intptr_t)0);
    if (KPTRESULT_FAILED(result)) return false;
    
    // set autocorrection types
    /*KPTInpMgrConfigT inpConfig = {0};
    inpConfig.errorCorrectionSuggestionsOn = errorCorrections?eKPTTrue:eKPTFalse;
	inpConfig.spaceCorrectionSuggestionsOn = spaceCorrections?eKPTTrue:eKPTFalse;
	inpConfig.fieldMask = eKPTInpMgrConfigMaskErrorCorrect | eKPTInpMgrConfigMaskSpaceCorrect;
	result = KPTFwkRunCmd(KPTCMD_INPUTMGR_SETCONFIG, (intptr_t)&inpConfig, (intptr_t)0);
    if (KPTRESULT_FAILED(result)) return false;*/
    
    return true;
}

bool OTextInputSystem::IsAutoLearningEnabled()
{
    uint32_t options = 0;
	KPTResultT result;
    
	/* Get the existing options */
	result = KPTFwkRunCmd(KPTCMD_LEARN_GETOPTIONS, (intptr_t)&options, 0);
	if (KPTRESULT_FAILED(result))
	{
        OErr("Failed to get autolearn options! %s:%s", OKPTComponent(result), OKPTError(result));
		return false;
	}
    return options & eKPTLearnEnabled;
}

#include "kptapi_error.h"

#define EXAMPLE_ERRORSTRING_BUFFSIZE 30
#define SysPrintF(x, ...) OLog(1, x, ##__VA_ARGS__)
KPTResultT
Example_KPTCMD_ERROR_POPSTACK2(void)
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
bool OTextInputSystem::UserDictGetWordForID(unsigned idx, char *&word) {
	KPTUniCharT* uniWord;
    //SysToUni(uniWord, word);
    
    KPTPDWordIdOperationT query;
    query.word = NULL;//(KPTUniCharT*)calloc(257, sizeof(KPTUniCharT));//uniWord;
	query.id = idx;//*/
	//KPTPDWordReplyT query;
    //query.
	
	KPTResultT result = KPTFwkRunCmd(KPTCMD_PERSONAL_GETWORDFORID, (intptr_t)&query, (intptr_t)&uniWord);
    //free(uniWord);
    if (KPTRESULT_SUCCEEDED(result) /*&& query.word != NULL*/) {
		UniToSys(word,uniWord);
		
		return true;
	} else
	Example_KPTCMD_ERROR_POPSTACK2();
    return false;
}

bool OTextInputSystem::UserDictClear()
{
    //Clears User Dictionary
	KPTResultT result = KPTFwkRunCmd(KPTCMD_PERSONAL_REMOVEALLWORDS, 0, 0);
	OAssert(result == KPT_SC_SUCCESS, return false, "Failed to remove all words from personal dict!");
    
    return true;
}

bool OTextInputSystem::UserDictGetNumWords(unsigned& numWords)
{
    KPTPDOpenViewRequestT openViewRequest;
	KPTPDOpenViewReplyT openViewReply = {0};
    
    openViewRequest.viewOption = eKPTPDViewAlphaAscending;
	openViewRequest.state = eKPTPDViewFilterNone;
	openViewRequest.query = NULL;
    
	KPTResultT result = KPTFwkRunCmd(KPTCMD_PERSONAL_OPENVIEW, (intptr_t)&openViewRequest, (intptr_t)&openViewReply);
	OAssert(result == KPT_SC_SUCCESS, return false, "Failed to get number of words in the personal dict!");
    
    numWords = openViewReply.numWordsFound;
    
    return true;
}

bool OTextInputSystem::UserDictWordExists(const char* word)
{
    KPTUniCharT* uniWord;
    SysToUni(uniWord, word);
    
    KPTPDWordIdOperationT query;
    query.word = uniWord;
	query.id = 0;
    
	KPTResultT result = KPTFwkRunCmd(KPTCMD_PERSONAL_GETIDFORWORD, (intptr_t)&query, 0);
    free(uniWord);
    
    return KPTRESULT_SUCCEEDED(result) && query.id != 0;
}

#include <mach/vm_map.h>

bool OTextInputSystem::DictGetList(sDictionaryArray* outDicts, unsigned* outNumDicts)
{
    KPTDictListAllocT aList = {0};
    
	if (KPTRESULT_FAILED( KPTFwkRunCmd(KPTCMD_DICTIONARY_GETLIST, (intptr_t)&aList, (intptr_t)NULL) ))
	{
        *outDicts = NULL;
        *outNumDicts = 0;
        return false;
    }
    
    *outNumDicts = aList.count;
    if (!aList.count) return true; // no dicts
    
    //*outDicts = (sDictionary*)malloc(sizeof(sDictionary)*aList.count);
    if (KERN_SUCCESS != vm_allocate(mach_task_self(), (vm_address_t*)outDicts, sizeof(sDictionary)*aList.count, true))
    {
        *outDicts = NULL;
        *outNumDicts = 0;
        return false;
    }
    
    for (unsigned index = 0; index < aList.count; ++index)
    {
        sDictionary& dict = (*outDicts)[index];
        
        char* str; UniToSys(str, aList.dictInfo[index].dictDisplayName);
        strcpy(dict.name, str);
        free(str);
		
		if (aList.dictInfo[index].dictLanguage.language.language)
			strncpy(dict.language, aList.dictInfo[index].dictLanguage.language.language, 1023);
		else if (aList.dictInfo[index].dictFileName)
		{
			OLog(3, "Unknown language string for %s", aList.dictInfo[index].dictFileName);
			strncpy(dict.language, aList.dictInfo[index].dictFileName, 1023);
		}
		else 
			sprintf(dict.language, "unkn%d", aList.dictState[index].componentId);
		
		dict.language[1023]=0;
        dict.version = aList.dictInfo[index].dictVersion;
        dict.componentId = aList.dictState[index].componentId;
        dict.loaded = aList.dictState[index].dictLoaded == eKPTTrue;
        dict.active = aList.dictState[index].dictActive == eKPTTrue;
        dict.priority = aList.dictState[index].dictPriority;
    }
    
    if (KPTRESULT_FAILED( KPTFwkReleaseAlloc(&aList) ))
    {
        vm_deallocate(mach_task_self(), (vm_address_t)*outDicts, sizeof(sDictionary)*aList.count);
        *outDicts = NULL;
        *outNumDicts = 0;
        return false;
    }
    
    return true;
}

bool OTextInputSystem::DictEnable(unsigned dictId, bool enable)
{
	KPTDictStateT dictState = {0};
	
	dictState.componentId = dictId;
	dictState.dictActive = enable?eKPTTrue:eKPTFalse;
	dictState.fieldMask  = eKPTDictStateActive;
	
	return KPTRESULT_SUCCEEDED( KPTFwkRunCmd(KPTCMD_DICTIONARY_SETSTATES, (intptr_t)&dictState, 1) );
}

bool OTextInputSystem::InputClear()
{
    KPTResultT result = KPTFwkRunCmd(KPTCMD_INPUTMGR_RESET, (intptr_t)NULL, 0);
	OAssert(result == KPT_SC_SUCCESS, return false, "Failed to clear input!");
    return true;
}

bool OTextInputSystem::InputRemove(int beforeCursor, int afterCursor)
{
    KPTInpMgrRemoveCharsT toRemove;
    
	toRemove.numBeforeCursor = beforeCursor;
	toRemove.numAfterCursor = afterCursor;
    
	return KPTRESULT_SUCCEEDED( KPTFwkRunCmd(KPTCMD_INPUTMGR_REMOVE, (intptr_t)&toRemove, 0) );
}

bool OTextInputSystem::InputReplace(int index, int len, const char *replacement)
{
    KPTInpMgrReplaceContentsT replaceContents;
    
    KPTUniCharT* uniReplace;
    size_t uniReplaceLen = SysToUni(uniReplace, replacement);
    
	replaceContents.firstCharIndex = index;
	replaceContents.lastCharIndex = index+len-1;
	replaceContents.replacementText = uniReplace;
	replaceContents.replacementLength = uniReplaceLen;
	KPTResultT result = KPTFwkRunCmd(KPTCMD_INPUTMGR_REPLACECONTENTS, (intptr_t)&replaceContents, 0);
	
    free(uniReplace);
    
    return KPTRESULT_SUCCEEDED(result);
}

bool OTextInputSystem::InputCursorMove(eSeekOrigin origin, int value)
{
    intptr_t kptorig = eKPTSeekRelative;
    if (origin == SO_START)
        kptorig = eKPTSeekStart;
    else if (origin == SO_END)
        kptorig = eKPTSeekEnd;
    
    KPTResultT result = KPTFwkRunCmd(KPTCMD_INPUTMGR_MOVECURSOR, kptorig, value);
    return result == KPT_SC_SUCCESS;
}

bool OTextInputSystem::InputCursorGetPosition(int &outPosition, int &outLen)
{
    KPTInpMgrCursorDetailsT aDetails;
    
    KPTResultT result = KPTFwkRunCmd(KPTCMD_INPUTMGR_GETCURSOR, (intptr_t)&aDetails, 0);
	if (KPTRESULT_SUCCEEDED(result))
	{
        outPosition = aDetails.cursorPos;
        outLen = aDetails.totalLength;
		return true;
	}
    return false;
}

bool OTextInputSystem::InputInsertChar(const char ch, eCapitalizationMode cm, bool disableAutoLearn)
{
    KPTInpMgrInsertCharT insert;
    insert.attributes = 0;
	insert.id = 0;
    
    if (cm == CM_SENTENCE)
        insert.attributes |= eKPTInsertCapSentence;
    else if (cm == CM_ALL)
        insert.attributes |= eKPTInsertCap;
    if (disableAutoLearn)
        insert.attributes |= eKPTInsertNoLearning;
    
    KPTUniCharT uniChars[3];
    SysCharToUniChar(uniChars, 3, &ch, 1);
    
    insert.insertChar = uniChars[0];
    
    /* Call pre-insert to check for possible corrections */
    
  /*  KPTInpMgrPreInsertCharRequestT request = {0};
	KPTInpMgrPreInsertCharReplyT reply = {0};
    
    request.insertChars = &insert;
    request.insertCharsCount = 1;
    result = KPTFwkRunCmd(KPTCMD_INPUTMGR_PREINSERTCHAR, (intptr_t)&request, (intptr_t)&reply);
    
    if (KPTRESULT_SUCCEEDED(result))
    {
        // Check the suggestions
        for (index = 0; index<reply.count; ++index)
        {
            const KPTSuggEntryT* entry = &(reply.suggestions[index]);
            switch (entry->suggestionType)
            {
                case KPTSUGGSTYPE_SPACECORRECTION:
                    printf("%d: KPTSUGGSTYPE_SPACECORRECTION: \""), index);
                    UniPrint(entry->suggestionString);
                    printf("\"\n");
                    break;
                case KPTSUGGSTYPE_ERRORCORRECTION:
                    printf("%d: KPTSUGGSTYPE_ERRORCORRECTION \"", index);
                    UniPrint(entry->suggestionString);
                    printf("\"\n");
                    break;
                default:
                    printf("%d: %d\n", index, entry->suggestionType);
                    break;
            }
        }
    }*/
    
    return KPTRESULT_SUCCEEDED( KPTFwkRunCmd(KPTCMD_INPUTMGR_INSERTCHAR, (intptr_t)&insert, 0) );
}

bool OTextInputSystem::InputInsertString(const char* str, eCapitalizationMode cm, bool disableAutoLearn)
{	
    KPTUniCharT* uniInp; 
    size_t uniInpLen = SysToUni(uniInp, str);
    
    KPTInpMgrInsertStringT stringToInsert = {0};
    stringToInsert.insertString = uniInp;
	stringToInsert.length = uniInpLen;
	stringToInsert.attributes = 0;
	stringToInsert.ids = NULL;
    
    if (cm == CM_SENTENCE)
        stringToInsert.attributes |= eKPTInsertCapSentence;
    else if (cm == CM_ALL)
        stringToInsert.attributes |= eKPTInsertCap;
    if (disableAutoLearn)
        stringToInsert.attributes |= eKPTInsertNoLearning;
    
    KPTResultT result = KPTFwkRunCmd(KPTCMD_INPUTMGR_INSERTSTRING, (intptr_t)&stringToInsert, 0);
    
    free(uniInp);
    
    return KPTRESULT_SUCCEEDED( result );
}

bool OTextInputSystem::InputInsertSugg(unsigned set, unsigned ident, bool appendSpace)
{
    KPTInpMgrInsertSuggRequestT suggRequest = {0};
    KPTInpMgrInsertSuggReplyAllocT suggReply = {0};
    
    suggRequest.appendSpace = appendSpace?eKPTTrue:eKPTFalse;
    suggRequest.suggestionId = ident;
    suggRequest.suggestionSet = set;
    
    KPTResultT result = KPTFwkRunCmd(KPTCMD_INPUTMGR_INSERTSUGG, (intptr_t)&suggRequest, (intptr_t)&suggReply);
    
    KPTFwkReleaseAlloc(&suggReply);
    
    return KPTRESULT_SUCCEEDED(result);
}

bool OTextInputSystem::InputGetCurrWord(oword_t &outWord)
{
    KPTResultT result;
	KPTInpMgrCurrentWordT aWord = { 0 };
    
    aWord.composition.fieldMask = eKPTCompositionMaskAll;
	aWord.fieldMask = eKPTCurrentWordMaskAll;
    
	result = KPTFwkRunCmd(KPTCMD_INPUTMGR_GETCURRWORD, (intptr_t)&aWord, 0);
	if (KPTRESULT_FAILED(result))
		return false;
    
    char* prefix;
    UniToSys(prefix, aWord.fixedPrefix);
    
	if (prefix)
		strncpy(outWord, prefix, O_MAX_WORD_LENGTH);
	else 
		outWord[0]=0;
	
    outWord[O_MAX_WORD_LENGTH] = 0; // terminate 
    
    /*printf("Composition:\n");
	for (int index=0; index<aWord.composition.compStringLength; ++index)
	{
		printf("%c ", aWord.composition.compString[index]);
		if (aWord.composition.fieldMask & eKPTCompositionMaskIds)
		{
			uint32_t id = aWord.composition.ids[index];
			printf("id=%d ", id);
		}
        
		if (aWord.composition.fieldMask & eKPTCompositionMaskAttributes)
		{
			uint32_t attributes = aWord.composition.attributes[index];
			if (attributes & eKPTCharacterAmbiguous)
				printf("Ambiguous ");
			else
				printf("Fixed ");
            
			if (attributes & eKPTCharacterUpper)
				printf("Upper ");
			else
				printf("Lower ");
			printf("\n");
		}
	}
    
    if ((aWord.composition.fieldMask & eKPTCompositionMaskOrigCompString))
    {
        char* origComposition;
        size_t origCompositionLen = UniToSys(origComposition, aWord.composition.originalCompString);
        printf("orig comp '%s'\n", origComposition);
    }
    
    char* suffix;
    size_t suffixLen = UniToSys(suffix, aWord.fixedSuffix);
    
    printf("prefix '%s' suffix '%s'\n", prefix, suffix);*/
    
    return true;
}

bool OTextInputSystem::InputLearn(eInputLearnOptions lo)
{
	KPTLearnContentsT learn;
    
    learn.stage = eKPTLearnSingle;    /* There is only one call */
    
	learn.range = eKPTLearnAll;
    if (lo == IL_CURR_WORD_GROUP)
        learn.range = eKPTLearnWordGroup;
    else if (lo == IL_PREV_WORD_GROUP)
        learn.range = eKPTLearnPreviousWordGroup;
    
	learn.progress = NULL;             /* No progress handler (See See Example_KPTCMD_LEARNFILE_RUN) */
	learn.progressContext = 0;        /* No progress context */
    
	return KPTRESULT_SUCCEEDED( KPTFwkRunCmd(KPTCMD_LEARN_CONTENTS, (intptr_t)&learn, 0) );
}

bool OTextInputSystem::SuggConfigure(unsigned maxSuggestions, unsigned suggestionThreshold, bool proximitySuggestion, bool errorCorrection, bool completion)
{
	KPTSuggConfigT config = {0};
	KPTSuggConfigT oldConfig = {0};
    
    if (maxSuggestions>O_MAX_SUGGESTIONS) maxSuggestions = O_MAX_SUGGESTIONS;
    
    config.fieldMask = eKPTSuggsConfigMaxSuggestions | eKPTSuggsConfigProximitySuggestions | eKPTSuggsConfigErrorCorrection | eKPTSuggsConfigCompletion | eKPTSuggsConfigThreshold;
    config.errorCorrectionOn = errorCorrection?eKPTTrue:eKPTFalse;
    config.proximitySuggestionOn = proximitySuggestion?eKPTTrue:eKPTFalse;
    config.completionOn = completion?eKPTTrue:eKPTFalse;
    config.maxNumSuggestions = maxSuggestions;
	config.suggestionThreshold = suggestionThreshold;
    
	return KPTRESULT_SUCCEEDED( KPTFwkRunCmd(KPTCMD_SUGGS_SETCONFIG, (intptr_t)&config, (intptr_t)&oldConfig));
}
bool OTextInputSystem::SuggConfigureCaps(bool capKnownWords, bool capSentence, bool capUser, bool capNext)
{
	KPTSuggConfigT config = {0};
	KPTSuggConfigT oldConfig = {0};
    
    config.fieldMask = eKPTSuggsConfigUseStoredCaps | eKPTSuggsConfigSentenceCase | eKPTSuggsConfigUserCaps | eKPTSuggsConfigCapNext;
    config.useStoredCaps = capKnownWords?eKPTTrue:eKPTFalse;
    config.useSentenceCase = capSentence?eKPTTrue:eKPTFalse;
    config.honourUserCaps = capUser?eKPTTrue:eKPTFalse;
    config.capNext = capNext?eKPTTrue:eKPTFalse;
    
	return KPTRESULT_SUCCEEDED( KPTFwkRunCmd(KPTCMD_SUGGS_SETCONFIG, (intptr_t)&config, (intptr_t)&oldConfig));
}

bool OTextInputSystem::SuggGetSuggestions(sSuggestions& outSuggs)
{
    KPTResultT result;
    KPTSuggWordsRequestT request = {0};
    KPTSuggWordsReplyT reply = {0};
    
    result = KPTFwkRunCmd(KPTCMD_SUGGS_GETSUGGESTIONS, (intptr_t)&request, (intptr_t)&reply);
    if (!KPTRESULT_SUCCEEDED(result))
    {
        outSuggs.count = 0;
        return false;
    }
    
    outSuggs.set = reply.suggestionSet;
    outSuggs.count = reply.count;
    if (outSuggs.count > O_MAX_SUGGESTIONS) outSuggs.count = O_MAX_SUGGESTIONS;
    
    for (register int i=0; i<outSuggs.count; i++)
    {
        const KPTSuggEntryT& s = reply.suggestions[i];
        
        char* str; UniToSys(str, s.suggestionString);
        
		if (str)
			strncpy(outSuggs.suggs[i].word, str, O_MAX_WORD_LENGTH);
		else 
			outSuggs.suggs[i].word[0] = 0;
		
        outSuggs.suggs[i].word[O_MAX_WORD_LENGTH] = 0; // terminate 
        
        int st = ST_NONE;
        if (s.suggestionType == KPTSUGGSTYPE_WORD)
            st |= ST_WORD;
        if (s.suggestionType == KPTSUGGSTYPE_ELISION)
            st |= ST_ELISON;
        if (s.suggestionType == KPTSUGGSTYPE_PREFIXMATCH)
            st |= ST_WORD;
        if (s.suggestionType == KPTSUGGSTYPE_CONTENT)
            st |= ST_WORD;
        if (s.suggestionType == KPTSUGGSTYPE_PUNCTUATIONLIST)
            st |= ST_WORD;
        if (s.suggestionType == KPTSUGGSTYPE_ACRONYMEXPANSION)
            st |= ST_WORD;
        if (s.suggestionType == KPTSUGGSTYPE_ERRORCORRECTION)
            st |= ST_WORD;
        if (s.suggestionType == KPTSUGGSTYPE_SPACECONTRACTION)
            st |= ST_WORD;
        if (s.suggestionType == KPTSUGGSTYPE_NEXTLETTER)
            st |= ST_WORD;
        if (s.suggestionType == KPTSUGGSTYPE_COMPOSITION)
            st |= ST_WORD;
        if (s.suggestionType == KPTSUGGSTYPE_PROXIMITYSUGGESTION)
            st |= ST_WORD;
        
        outSuggs.suggs[i].type = st;
        outSuggs.suggs[i].ident = s.suggestionId;
        
        free(str);
    }
    
    return true;
}

bool OTextInputSystem::SuggPrint()
{
    sSuggestions sugs;
    if (!SuggGetSuggestions(sugs))
        return false;
    
    for (int i=0; i<sugs.count; i++)
    {
        printf("%d\t%s\n", sugs.suggs[i].type, sugs.suggs[i].word);
    }
    
    return true;
}

bool OTextInputSystem::ProfileSave()
{
    return KPTRESULT_SUCCEEDED(KPTFwkRunCmd(KPTCMD_PROFILE_SAVE, 0, 0));
}

bool OTextInputSystem::ProfileReload()
{
    return KPTRESULT_SUCCEEDED(KPTFwkRunCmd(KPTCMD_PROFILE_RELOAD, 0, 0));
}

// --------------------------------

size_t OTextInputSystem::SysToUni(KPTUniCharT* &outMem, const KPTSysCharT* inpMem)
{
    size_t inpByteLen = strlen(inpMem);
    if (!inpByteLen)
    {
        outMem = (KPTUniCharT*)malloc(sizeof(KPTUniCharT));
        outMem[0] = 0;
    }
    
    KPTUniCharT* uniBuff = (KPTUniCharT*)malloc(sizeof(KPTUniCharT) * (inpByteLen+1));
    uniBuff[0] = 0;
    unsigned uniNum = SysCharToUniChar(uniBuff, inpByteLen+1, inpMem, inpByteLen);
    
    outMem = uniBuff;
    return uniNum;
}
size_t OTextInputSystem::UniToSys(KPTSysCharT* &outMem, const KPTUniCharT* inpMem)
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

void OTextInputSystem::UniPrint(const KPTUniCharT* str)
{
    KPTSysCharT* sysStr; 
    UniToSys(sysStr, str);
    
    printf("%s\n", sysStr);
    
    free(sysStr);
}










