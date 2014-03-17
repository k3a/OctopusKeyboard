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
 * @file    kptapi_libversion.h
 *
 * @brief   API Library Version Information 
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTAPI_LIBVERSION_H
#define H_KPTAPI_LIBVERSION_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* library version */
KPT_LIB_API
KPTResultT
KPT_CALL
KPTFwkGetVersion(uint16_t* aMajor,
                 uint16_t* aMinor,
                 uint16_t* aPatch,
                 uint16_t* aBuild);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTAPI_LIBVERSION_H */
