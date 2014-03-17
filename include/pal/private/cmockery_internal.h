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
 * @file    cmockery_internal.h
 * 
 * @brief   internal cmockery header file declarations
 *
 * @details
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_CMOCKERY_SYM_H
#define H_CMOCKERY_SYM_H

/*#ifndef C_FILE_COMPILE_AS_CPP*/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/*#endif*/

int KPTTestCaptureExceptions();
void KPTTestRestoreExceptions(int aHandleExceptions);

/*#ifndef C_FILE_COMPILE_AS_CPP*/
#ifdef __cplusplus
}
#endif /*__cplusplus */
/*#endif*/

#endif /* #ifndef H_CMOCKERY_SYM_H*/
