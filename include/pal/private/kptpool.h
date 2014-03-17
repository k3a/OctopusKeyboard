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
 * @file kptpool.h           
 * 
 * @brief Pool Object for managing allocations.
 *
 * @details 
 *
 ****************************************************************************/

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPT_POOL_H
#define H_KPT_POOL_H

#include "kptlibcollections.h"
#include "kptapi.h"
#include "kptiterator.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* default grow size */
#define KPTPOOL_DEFAULT_GROW_SIZE	1

/* default number of nodes allocated if not set during construction. */
#define KPTPOOL_DEFAULT_PREALLOCSIZE	1

/* forward declarations */
typedef struct	KPTPoolT	KPTPoolT;
typedef	struct	KPTClassPoolT	KPTClassPoolT;
typedef struct KPTPoolDataT	KPTPoolDataT;

/** structures holding functions for  Pool Object */
struct	KPTClassPoolT
{
	/* gives requested number of nodes of requested size */
	void*	(*GetNodesFromPool)(KPTPoolT* aHandle,size_t aNumberOfNodes);
	/* appends requested number of nodes to Pool */
	size_t	(*AppendPoolNodes)	(KPTPoolT* aHandle,size_t aNumberOfNodes);
};

/** Pool Object to handle memory for collections. */
struct	KPTPoolT
{
	KPTClassPoolT	*cls;	/**<	holds Pool functions */
	KPTHeapT*	poolHeap;   /**<	Heap used for allocation */
	KPTPoolDataT	*start;	/**<	start of Pool Data */
	KPTPoolDataT	*end;	/**<	end of complete list	*/
	KPTPoolDataT	*tail;	/**<	end of filled nodes	*/
	size_t	nodeSize;		/**<    Size of each Node */
	size_t	freeNodes;		/**<	number of free nodes available */
	size_t chunkSize;		/**<	number of nodes appended (equals KPTPOOL_DEFAULT_GROW_SIZE by default) */
}; 

KPTResultT
KPTPoolInit(KPTPoolT *aHandle,
            KPTHeapT* aHeap,
            size_t aNodeSize, 
            size_t aNumberOfNodes, 
            size_t aChunkSize);

void
KPTPoolClassInit(KPTPoolT* aHandle);

KPTResultT
KPTPoolCreate(KPTPoolT* aHandle,
              KPTHeapT* aHeap,
              size_t aNodeSize,
              size_t aNumberOfNodes,
              size_t aChunkSize);

void	
KPTPoolDestroy(KPTPoolT	*aHandle);

size_t 
KPTPoolGetNodeSize(KPTPoolT *aHandle);

KPTResultT 
KPTPoolSetChunkSize(KPTPoolT *aHandle, 
				   size_t aChunkSize);


/* Handy Macros */
#define KPTPool_GetNodes(aHandle,aNumberOfNodes)	\
		(((KPTPoolT*)(aHandle))->cls->GetNodesFromPool((aHandle),(aNumberOfNodes)))

#define KPTPool_AppendNodes(aHandle,aNumberOfNodes)	\
		(((KPTPoolT*)(aHandle))->cls->AppendPoolNodes((aHandle),(aNumberOfNodes)))


#ifdef __cplusplus
}
#endif /*__cplusplus */


#endif	/*	H_KPT_POOL_H */
