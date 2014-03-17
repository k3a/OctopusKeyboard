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
 * @file kpttreebase.h                      
 * 
 * @brief abstract Base class for Tree.
 *
 * @details 
 *
 ****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_TREE_BASE_H
#define H_TREE_BASE_H

#include "kptlibcollections.h"
#include "kptapi.h"
#include "kptiterator.h"
#include "kptpool.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Internal macro to get the value in node */
#define KPTTREE_NODE_VALUE(nodeSize,node)	\
		(nodeSize)? &((node)->value) : (node)->value


/* Function to get the Key Value of given Node */
typedef void* (KPT_CALLB KPTTreeGetKeyFnT) (void* aNode);

/** Tree types */
enum KPTTreeTypeT
{       
		eKPTRBTree =  eKPTTreeRBTree,	/**< Red Black Tree */
        eKPTBSTree =  eKPTTreeBSTree,	/**< Binary Search Tree */
        eKPTERRTree = KPTBIT(30)		/**< Error Value */ 
};
typedef enum KPTTreeTypeT	KPTTreeTypeT;



/* forward declaration for TreeBase Object */
typedef struct KPTTreeBaseT	KPTTreeBaseT;
typedef struct KPTClassTreeBaseT	KPTClassTreeBaseT;

/** structures holding functions for  TreeBase Object */
struct KPTClassTreeBaseT
{
	/* Function to Insert Tree Node */
	KPTIteratorT (*InsertTreeNode)(KPTTreeBaseT* aHandle, 
		const void* aNode,
		KPTNodeComparisionFnT* aCompareFn,
		KPTTreeGetKeyFnT* aKeyFn,
		KPTNodeConstructionFnT* aConstructFn,
		KPTResultT* aRetStatus);

	/* Function to Search Tree*/
	KPTIteratorT (*SearchTreeNode)(KPTTreeBaseT* aHandle,
		const void* aKey,
		KPTNodeComparisionFnT* aCompareFn,
		KPTTreeGetKeyFnT* aKeyFn,
		KPTResultT* aRetStatus);

	/* Function to Search Tree*/
	KPTConstIteratorT (*SearchTreeNodeConst)(const KPTTreeBaseT* aHandle,
		const void* aKey,
		KPTNodeComparisionFnT* aCompareFn,
		KPTTreeGetKeyFnT* aKeyFn,
		KPTResultT* aRetStatus);

	/* Function to Delete tree Node */
	void (*DeleteTreeNode)(KPTTreeBaseT* aHandle,
		void* aNode,
		KPTNodeComparisionFnT* aCompareFn,
		KPTTreeGetKeyFnT* aKeyFn,
		KPTNodeDestructionFnT* aDelFn,
		KPTResultT* aRetStatus);

	/* Function to Delete all Tree Nodes */
	void (*ClearTree)(KPTTreeBaseT* aHandle,
		KPTNodeDestructionFnT* aDelFn,
		KPTResultT* aRetStatus);
	
	/* Function to get Tree Root */
	KPTIteratorT (*GetRoot) (KPTTreeBaseT* aHandle);

	/* Fucntion to get Type of Tree being Used */
	KPTTreeTypeT (*GetTreeType) (KPTTreeBaseT* aHandle);
	
	/* Function to get Start node of Tree (min element - in order) */
	KPTIteratorT (*GetTreeBegin) (KPTTreeBaseT* aHandle);

	/* Functon to get Last Node (Max value - inorder) */
	KPTIteratorT (*GetTreeEnd) (KPTTreeBaseT* aHandle);

	/* Function to get Tree Root */
	KPTConstIteratorT (*GetRootConst) (const KPTTreeBaseT* aHandle);

	/* Function to get Start node of Tree (min element - in order) */
	KPTConstIteratorT (*GetTreeBeginConst) (const KPTTreeBaseT* aHandle);

	/* Functon to get Last Node (Max value - inorder) */
	KPTConstIteratorT (*GetTreeEndConst) (const KPTTreeBaseT* aHandle);

};

