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
 * @file    kptlibapi.h
 *
 * @brief   Include file for the KPT API library (Android)
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "kptcompile.h"

#ifndef H_KPT_LIBAPI_H
#define H_KPT_LIBAPI_H

/* Using the code directly */
#define KPT_LIB_API __attribute__ ((visibility("default")))

#endif /* #ifndef H_KPT_LIBAPI_H */
