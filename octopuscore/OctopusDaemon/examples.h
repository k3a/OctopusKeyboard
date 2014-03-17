//
//  examples.h
//  CoreRegressSystem
//
//  Created by K3A on 5/19/12.
//  Copyright (c) 2012 K3A. All rights reserved.
//

#ifndef CoreRegressSystem_examples_h
#define CoreRegressSystem_examples_h

#include <stdint.h> // uint8_t etc
#include "kptresult.h"

KPTResultT
Example_KPTCMD_SUGGS_GETSUGGESTIONS(void);

KPTResultT
Example_KPTCMD_KEYMAP_GETAVAILABLE(void);

KPTResultT
Example_KPTCMD_COMPONENT_GETAVAILABLE(void);

KPTResultT
Example_KPTCMD_KEYMAP_GETLAYOUT(void);

KPTResultT
Example_KPTCMD_KEYMAP_QUERY(void);

KPTResultT
Example_KPTCMD_ERROR_POPSTACK(void);

KPTResultT
Example_KPTCMD_DICTIONARY_GETLANGLIST(void);

KPTResultT
Example_KPTCMD_DICTIONARY_GETLIST(void);

KPTResultT
Example_KPTCMD_INPUTMGR_GETCURRWORD(void);

#endif
