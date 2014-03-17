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
 * @file    kptbyte.h
 *
 * @brief   Bit and Byte manipulation.
 *
 * @details This file contains functions and macros for manipulating bits
 *          and handling byte order issues. Some of the order functions are 
 *          implemented as macros.
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTBYTE_H
#define H_KPTBYTE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Byte type for memory offsets.
 */
typedef uint8_t KPTByteT;

/**
 * Defines an integer with bit \a bit set.
 */
#define KPTBIT(bit)                    (1 << (bit))

/**
 * Sets the specified bit in \a num.
 */
#define KPTBIT_SET(num, bit)           ((num) |= KPTBIT(bit))

/**
 * Clears the specified bit in \a num.
 */
#define KPTBIT_CLEAR(num, bit)         ((num) &= ~KPTBIT(bit))

/**
 * Toggles the specified bit in \a num.
 */
#define KPTBIT_TOGGLE(num, bit)        ((num) ^= KPTBIT(bit))

/**
 * Tests if the specified bit is set in \a num.
 */
#define KPTBIT_CHECK(num, bit)         (0 != ((num) & KPTBIT(bit)))



/**
 * Defines an integer with 8-bits set at index \a b.
 */
#define KPTBIT8(b)                     (0xff << ((b) * 8))

/**
 * Sets all 8-bits at index \a b.
 */
#define KPTBIT8_SET(num, b)            ((num) |= KPTBIT8(b))

/**
 * Clears all 8-bits at index \a b.
 */
#define KPTBIT8_CLEAR(num, b)          ((num) &= ~KPTBIT8(b))

/**
 * Toggles all 8-bits at index \a b.
 */
#define KPTBIT8_TOGGLE(num, b)         ((num) ^= KPTBIT8(b))

/**
 * Tests if any of the 8-bits are set at index \a b.
 */
#define KPTBIT8_CHECK(num, b)          (0 != ((num) & KPTBIT8(b)))

/**
 * Tests if all of the 8-bits are set at index \a b.
 */
#define KPTBIT8_CHECKALL(num, b)       (KPTBIT8(b) != ((num) & KPTBIT8(b)))

/**
 * Gets the result of a number shifted left by a multiple of 8 bits.
 */
#define KPTBIT8_SHIFTL(num, b)         ((num) << (b * 8))

/**
 * Gets the result of a number shifted right by a multiple of 8 bits.
 */
#define KPTBIT8_SHIFTR(num, b)         ((num) >> (b * 8))

/**
 * Creates an integer where the 8-bits at index \a b are the least 
 * significant 8-bits in \a num.
 */
#define KPTBIT8_PACK(num, b)           (KPTBIT8_SHIFTL(num, b) & KPTBIT8(b))

/**
 * Creates an integer where the the least significant 8-bits are the
 * same as \a num, index \a b 
 */
#define KPTBIT8_UNPACK(num, b)         (uint8_t)(KPTBIT8_SHIFTR(num, b) & KPTBIT8(0))




/**
 * Defines an integer with 16-bits set at index \a b.
 */
#define KPTBIT16(b)                    (0xffff << ((b) * 16))

/**
 * Sets all 16-bits at index \a b.
 */
#define KPTBIT16_SET(num, b)           ((num) |= KPTBIT16(b))

/**
 * Clears all 16-bits at index \a b.
 */
#define KPTBIT16_CLEAR(num, b)         ((num) &= ~KPTBIT16(b))

/**
 * Toggles all 16-bits at index \a b.
 */
#define KPTBIT16_TOGGLE(num, b)        ((num) ^= KPTBIT16(b))

/**
 * Tests if any of the 16-bits are set at index \a b.
 */
#define KPTBIT16_CHECK(num, b)         (0 != ((num) & KPTBIT16(b)))

/**
 * Tests if all of the 16-bits are set at index \a b.
 */
#define KPTBIT16_CHECKALL(num, b)      (KPTBIT16(b) != ((num) & KPTBIT16(b)))

/**
 * Gets the result of a number shifted left by a multiple of 16 bits.
 */
#define KPTBIT16_SHIFTL(num, b)        ((num) << (b * 16))

/**
 * Gets the result of a number shifted right by a multiple of 16 bits.
 */
#define KPTBIT16_SHIFTR(num, b)        ((num) >> (b * 16))

/**
 * Creates an integer where the 16-bits at index \a b are the least 
 * significant 16-bits in \a num.
 */
#define KPTBIT16_PACK(num, b)          (KPTBIT16_SHIFTL(num, b) & KPTBIT16(b))

/**
 * Creates an integer where the the least significant 16-bits are the
 * same as \a num, index \a b 
 */
#define KPTBIT16_UNPACK(num, b)        (uint16_t)(KPTBIT16_SHIFTR(num, b) & KPTBIT16(0))




/**
 * Sets the bits in \a num that are set in \a mask.
 */
#define KPTMASK_ADD(num, mask)         ((num) |= (mask))

/**
 * Clears the bits in \a num that are set in \a mask.
 */
#define KPTMASK_CLEAR(num, mask)       ((num) &= ~(mask))

/**
 * Toggles the bits in \a num that are set in \a mask.
 */
