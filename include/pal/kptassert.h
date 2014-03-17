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
 * @file    kptassert.h
 *
 * @brief   Assert functions.
 *
 * @details 
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTASSERT_H
#define H_KPTASSERT_H

#include "kpterr.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \def KPTASSERT_STATIC(aCondition)
 * Compile time assertions on static code. These can be used for portability checks
 * but they will not appear in the runtime code.
 */

/**
 * \def KPTASSERT_DYNAMIC(aCondition)
 * Runtime assertion.
 */
#ifdef NDEBUG

	#define KPTASSERT_DYNAMIC(x)	KPT_NOP_FUNCTION

#else

	#define KPTASSERT_DYNAMIC(aCondition)	\
		if (!(aCondition)) KPTERR_PUSHTEXT1(KPTRESULT_ERROR(0, KPT_SC_ASSERT), KPT_TS(#aCondition))

#endif

#define KPTASSERT_JOIN_P(x, y) x ## y
#define KPTASSERT_JOIN(x, y) KPTASSERT_JOIN_P(x, y)
#define KPTASSERT_STATIC(aCondition) \
	typedef int KPTASSERT_JOIN(KPTASSERT_STATIC_, __LINE__) [(aCondition) ? 1 : -1]

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTASSERT_H */
