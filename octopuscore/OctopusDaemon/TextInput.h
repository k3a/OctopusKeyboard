//
//  TextInput.h
//  OctopusDaemon
//
//  Created by K3A on 5/19/12.
//  Copyright (c) 2012 K3A. All rights reserved.
//

#ifndef OctopusDaemon_TextInput_h
#define OctopusDaemon_TextInput_h

#include <stdint.h>
#include <unistd.h> // size_t etc
#include <stddef.h>

#include "kptstrings.h"
#include "kptunicode.h"

unsigned SysCharToUniChar(KPTUniCharT* OutWord, size_t OutWordSize, const KPTSysCharT* InWord, size_t len);
unsigned UniCharToSysChar(KPTSysCharT* OutWord, size_t OutWordSize, const KPTUniCharT* InWord, size_t len);

#include "octopus_mach_types.h"

class OTextInputSystem
{
public:
    OTextInputSystem(const char* profilePath);
    ~OTextInputSystem();
    
    bool IsInitialized()const{return mInited;};
    
    bool SetKeyLayout(eKeyLayout kl);
    bool LearnBuffer(const char* utf8Buff);
    bool EnableAutoLearning(bool enable=true);
    bool IsAutoLearningEnabled();
    bool EnableAutoCorrection(bool enable=true, bool errorCorrections=true, bool spaceCorrections=true);
    
    bool UserDictClear();
	bool UserDictGetWordForID(unsigned idx, char *&word);
    bool UserDictWordExists(const char* word);
    bool UserDictGetNumWords(unsigned& numWords);
    bool UserDictGetMaxWords(unsigned& numWords);
    bool UserDictSetMaxWords(unsigned numWords);
    
    bool DictGetList(sDictionaryArray* outDicts, unsigned* outNumDicts);
	bool DictEnable(unsigned dictId, bool enable=true);
    
    bool InputClear();
    bool InputRemove(int beforeCursor, int afterCursor);
    bool InputReplace(int index, int len, const char* replacement);
    bool InputCursorMove(eSeekOrigin origin, int value);
    bool InputCursorGetPosition(int &outPosition, int &outLen);
    bool InputInsertChar(const char ch, eCapitalizationMode cm = CM_SENTENCE, bool disableAutoLearn = false);
    bool InputInsertString(const char* str, eCapitalizationMode cm = CM_SENTENCE, bool disableAutoLearn = false);
    bool InputInsertSugg(unsigned set, unsigned ident, bool appendSpace=true);
    bool InputGetCurrWord(oword_t &outWord);
    bool InputLearn(eInputLearnOptions lo = IL_ALL);
    
	/** \param suggestionThreshold Specifies which words to use for suggestion (0-100 where 0 = all stored words, 100 = most frequently used ones only) */
    bool SuggConfigure(unsigned maxSuggestions, unsigned suggestionThreshold, bool proximitySuggestion, bool errorCorrection, bool completion);
    bool SuggConfigureCaps(bool capKnownWords, bool capSentence, bool capUser, bool capNext);
    bool SuggGetSuggestions(sSuggestions& outSuggs);
    bool SuggPrint();
    
    bool ProfileSave();
	bool ProfileReload();
    
private:
    size_t SysToUni(KPTUniCharT* &outMem, const KPTSysCharT* inpMem); // user is responsible for freeing memory
    size_t UniToSys(KPTSysCharT* &outMem, const KPTUniCharT* inpMem); // user is responsible for freeing memory
    void UniPrint(const KPTUniCharT* str);
    
private:
    bool    mInited;
};


#endif
