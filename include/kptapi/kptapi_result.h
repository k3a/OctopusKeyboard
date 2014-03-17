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
 * @file    kptapi_result.h
 *
 * @brief   Return types and macros in the KPT system.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTAPI_RESULT_H
#define H_KPTAPI_RESULT_H

#include "kptresult.h"

#define KPT_CC_FRAMEWORK     0x101
#define KPT_CC_APIMGMT       0x102
#define KPT_CC_CONFIG        0x103
#define KPT_CC_DICTIONARIES  0x104
#define KPT_CC_ERRORMGR      0x105
#define KPT_CC_INPUTMGR      0x106
#define KPT_CC_KEYMAP        0x107
#define KPT_CC_LEARNING      0x108
#define KPT_CC_COMPONENTS    0x10A
#define KPT_CC_OUTPUT        0x10D
#define KPT_CC_PACKAGEMGMT   0x10E
#define KPT_CC_PERSONAL      0x10F
#define KPT_CC_SUGGESTIONS   0x112
#define KPT_CC_FILE          0x116
#define KPT_CC_LANGUAGE      0x117
#define KPT_CC_TEMPV2SUPPORT 0x118

#endif /* #ifndef H_KPTAPI_RESULT_H */
