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
 * @file    unittest.h
 *
 * @brief  Unit Test Header
 *
 * @details 
 *  
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTUNITTEST_H
#define H_KPTUNITTEST_H

#define UNIT_TESTING 1

/* If this is being built for a unit test. */
#if UNIT_TESTING

/* For those who are used to __func__ from gcc. */
#ifndef __func__
#define __func__ __FUNCTION__
#endif



/*
make sure the calling convention is forced to __cdecl under UNIT_TESTING

MSVS generates RTC exception for using __stdcall if,
The function contains parameters that are larger than 64 kilobytes (KB)
<state info maintianed in test suite setup is generally huge > 64KB >.

source: http://support.microsoft.com/kb/822039
*/

#ifdef KPT_CALL
#undef KPT_CALL
#define KPT_CALL __cdecl
#endif


/* if asserts are used in source code they wont quit the application instead corresponding test is terminated */
extern void mock_assert(const int result, const char* const expression, const char * const file, const int line);
#undef assert 
#define assert(expression)  mock_assert((int)(expression), #expression, __FILE__, __LINE__); 


/* provide memory leak detection funcitonality. */
extern void* _test_malloc(const size_t size, const char* file, const int line);
extern void* _test_calloc(const size_t number_of_elements, const size_t size, const char* file, const int line);
extern void _test_free(void* const ptr, const char* file, const int line,const char *const func);


#ifdef KPTHeapCalloc
#undef KPTHeapCalloc
#define KPTHeapCalloc(aHeap,aNum,aSize)	_test_calloc(aNum, aSize, __FILE__, __LINE__) 
#endif

#ifdef KPTHeapFree
#undef KPTHeapFree
#define KPTHeapFree(heap, mem)              _test_free(mem, __FILE__, __LINE__,__func__) 
#endif

#ifdef KPTHeapMalloc
#undef KPTHeapMalloc
#define KPTHeapMalloc(heap, size)           _test_malloc(size, __FILE__, __LINE__)
#endif

#if NOCODE /* need to implement them in cMockery source */ 
#define KPTHeapRealloc(heap, mem, newsize)  KPTHeapReallocRel(heap, mem, newsize)
#define KPTHeapStrDup(heap, str)            KPTHeapStrDupRel(heap, str)
#define KPTHeapCheckAllMemory(heap)         KPTHeapCheckAllMemoryRel(heap)
#define KPTHeapEnterScope(heap)             KPTHeapEnterScopeRel(heap)
#define KPTHeapLeaveScope(heap)             KPTHeapLeaveScopeRel(heap)
#endif

#define malloc(size) _test_malloc(size, __FILE__, __LINE__)
#define calloc(num, size) _test_calloc(num, size, __FILE__, __LINE__) 
#define free(ptr) _test_free(ptr, __FILE__, __LINE__,__func__) 

#endif /* UNIT_TESTING*/

#endif /* H_KPTUNITTEST_H */