#define KPTMASK_TOGGLE(num, mask)       ((num) ^= (mask))

/**
 * Checks if any bits set in \a mask are also set in \a num.
 */
#define KPTMASK_CHECK(num, mask)       (0 != ((num) & (mask)))

/**
 * Checks if all bits set in \a mask are also set in \a num.
 */
#define KPTMASK_CHECKALL(num, mask)    ((mask) == ((num) & (mask)))




/**
 * Returns a 16-bit unsigned integer that represents \a value with the
 * byte order swapped.
 */
#define KPTBYTE_SWAP16(value) (uint16_t)((uint16_t)(KPTBIT8_SHIFTL(value, 1) & KPTBIT8(1))  |\
                                        (uint16_t)(KPTBIT8_SHIFTR(value, 1) & KPTBIT8(0)))

/**
 * Returns a 32-bit unsigned integer that represents \a value with the
 * byte order swapped.
 */
#define KPTBYTE_SWAP32(value) (uint32_t)((uint32_t)(KPTBIT8_SHIFTL(value, 3) & KPTBIT8(3))  |\
                                        (uint32_t)(KPTBIT8_SHIFTL(value, 1) & KPTBIT8(2))  |\
                                        (uint32_t)(KPTBIT8_SHIFTR(value, 1) & KPTBIT8(1))  |\
                                        (uint32_t)(KPTBIT8_SHIFTR(value, 3) & KPTBIT8(0)))

/**
 * Performs byte swapping on an array of 16-bit integers.
 * 
 * aSource and aTarget can be the same, but must not be NULL.
 * @param[in] aTarget   Target pointer.
 * @param[in] aSource   Source pointer.
 * @param[in] aCount    Array size.
 */
static KPTINLINE
void KPTByteSwapArray16(uint16_t* aTarget,
                        const uint16_t* aSource,
                        size_t aCount)
{
	while (aCount--)
	{
		*aTarget = KPTBYTE_SWAP16(*aSource);
		++aTarget;
		++aSource;
	}
}

/**
 * Performs byte swapping on an array of 32-bit integers.
 *
 * aSource and aTarget can be the same, but must not be NULL.
 * @param[in] aTarget   Target pointer.
 * @param[in] aSource   Source pointer.
 * @param[in] aCount    Array size.
 */
static KPTINLINE
void KPTByteSwapArray32(uint32_t* aTarget,
                        const uint32_t* aSource,
                        size_t aCount)
{
	while (aCount--)
	{
		*aTarget = KPTBYTE_SWAP32(*aSource);
		++aTarget;
		++aSource;
	}
}

/**
 * Offsets a pointer by a specified number of bytes, not pointers.
 * 
 * @param[in] aPointer  Start pointer.
 * @param[in] aBytes    Byte offset, can be negative.
 */
static KPTINLINE
void* KPTBytePointerOffset(const void* aPointer,
                           ptrdiff_t aBytes)
{
	return ((KPTByteT*)aPointer) + aBytes;
}

/**
 * Calculates the number of bytes between two pointers.
 *
 * @param[in] aFrom  Start pointer.
 * @param[in] aTo    End pointer.
 * @return           Difference in bytes (aFrom - aTo). May be negative.
 */
static KPTINLINE
ptrdiff_t KPTBytePointerDiff(const void* aFrom,
                             const void* aTo)
{
	return (KPTByteT*)aTo - (KPTByteT*)aFrom;
}

/**
 * Returns an aligned pointer.
 *
 * @param[in] aBase         Base pointer.
 * @param[in] aAlignment    Size of byte alignment (1,2,4,8,...).
 * @return                  Aligned pointer.
 */
static KPTINLINE
void* KPTBytePointerAlign(const void* aBase,
                          size_t aAlignment)
{
	return (void*)(((intptr_t)aBase + (aAlignment-1)) & ~(aAlignment-1));
}

/**
 * Rounds a byte count up to the nearest block multiple.
 *
 * @param[in] aNumber       The number to round up.
 * @param[in] aMultiple     The required multiple.
 * @return                  The rounded value size.
 * @returns
 *    if aNumber = 0 : aMultiple
 *    if aMultiple = 0 : aNumber
 *    else rounded value
 */
static KPTINLINE
size_t KPTByteRoundUpToMultiple(size_t aNumber,
                                size_t aMultiple)
{
	if (aMultiple)
	{
		aNumber += aMultiple - 1;
		aNumber -= (aNumber % aMultiple);
		if (!aNumber)
		{
			aNumber = aMultiple;
		}
	}
	return aNumber;
}

/**
 * Offsets a pointer by a number of items.
 * 
 * @param[in] aPointer  Start pointer.
 * @param[in] aCount    The number of items to offset, can be negative.
 * @param[in] aWidth    The wdth of each item.
 */
static KPTINLINE
void* KPTPointerOffset(const void* aPointer,
                       ptrdiff_t aCount,
                       size_t aWidth)
{
	return KPTBytePointerOffset(aPointer, (ptrdiff_t)(aCount * aWidth));
}


#ifdef __cplusplus
}
#endif

#endif /* #ifndef H_KPTBYTE_H */
