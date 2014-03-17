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
 *
 * @file    kptpal_imp.h
 * 
 * @brief   Internal header file to retrieve application directory and temporary directory
 *
 * @details
 *****************************************************************************/
#ifndef H_PAL_IMP_H
#define H_PAL_IMP_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

KPT_LIB_SYSTEM
KPTSysCharT *
KPT_CALL
KPTPalGetApplicationDirectory();

KPT_LIB_SYSTEM
KPTSysCharT *
KPT_CALL
KPTPalGetTempDirectory();

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTSYMBIAN_GLOBAL_H */
