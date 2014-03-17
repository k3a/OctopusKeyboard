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
 * @file    kptfortify_user.h
 * 
 * @brief   User options for Fortify memory debugging tool.
 *
 * @details This has been updated so that changes to this 
 *          file require kptfortify.c to be recompiled, but nothing else.
 *
 *  
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_FORTIFY_USER_H
#define H_FORTIFY_USER_H

#define FORTIFY_STORAGE              /* storage for public functions   */

#define FORTIFY_ALIGNMENT        sizeof(double) /* Byte alignment of all memory blocks */

#define FORTIFY_BEFORE_SIZE      32  /* Bytes to allocate before block */
#define FORTIFY_BEFORE_VALUE   0xA3  /* Fill value before block        */
					  
#define FORTIFY_AFTER_SIZE       32  /* Bytes to allocate after block  */
#define FORTIFY_AFTER_VALUE    0xA5  /* Fill value after block         */

#define FORTIFY_FILL_ON_ALLOCATE               /* Nuke out malloc'd memory       */
#define FORTIFY_FILL_ON_ALLOCATE_VALUE   0xA7  /* Value to initialize with       */

#define FORTIFY_FILL_ON_DEALLOCATE             /* free'd memory is cleared       */
#define FORTIFY_FILL_ON_DEALLOCATE_VALUE 0xA9  /* Value to de-initialize with    */

#define FORTIFY_FILL_ON_CORRUPTION             /* Nuke out corrupted memory    */

/*#define FORTIFY_CHECK_ALL_MEMORY_ON_ALLOCATE*/
/*#define FORTIFY_CHECK_ALL_MEMORY_ON_DEALLOCATE*/
#define FORTIFY_PARANOID_DEALLOCATE

#define FORTIFY_WARN_ON_ZERO_MALLOC  /* A debug is issued on a malloc(0) */
#define FORTIFY_FAIL_ON_ZERO_MALLOC  /* A malloc(0) will fail            */

#define FORTIFY_WARN_ON_ALLOCATE_FAIL    /* A debug is issued on a failed alloc  */
#define FORTIFY_WARN_ON_FALSE_FAIL       /* See Fortify_SetAllocateFailRate      */
#define FORTIFY_WARN_ON_SIZE_T_OVERFLOW  /* Watch for breaking the 64K limit in  */
										 /* some braindead architectures...      */

#define FORTIFY_TRACK_DEALLOCATED_MEMORY
#define FORTIFY_DEALLOCATED_MEMORY_LIMIT 8048576 /* Maximum amount of deallocated bytes to keep */
#define FORTIFY_WARN_WHEN_DISCARDING_DEALLOCATED_MEMORY
#define FORTIFY_VERBOSE_WARN_WHEN_DISCARDING_DEALLOCATED_MEMORY

/* #define FORTIFY_NO_PERCENT_P */       /* sprintf() doesn't support %p */
/* #define FORTIFY_STRDUP       */       /* if you use non-ANSI strdup() */

#define FORTIFY_LOCK()
#define FORTIFY_UNLOCK()

#define FORTIFY_DELETE_STACK_SIZE    256

#endif /* H_FORTIFY_USER_H */
