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
 * @file kpttreefactory.h                                                           
 * 
 * @brief Object providing Factory Method for Tree construction.
 *
 * @details 
 *
 ****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_TREE_FACTORY_H
#define H_TREE_FACTORY_H


#include "kptlibcollections.h"
#include "kptapi.h" 
#include "kptiterator.h"
#include "kpttree.h"
#include "kpttreebase.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/*
 Factory method to create tree based on type.
*/
KPTTreeBaseT*
KPT_CALL
KPTCreateTreeByType(KPTHeapT* aHeap, 
                    size_t aNodeSize, 
                    KPTTreeTypeT aTreeType,
                    size_t aPreAllocs, 
                    KPTBoolT aIsUnique, 
                    KPTResultT *aRetStatus);

/*
 Factory method to destroy tree based on type.
*/
void
KPT_CALL
KPTTreeFinalize(KPTTreeBaseT *aTree, 
                KPTTreeTypeT aTreeType,
				KPTNodeDestructionFnT* aDestructFn);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif	/*	H_TREE_FACTORY_H */
