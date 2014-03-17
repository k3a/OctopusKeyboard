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
 * @file    kptid.h
 * 
 * @brief   Identifiers for all PAL interfaces.
 *
 * @details This file contains a list of all the KPT_CC_ definitions.
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTID_H
#define H_KPTID_H

#define KPT_CC_HEAP                 0x0001
#define KPT_CC_PAL                  0x0002
#define KPT_CC_TIMER                0x0003
#define KPT_CC_TESTHEAP             0x0004
#define KPT_CC_ERRORSTACK           0x0005
#define KPT_CC_TIME                 0x0006
#define KPT_CC_OUT                  0x0007
#define KPT_CC_FILEMANAGER          0x0008
#define KPT_CC_LIST                 0x0009
#define KPT_CC_VECTOR               0x000A
#define KPT_CC_SYSSTRINGCONTAINER   0x000B
#define KPT_CC_CRITICALSECTION      0x000C
#define KPT_CC_FILEHDR              0x000D
#define KPT_CC_FILEPATH             0x000E
#define KPT_CC_MEMORY               0x000F
#define KPT_CC_FL16                 0x0010
#define KPT_CC_CRC                  0x0011
#define KPT_CC_TREE                 0x0012
#define KPT_CC_MAP                  0x0013
#define KPT_CC_UNICODEBINARYDATA    0x0014
#define KPT_CC_UNICODE              0x0015
#define KPT_CC_STRINGS              0x0016
#define KPT_CC_UNISTRINGCONTAINER   0x0017
#define KPT_CC_TEXTFILE             0x0018
#define KPT_CC_BINARYFILE           0x0019
#define KPT_CC_MEMORYFILE           0x001A
#define KPT_CC_BINARYSTREAM         0x001B
#define KPT_CC_BINARYSTORE          0x001C
#define KPT_CC_MEMORYSHARE          0x001D
#define KPT_CC_UNISTRING            0x001E
#define KPT_CC_SYSSTRING            0x001F
#define KPT_CC_STORAGE              0x0020
#define KPT_CC_DIRMANAGER           0x0021
#define KPT_CC_DIRSCAN              0x0022
#define KPT_CC_DLLLOADER            0x0023
#define KPT_CC_THREAD               0x0024
#define KPT_CC_UTIL                 0x0025

/** Macro to get the component id associated with an interface */
#define KPT_CC(name)            KPT_CC_##name

#endif /* #ifndef H_KPTID_H */