/** KPTTreeBase Object - Abstract Tree Base */
struct KPTTreeBaseT
{
	KPTClassTreeBaseT* cls;  /**< holds Tree functions */
	KPTHeapT* treeHeap;      /**< Heap used for allocation */
	KPTPoolT* treePool;      /**< Pool object used for memory allocation */
	size_t preallocs;        /**< reserve nodes */
	size_t chunkSize;        /**< grow size by which nodes are added once reserve nodes are used */
	size_t count;            /**< number of nodes */
	size_t nodeSize;         /**< size of value stored */
	KPTBoolT isUnique;       /**< False if supports non unique keys */
};

KPTResultT
KPTTreeBaseInit(KPTTreeBaseT	*aHandle,
				 KPTHeapT* aHeap,
				 size_t aNodeSize,
				 size_t aPoolNodeSize,
				 size_t aPreAllocs,
				 KPTBoolT aIsUnique);
void	KPTClassTreeBaseInit(KPTTreeBaseT*);
void	KPTTreeBaseFinalize(KPTTreeBaseT*);


/* Function to Make Tree Object of given type*/
KPTResultT
KPTTreeMake(KPTTreeTypeT aTreeType,
			KPTTreeBaseT *aHandle,
			KPTHeapT* aHeap,
			size_t aNodeSize,
			size_t aPreAllocs,
			KPTBoolT aIsUnique);


/* Handy Macros */

#define KPTTreeBase_SearchTreeNode(aHandle,aNode,aCompareFn,aKeyFn,aRetStatus)	\
		(((KPTTreeBaseT*)(aHandle))->cls->SearchTreeNode((aHandle),(aNode),(aCompareFn),(aKeyFn),(aRetStatus)));

#define KPTTreeBase_SearchTreeNodeConst(aHandle,aNode,aCompareFn,aKeyFn,aRetStatus)	\
		(((KPTTreeBaseT*)(aHandle))->cls->SearchTreeNodeConst((aHandle),(aNode),(aCompareFn),(aKeyFn),(aRetStatus)));

#define KPTTreeBase_InsertTreeNode(aHandle,aNode,aCompareFn,aKeyFn,aConstructFn,aRetStatus)	\
		(((KPTTreeBaseT*)(aHandle))->cls->InsertTreeNode((aHandle),(aNode),(aCompareFn),(aKeyFn),(aConstructFn),(aRetStatus)));

#define KPTTreeBase_DeleteTreeNode(aHandle,aNode,aCompareFn,aKeyFn,aDelFn,aRetStatus)	\
		(((KPTTreeBaseT*)(aHandle))->cls->DeleteTreeNode((aHandle),(aNode),(aCompareFn),(aKeyFn),(aDelFn),(aRetStatus)));

#define KPTTreeBase_ClearTree(aHandle,aDelFn,aRetStatus)	\
		(((KPTTreeBaseT*)(aHandle))->cls->ClearTree((aHandle),(aDelFn),(aRetStatus)));

#define KPTTreeBase_GetRoot(aHandle)	\
		(((KPTTreeBaseT*)(aHandle))->cls->GetRoot((aHandle)));

#define KPTTreeBase_GetRootConst(aHandle)	\
		(((const KPTTreeBaseT*)(aHandle))->cls->GetRootConst((aHandle)));

#define KPTTreeBase_GetTreeType(aHandle)	\
		(((KPTTreeBaseT*)(aHandle))->cls->GetTreeType((aHandle)));

#define KPTTreeBase_TreeBegin(aHandle)	\
		(((KPTTreeBaseT*)(aHandle))->cls->GetTreeBegin((aHandle)));

#define KPTTreeBase_TreeBeginConst(aHandle)	\
		(((const KPTTreeBaseT*)(aHandle))->cls->GetTreeBeginConst((aHandle)));

#define KPTTreeBase_TreeEnd(aHandle)	\
		(((KPTTreeBaseT*)(aHandle))->cls->GetTreeEnd((aHandle)));

#define KPTTreeBase_TreeEndConst(aHandle)	\
		(((const KPTTreeBaseT*)(aHandle))->cls->GetTreeEndConst((aHandle)));


#ifdef __cplusplus
}
#endif /*__cplusplus */


#endif	/* H_TREE_BASE_H */
