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
 * @file kptfilepath_platform.h
 *
 * @brief Platform-dependent file path defines.
 *
 * @details 
 *
 ****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPT_FILEPATHPLATFORM_H
#define H_KPT_FILEPATHPLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus */

#ifndef MAX_PATH
#define MAX_PATH PATH_MAX
#endif

#ifndef KPT_DIR_DELIM_STD
#define KPT_DIR_DELIM_STD   KPT_TS('/')
#endif
#ifndef KPT_DIR_DELIM_ALT
#define KPT_DIR_DELIM_ALT   KPT_TS('\\')
#endif


#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* H_KPT_FILEPATHPLATFORM_H */
