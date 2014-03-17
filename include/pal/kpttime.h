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
 * @file    kpttime.h
 *
 * @brief   System time information functions.
 *
 * @details 
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTTIME_H
#define H_KPTTIME_H

#include "kptlibsystem.h"
#include "kptapi.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct KPTTimeT KPTTimeT;
/** A structure that represents an time and date */
struct KPTTimeT
{
	uint32_t info;                  /**< One or more KPTTimeInfoT values */
	uint16_t year;                  /**<  */
	uint16_t month;                 /**< (1-12)*/ 
	uint16_t dayOfWeek;             /**< (0-6) 0=Sunday */ 
	uint16_t day;                   /**< (1-31) */
	uint16_t hour;                  /**< (0-23) */ 
	uint16_t minute;                /**< (0-59) */ 
	uint16_t second;                /**< (0-60) */ 
	uint16_t milliseconds;          /**< (0-999) */ 
};

/** Information bits for a time structure */
enum KPTTimeInfoT
{
	eKPTTimeValid = KPTBIT(0),      /**< Indicates that the data has been validated */
	eKPTTimeUTC = KPTBIT(1)         /**< Indicates that the data uses the UTC time zone*/
};
typedef enum KPTTimeInfoT KPTTimeInfoT;

typedef struct KPTTimeDiffT KPTTimeDiffT;
/** Difference between two KPTTimeT structures */
struct KPTTimeDiffT
{
	uint32_t days;                  /**< number of days difference */
	uint16_t hours;                 /**< number of hours difference */
	uint16_t minutes;               /**< number of minutes difference */
	uint16_t seconds;               /**< number of seconds difference */
	uint16_t milliseconds;          /**< number of milliseconds difference */
	int comparison;                 /**< Comparison flag */
};

/** Constants for converting time units */
enum KPTTimeConstantsT
{
	eKPTTimeSecondsPerMinute = 60,  /**< Number of seconds in a standard minute */
	eKPTTimeMinutesPerHour = 60,    /**< Number of minutes in a standard hour */
	eKPTTimeHoursPerDay = 24,       /**< Number of hours in a standard day */

	/** Number of seconds in a standard hour */
	eKPTTimeSecondsPerHour = eKPTTimeSecondsPerMinute * eKPTTimeMinutesPerHour,

	/** Number of seconds in a standard day */
	eKPTTimeSecondsPerDay = eKPTTimeSecondsPerHour * eKPTTimeHoursPerDay,

	/** Number of minutes in a standard day */
	eKPTTimeMinutesPerDay = eKPTTimeMinutesPerHour * eKPTTimeHoursPerDay,

	/** Number of milliseconds in a standard hour */
	eKPTTimeMillisecondsPerDay = eKPTTimeSecondsPerDay * 1000
};
typedef enum KPTTimeConstantsT KPTTimeConstantsT;

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTimeGetUTC(KPTTimeT* aTime);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTimeGetLocal(KPTTimeT* aTime);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTimeInitDate(KPTTimeT* aTime,
                int aYear,
                int aMonth,
                int aDay,
                uint32_t aInfo);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTimeValidate(KPTTimeT* aTime);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTimeAfterMidnight(const KPTTimeT* aTime,
                     uint32_t* aMilliseconds);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTimeBeforeMidnight(const KPTTimeT* aTime,
                      uint32_t* aMilliseconds);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTimeGetDiff(const KPTTimeT* aFrom,
               const KPTTimeT* aTo,
               KPTTimeDiffT* aDiff);

KPT_LIB_SYSTEM
KPTResultT
KPT_CALL
KPTTimeCompare(const KPTTimeT* aTime1,
               const KPTTimeT* aTime2,
               int* aCompare);

KPT_LIB_SYSTEM
KPTBoolT
KPT_CALL
KPTTimeIsLeapYear(int aYear);

KPT_LIB_SYSTEM
int
KPT_CALL
KPTTimeDaysInYear(int aYear);

KPT_LIB_SYSTEM
int
KPT_CALL
KPTTimeGetDayOfWeek(int aYear,
                    int aMonth,
                    int aDay);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* #ifndef H_KPTTIME_H */
