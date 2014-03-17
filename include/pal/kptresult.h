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
 * @file    kptresult.h
 *
 * @brief   Return types and macros in the KPT system.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTRESULT_H
#define H_KPTRESULT_H

typedef int32_t KPTResultT; /**< Result type */

/**
 *   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0
 *   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 *  +---+---+-----------------------+-------------------------------+
 *  | S | R |       Component       +         Status Code           |
 *  +---+---+-----------------------+-------------------------------+
 *
 * S: Severity code
 *      00: Success
 *      10: Error
 *      11: Warning
 *
 * R: reserved
 *
 * Component: Component code
 * Status Code: Status code
 */

/** Result severity for Success */
#define KPT_SV_SUCCESS  0x00

/** Result severity for Debug codes */
#define KPT_SV_DEBUG    0x01

/** Result severity for Warnings */
#define KPT_SV_WARNING  0x02

/** Result severity for Errors */
#define KPT_SV_ERROR    0x03


/** Mask for severity bits */
#define KPTRESULT_MASK_SEVERITY(aValue) ((aValue) & 0x03)

/** Mask for component bits */
#define KPTRESULT_MASK_COMPONENT(aValue) ((aValue) & 0x0FFF)

/** Mask for code bits */
#define KPTRESULT_MASK_STATUS(aValue) ((aValue) & 0xFFFF)


/** Offset for severity bits */
#define KPTRESULT_SV_OFFSET 30

/** Offset for component bits */
#define KPTRESULT_CC_OFFSET 16


/** Get the severity code from a result */
#define KPTRESULT_GETSEVERITY(aResult) KPTRESULT_MASK_SEVERITY((aResult) >> KPTRESULT_SV_OFFSET)

/** Get the component code from a result */
#define KPTRESULT_GETCOMPONENT(aResult) KPTRESULT_MASK_COMPONENT((aResult) >> KPTRESULT_CC_OFFSET)

/** Get the status code from a result */
#define KPTRESULT_GETSTATUS(aResult) KPTRESULT_MASK_STATUS(aResult)


/** Make a result from severity, component and code */
#define KPTRESULT_MAKE(aSeverity, aComponent, aCode) \
            ((KPTResultT) (((uint32_t)KPTRESULT_MASK_SEVERITY(aSeverity)<<KPTRESULT_SV_OFFSET) | \
                           ((uint32_t)KPTRESULT_MASK_COMPONENT(aComponent)<<KPTRESULT_CC_OFFSET) | \
                           (uint32_t)KPTRESULT_MASK_STATUS(aCode)))

/** Make an information result from component and code */
#define KPTRESULT_INFO(aComponent, aCode) KPTRESULT_MAKE(KPT_SV_SUCCESS, aComponent, aCode)

/** Make a debug result from component and code */
#define KPTRESULT_DEBUG(aComponent, aCode) KPTRESULT_MAKE(KPT_SV_DEBUG, aComponent, aCode)

/** Make a warning result from component and code */
#define KPTRESULT_WARN(aComponent, aCode) KPTRESULT_MAKE(KPT_SV_WARNING, aComponent, aCode)

/** Make an error result from component and code */
#define KPTRESULT_ERROR(aComponent, aCode) KPTRESULT_MAKE(KPT_SV_ERROR, aComponent, aCode)



/** Check if a result represents an error */
#define KPTRESULT_ISERROR(aResult) (KPT_SV_ERROR == KPTRESULT_GETSEVERITY(aResult))

/** Check if a result represents a warning */
#define KPTRESULT_ISWARNING(aResult) (KPT_SV_WARNING == KPTRESULT_GETSEVERITY(aResult))

/** Check if a result represents information only */
#define KPTRESULT_ISSUCCESS(aResult) (KPT_SV_SUCCESS == KPTRESULT_GETSEVERITY(aResult))

/** Check if a result represents debug information */
#define KPTRESULT_ISDEBUG(aResult) (KPT_SV_DEBUG == KPTRESULT_GETSEVERITY(aResult))


/** Check if a result represents a warning or error */
#define KPTRESULT_FAILED(aResult) ((KPTResultT)(aResult) < 0)

/** Check if a result represents success */
#define KPTRESULT_SUCCEEDED(aResult) ((KPTResultT)(aResult) >= 0)

/** Successful result */
#define KPTRESULT_SUCCESS           (KPTResultT)0

/** Uninitialized result */
#define KPTRESULT_INVALID           (KPTResultT)-1

#endif /* #ifndef H_KPTRESULT_H */
