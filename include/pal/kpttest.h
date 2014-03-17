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
 * @file    kpttest.h
 *
 * @brief   KPTTest interface.
 *
 * @details 
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTTEST_H
#define H_KPTTEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "kptlibtest.h"
#include "cmockery.h"

#ifdef __cplusplus
}
#endif /*__cplusplus */

#define KPT_SET_UNIT(u, f) { u->name = #f; u->function = f; u->function_type = UNIT_TEST_FUNCTION_TYPE_TEST; }
#define KPT_SETUP_UNIT(u, f) { u->name = #f; u->function = f; u->function_type = UNIT_TEST_FUNCTION_TYPE_SETUP; }
#define KPT_TEARDOWN_UNIT(u, f) { u->name = #f; u->function = f; u->function_type = UNIT_TEST_FUNCTION_TYPE_TEARDOWN; }

static KPTINLINE
int KPTTestCopyGroup(UnitTest* aTarget,
                     size_t aTargetMax,
                     size_t* aTargetIndex,
                     UnitTest* aSource,
                     size_t aSourceCount)
{
	if ((*aTargetIndex + aSourceCount) >= aTargetMax)
	{
		return -1;
	}
	else
	{
		UnitTest* destination = aTarget + *aTargetIndex;
		size_t index = 0;
		for(; index < aSourceCount; ++index)
		{
			*destination++ = *aSource++;
		}
		*aTargetIndex += aSourceCount;
	}
	return 0;
}

#endif /* #ifndef H_KPTTEST_H */
