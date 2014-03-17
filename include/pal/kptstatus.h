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
 * @file    kptstatus.h
 *
 * @brief   Result status codes for the KPT system.
 *
 * @details This file contains status codes that will be used as part of the 
 *          kptresult mechanism. Each status code is 16-bits.
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTSTATUS_H
#define H_KPTSTATUS_H

/** Successful operation */
#define KPT_SC_SUCCESS               0x0000

/** Undefined error */
#define KPT_SC_ERROR                 0x0001

/** Object or item was not found */
#define KPT_SC_NOTFOUND              0x0002

/** Operation would exceed length limits */
#define KPT_SC_LENGTHERROR           0x0003

/** Value was not within the expected range */
#define KPT_SC_OUTOFRANGE            0x0004

/** An argument to the function was invalid */
#define KPT_SC_INVALIDARGUMENT       0x0005

/** The operation is not implemented */
#define KPT_SC_NOTIMPLEMENTED        0x0006

/** The operation is not permitted for the present state*/
#define KPT_SC_INVALIDOPERATION      0x0007

/** The structure of the data is not supported */
#define KPT_SC_BADSCHEMA             0x0008

/** The valid lifetime of the object has expired */
#define KPT_SC_EXPIRED               0x0009

/** Out of memory condition */
#define KPT_SC_OUTOFMEMORY           0x000A

/** Failed to copy object */
#define KPT_SC_COPYFAILED            0x000B

/** Failed to move object */
#define KPT_SC_MOVEFAILED            0x000C

/** Failed to delete object */
#define KPT_SC_DELETEFAILED          0x000D

/** Failed to rename object */
#define KPT_SC_RENAMEFAILED          0x000E

/** Invalid pointer */
#define KPT_SC_INVALIDPOINTER        0x000F

/** Object already exists */
#define KPT_SC_ALREADYEXISTS         0x0010

/** Target buffer is too small */
#define KPT_SC_BUFFERTOOSMALL        0x0011

/** Target buffer is full */
#define KPT_SC_BUFFERFULL            0x0012

/** Source data is invalid */
#define KPT_SC_SOURCEINVALID         0x0013

/** No more source data */
#define KPT_SC_SOURCEEXHAUSTED       0x0014

/** Interface invalid */
#define KPT_SC_INVALIDINTERFACE      0x0015

/** Operation timed out */
#define KPT_SC_TIMEOUT               0x0016

/** Lock failed */
#define KPT_SC_LOCKFAILED            0x0017

/** Unlock failed */
#define KPT_SC_UNLOCKFAILED          0x0018

/** Read operation failed */
#define KPT_SC_READFAILED            0x0019

/** Write operation failed */
#define KPT_SC_WRITEFAILED           0x001A

/** Access denied */
#define KPT_SC_ACCESSDENIED          0x001B

/** Item is already initialised */
#define KPT_SC_ALREADYINITIALISED    0x001C

/** Operation Cancelled */
#define KPT_SC_CANCELLED             0x001D

/** Assertion failed */
#define KPT_SC_ASSERT                0x001E

/** Invalid handle */
#define KPT_SC_INVALIDHANDLE         0x001F

/** End-of-file  */
#define KPT_SC_ENDOFFILE             0x0020

/** Not Empty */
#define KPT_SC_NOTEMPTY              0x0021

/** OS error code */
#define KPT_SC_OSERROR               0x0022

/** Device/Object not open */
#define KPT_SC_NOTOPEN               0x0023

/** Could not open Device/Object */
#define KPT_SC_OPENFAILED            0x0024

/** Checksum error */
#define KPT_SC_DATACHECKFAILED       0x0025

/** Checksum error */
#define KPT_SC_HEADERCHECKFAILED     0x0026

/** Buffer underrun */
#define KPT_SC_UNDERRUN              0x0027

/** Buffer overrun */
#define KPT_SC_OVERRUN               0x0028

/** Thread is being initialised */
#define KPT_SC_THREADINIT            0x0029

/** An object is still in use */
#define KPT_SC_OBJECTINUSE           0x002A

/** An error occured due to a path setting or length */
#define KPT_SC_PATHERROR             0x002B

#endif /* #ifndef H_KPTSTATUS_H */
