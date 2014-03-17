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
 * @file    kptendian.h
 *
 * @brief   Byte Order issues
 *
 * @details This file handling byte order issues. Some of the order functions 
 *          may be implemented as macros.
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTENDIAN_H
#define H_KPTENDIAN_H

#include "kptlibsystem.h"
#include "kptapi.h"

#define KPT_ENDIAN_LITTLE   1
#define KPT_ENDIAN_BIG      2
#define KPT_ENDIAN_DYNAMIC  3

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \def KPTNToH16(n)
 * Converts a 16-bit integer from network to host order.
 */

/**
 * \def KPTHToN16(n)
 * Converts a 16-bit integer from host to network order.
 */

/**
 * \def KPTNToH32(n)
 * Converts a 32-bit integer from network to host order.
 */

/**
 * \def KPTHToN32(n)
 * Converts a 32-bit integer from host to network order.
 */

#if (KPT_BYTE_ORDER == KPT_ENDIAN_BIG)

	#define KPTNToH32(n)   (n)
	#define KPTHToN32(n)   (n)
	#define KPTNToH16(n)   (n)
	#define KPTHToN16(n)   (n)

#elif (KPT_BYTE_ORDER == KPT_ENDIAN_LITTLE)

	#define KPTNToH32(n)   KPTBYTE_SWAP32(n)
	#define KPTHToN32(n)   KPTBYTE_SWAP32(n)
	#define KPTNToH16(n)   KPTBYTE_SWAP16(n)
	#define KPTHToN16(n)   KPTBYTE_SWAP16(n)

#elif (KPT_BYTE_ORDER == KPT_ENDIAN_DYNAMIC)

	#define KPTNToH32(n)   KPTEndianNetworkToHost32(n)
	#define KPTHToN32(n)   KPTEndianHostToNetwork32(n)
	#define KPTNToH16(n)   KPTEndianNetworkToHost16(n)
	#define KPTHToN16(n)   KPTEndianHostToNetwork16(n)

#else

	error byte order undefined

#endif

KPT_LIB_SYSTEM
uint32_t
KPT_CALL
KPTEndianNetworkToHost32(uint32_t aValue);

KPT_LIB_SYSTEM
uint16_t
KPT_CALL
KPTEndianNetworkToHost16(uint16_t aValue);

KPT_LIB_SYSTEM
uint32_t
KPT_CALL
KPTEndianHostToNetwork32(uint32_t aValue);

KPT_LIB_SYSTEM
uint16_t
KPT_CALL
KPTEndianHostToNetwork16(uint16_t aValue);

KPT_LIB_SYSTEM
KPTBoolT
KPT_CALL
KPTEndianIsLittle(void);

KPT_LIB_SYSTEM
KPTBoolT
KPT_CALL
KPTEndianIsBig(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef H_KPTENDIAN_H */
