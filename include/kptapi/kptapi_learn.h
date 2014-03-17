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
 * @file    kptapi_learn.h
 * 
 * @brief   Learn types and structures.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTAPI_LEARN_H
#define H_KPTAPI_LEARN_H

#include "kptapi.h"
#include "kptapi_progress.h"
#include "kptapi_dict.h"

/** General learning options. */
enum KPTLearnOptionsT
{
	eKPTLearnEnabled = KPTBIT(0),   /**< Automatic learning enabled */
};
typedef enum KPTLearnOptionsT KPTLearnOptionsT;

/** Specifies the range to learn in the Input Buffer. */
enum KPTLearningRangeT
{
	eKPTLearnAll = 0,               /**< Learn all of the text in the engine */
	eKPTLearnWordGroup = 1,         /**< Learns the word group containing the cursor */
	eKPTLearnPreviousWordGroup = 2  /**< Learns the word grouping before the previous space */
};
typedef enum KPTLearningRangeT KPTLearningRangeT;


/** Stages in single-pass or multiple-pass learning. */
enum KPTLearningStageT
{
	eKPTLearnSingle = 0,            /**< Learns the data in a single call */
	eKPTLearnMultiStart = 1,        /**< Starts a new multi-phase pass */
	eKPTLearnMultiContinue = 2,     /**< Continues a multi-phase pass */
	eKPTLearnMultiEnd = 3,          /**< Completes a multi-phase pass */
	eKPTLearnFlush = 4,             /**< Flushes any cached storage without learning */
};
typedef enum KPTLearningStageT KPTLearningStageT;

/** Command details to learn the contents of the Input Buffer. */
typedef struct KPTLearnContentsT KPTLearnContentsT;
struct KPTLearnContentsT
{
	KPTLearningStageT stage;        /**< The learning stage */
	KPTLearningRangeT range;        /**< The range of text to be learned */
	KPTProgressFnT progress;        /**< A progress callback (optional) */
	intptr_t progressContext;       /**< User context for the progress callback (optional) */
};

/** Command details to learn the contents of an external buffer. */
typedef struct KPTLearnBufferT KPTLearnBufferT;
struct KPTLearnBufferT
{
	KPTUniCharT* buffer;            /**< The buffer to learn */
	size_t bufferSize;              /**< The number of characters in the buffer */
	KPTLearningStageT stage;        /**< The learning stage */
	KPTLanguageIdT language;        /**< The language of the text (optional) */
	KPTProgressFnT progress;        /**< A progress callback (optional) */
	intptr_t progressContext;       /**< User context for the progress callback (optional) */
};

#endif /* #ifndef H_KPTAPI_LEARN_H */
