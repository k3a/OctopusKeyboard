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
 * @file    kptbool.h
 *
 * @brief   Boolean type for interfaces.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTBOOL_H
#define H_KPTBOOL_H

/** Boolean type */
enum KPTBoolT
{
	eKPTFalse = 0,  /**< false */
	eKPTTrue = 1    /**< true */
};
typedef enum KPTBoolT KPTBoolT;

#endif /* #ifndef H_KPTBOOL_H */
