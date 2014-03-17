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
 * @file    kpttextfilebomparser.h
 *
 * @brief   Interface to BOM parser.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTTEXTFILEBOMPARSER_H
#define H_KPTTEXTFILEBOMPARSER_H

#include "kptlibsystem.h"
#include "kptapi.h"
#include "kptbinarystream.h"
#include "kpttextfile.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

KPT_LIB_SYSTEM
KPTBoolT
KPT_CALL
KPTIdentifyBinaryStreamBOM(KPTBinaryStreamT* aStream,
                           KPTTextFileBOMT aUserSuppliedBOM,
                           KPTTextFileBOMT* aBOM,
                           KPTBoolT* aBOMFromData);

#ifdef __cplusplus
}
#endif /*__cplusplus */


#endif /* H_KPTTEXTFILEBOMPARSER_H */
