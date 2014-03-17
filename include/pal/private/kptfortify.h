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
 * @file    kptfortify.h
 * 
 * @brief   Fortify memory debugging tool
 *
 *  
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_FORTIFY_H
#define H_FORTIFY_H

/*
 * Code to detect and configure for various compilers lives here.
 */

#ifdef __GNUG__ 
	/* GCC configuration */
	#define FORTIFY_PROVIDE_ARRAY_NEW
	#define FORTIFY_PROVIDE_ARRAY_DELETE
#endif

#ifdef __BC45__
	/* Borland C++ 4.5 configuration */
	#define FORTIFY_PROVIDE_ARRAY_NEW
	#define FORTIFY_PROVIDE_ARRAY_DELETE
	#define FORTIFY_FAIL_ON_ZERO_MALLOC
#endif

#ifdef __SASC
	/* SAS configuration */
	#define FORTIFY_FAIL_ON_ZERO_MALLOC
#endif

#if defined(__WINSCW__) || defined(__GCCE__)
	/* Symbian emulator and device builds */
	#define FORTIFY_PROVIDE_ARRAY_NEW
	#define FORTIFY_PROVIDE_ARRAY_DELETE
#endif

#ifdef _MSC_VER
	#define FORTIFY_PROVIDE_ARRAY_NEW
	#define FORTIFY_PROVIDE_ARRAY_DELETE
#endif

/* Allocators */
#define Fortify_Allocator_malloc            0    /* ANSI C   */
#define Fortify_Allocator_calloc            1    /* ANSI C   */
#define Fortify_Allocator_realloc           2    /* ANSI C   */
#define Fortify_Allocator_strdup            3    /*      C   */
#define Fortify_Allocator_new               4    /* ANSI C++ */
#define Fortify_Allocator_array_new         5    /* Some C++ */

/* Deallocators */
#define Fortify_Deallocator_nobody          0
#define Fortify_Deallocator_free            1    /* ANSI C   */
#define Fortify_Deallocator_realloc         2    /* ANSI C   */
#define Fortify_Deallocator_delete          3    /* ANSI C++ */
#define Fortify_Deallocator_array_delete    4    /* Some C++ */

/* Public Fortify Types */
typedef void (*Fortify_OutputFuncPtr)(const char *);

#ifdef __cplusplus
extern "C" {
#endif

/* Core Fortify Functions */
void *Fortify_Allocate  (size_t size, unsigned char allocator, const char *file, unsigned long line);
void  Fortify_Deallocate(void *uptr,  unsigned char deallocator, const char *file, unsigned long line);
size_t Fortify_CheckAllMemory(const char *file, unsigned long line);
size_t Fortify_ListAllMemory (const char *file, unsigned long line);
size_t Fortify_DumpAllMemory (const char *file, unsigned long line);
int   Fortify_CheckPointer(void *uptr, const char *file, unsigned long line);
void  Fortify_LabelPointer(void *uptr, const char *label, const char *file, unsigned long line);
unsigned char Fortify_EnterScope(const char *file, unsigned long line);
unsigned char Fortify_LeaveScope(const char *file, unsigned long line);
void  Fortify_OutputStatistics(const char *file, unsigned long line);
size_t Fortify_GetCurrentAllocation(const char *file, unsigned long line);
int   Fortify_SetAllocateFailRate(int Percent);
void  Fortify_SetAllocationLimit(unsigned long Limit, const char *file, unsigned long line);
void  Fortify_SetMaxAllocationsLimit(unsigned long Limit, const char *file, unsigned long line);
int   Fortify_SetFailRate(int Percent);
Fortify_OutputFuncPtr Fortify_SetOutputFunc(Fortify_OutputFuncPtr Output);
void  Fortify_Disable(const char *file, unsigned long line);
void  Fortify_Enable(void);
void  Fortify_Mark(const char *file, unsigned long line);

/* Fortify versions of the ANSI C memory allocation functions */
void *Fortify_malloc(size_t size, const char *file, unsigned long line);
void *Fortify_realloc(void *ptr, size_t new_size, const char *file, unsigned long line);
void *Fortify_calloc(size_t num, size_t size, const char *file, unsigned long line);
void  Fortify_free(void *uptr, const char *file, unsigned long line);

/* Fortify versions of some non-ANSI C memory allocation functions */
char *Fortify_strdup(const char *oldStr, const char *file, unsigned long line);
wchar_t *Fortify_strdupW(const wchar_t *oldStr, const char *file, unsigned long line);

#ifdef __cplusplus
/* Magic global variable */
extern int gbl_FortifyMagic;
#endif

#ifdef __cplusplus
}
#endif

#endif /* H_FORTIFY_H */
